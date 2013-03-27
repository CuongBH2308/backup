/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "mm_manager.h"
#include "mm_txn.h"
#include "mm_txnmanager.h"

#ifdef _DEBUG
#include "msxml.h"
#import "msxml6.dll"
#endif

#define PAGE_SIZE  4096
#define BLOCK_SIZE (PAGE_SIZE * 16)

MM_Manager::MM_Manager(void)
{
}

MM_Manager::~MM_Manager(void)
{
	BOOL bOK = false;

	std::vector<void*>::const_iterator itEnd = m_vPageAllocated.end();
	std::vector<void*>::const_iterator it;
	for(it = m_vPageAllocated.begin(); it != itEnd; ++it)
		::VirtualFree(*it, 0, MEM_RELEASE);

	m_vPageAllocated.clear();
	m_mMemoryUsed.clear();
	m_mMemoryUnused.clear();
}

MM_Manager* MM_Manager::Get()
{
	static MM_Manager memManager;
	return &memManager;
}

// Exception filter
// Backup the target page
int MM_Manager::ExceptionFilter(void* exp)
{
	// Must happen in a transaction
	MM_Txn* pTxn = MM_TxnManager::Get()->GetActiveTxn();
	if(!pTxn)
		return EXCEPTION_CONTINUE_SEARCH;

	LPEXCEPTION_POINTERS e = static_cast<LPEXCEPTION_POINTERS>(exp);

	// Ignore if the exception is not EXCEPTION_ACCESS_VIOLATION
	if (e->ExceptionRecord->ExceptionCode != EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_CONTINUE_SEARCH;

	// The first element of the ExceptionInformation[] array contains a read-write flag 
	// that indicates the type of operation that caused the access violation. 
	// If this value is 0, the thread attempted to read the inaccessible data. 
	// If this value is 1, the thread attempted to write to an inaccessible address. 
	// The second array element specifies the virtual address of the inaccessible data. 
	bool	bWriting = (e->ExceptionRecord->ExceptionInformation[0] != 0);
	void*	pAddr	 = (void*)e->ExceptionRecord->ExceptionInformation[1];
	void*	pPage	 = GetPageAddress(pAddr);//(void*)((ULONG_PTR)pAddr & ~(PAGE_SIZE - 1));

	// Ignore if reading data 
	if (!bWriting)
		return EXCEPTION_CONTINUE_SEARCH;

	// Ignore if this memory is not controlled by this manager
	if (!IsStorage(pPage))
		return EXCEPTION_CONTINUE_SEARCH;

	// Backup this page
	void* pBackup = BackupAPage(pPage);
	if (!pBackup)
		return EXCEPTION_CONTINUE_SEARCH;

	BOOL bOK = pTxn->SetMap(pPage, pBackup);
	if(!bOK)
		return EXCEPTION_CONTINUE_SEARCH;

	// Make the original memory can be written into
	bOK = UnlockStorage(pPage, PAGE_SIZE);
	if(!bOK)
		return EXCEPTION_CONTINUE_SEARCH;

	return EXCEPTION_CONTINUE_EXECUTION;
}

// Get one page's size
size_t MM_Manager::GetPageSize() const
{
	return PAGE_SIZE;
}

// Get page's address
void* MM_Manager::GetPageAddress(void* pAddress) const
{
	return (void*)((ULONG_PTR)pAddress & ~(PAGE_SIZE - 1));
}

// Allocate memory 
void* MM_Manager::AllocStorage(size_t nSize)
{
	void* pAddress = NULL;

	// Try to allocate the memory from the unused block
	std::map<void*, size_t>::const_iterator itEnd = m_mMemoryUnused.end();
	std::map<void*, size_t>::iterator it;
	for(it = m_mMemoryUnused.begin(); it != itEnd; ++it)
	{
		if(it->second == nSize)
		{
			pAddress = it->first;
			m_mMemoryUsed[pAddress] = nSize;
			m_mMemoryUnused.erase(it);
			break;
		}
		else if(it->second > nSize)
		{
			pAddress = it->first;
			m_mMemoryUsed[pAddress] = nSize;
			size_t nLeft = it->second - nSize;
			m_mMemoryUnused.erase(it);
			m_mMemoryUnused[(void*)((char*)(pAddress)+nSize)] = nLeft;
			break;
		}
	}

	// If pAddress is locked, then we need to backup that page and unlock it
	if(pAddress)
	{
		//void* pPage		= GetPageAddress(pAddress);
		//MM_Txn* pTxn	= MM_TxnManager::Get()->GetActiveTxn();

		//if(IsLocked(pPage) && pTxn)
		//{
		//	// Backup this page
		//	void* pBackup = BackupAPage(pAddress);
		//	ASSERT(pBackup);

		//	BOOL bOK = pTxn->SetMap(pPage, pBackup);
		//	ASSERT(bOK);

		//	// Make the original memory can be written into
		//	bOK = UnlockStorage(pPage, PAGE_SIZE);
		//	ASSERT(bOK);
		//}
	}
	else
	{
		// Get pages that will be allocated
		size_t iPage = nSize/PAGE_SIZE;
		if(nSize%PAGE_SIZE != 0)
			iPage++;

		// Get the real size that will be allocated
		size_t nRealSize = iPage*PAGE_SIZE;

		// Allocate memory
		pAddress = ::VirtualAlloc(NULL, nRealSize, MEM_COMMIT, PAGE_READWRITE);

		// Record the memory's information
		if(pAddress)
		{
			// Store the allocated page for release in the future
			m_vPageAllocated.push_back(pAddress);

			// Record the used memory's information
			m_mMemoryUsed[pAddress] = nSize;

			// Record the unused memory's information
			if(nRealSize > nSize)
				m_mMemoryUnused[(void*)((char*)(pAddress)+nSize)] = nRealSize-nSize;
		}
	}


	return pAddress;
}

// Deallocate memory of storage
BOOL MM_Manager::FreeStorage(void* pAddress)
{
	return TRUE;
}

// Get memory information
BOOL MM_Manager::GetStorage(void* pAddress, void** p, size_t* pnSize) const
{
	std::map<void*, size_t>::const_iterator itEnd = m_mMemoryUsed.end();
	std::map<void*, size_t>::const_iterator it;
	for(it = m_mMemoryUsed.begin(); it != itEnd; ++it)
	{
		if(it->first <= pAddress && (char*)it->first+it->second > pAddress)
		{
			if(p)
				*p = it->first;
			if(pnSize)
				*pnSize = it->second;
			return TRUE;
		}
	}

	return FALSE;
}

// Is the memory controlled by this manager
BOOL MM_Manager::IsStorage(void* pAddress) const
{
	return (GetStorage(pAddress)!=NULL);
}

// Lock all storage memory
BOOL MM_Manager::LockAll() const
{
	BOOL bOK = FALSE;

	std::map<void*, size_t>::const_iterator itEnd = m_mMemoryUsed.end();
	std::map<void*, size_t>::const_iterator it;
	for(it = m_mMemoryUsed.begin(); it != itEnd; ++it)
	{
		bOK = LockStorage(it->first, it->second);
		ASSERT(bOK);
	}

	return bOK;
}

// Unlock all storage memory
BOOL MM_Manager::UnlockAll() const
{
	BOOL bOK = FALSE;

	std::map<void*, size_t>::const_iterator itEnd = m_mMemoryUsed.end();
	std::map<void*, size_t>::const_iterator it;
	for(it = m_mMemoryUsed.begin(); it != itEnd; ++it)
	{
		bOK = UnlockStorage(it->first, it->second);
		ASSERT(bOK);
	}

	return bOK;
}

// Whether the page is locked
BOOL MM_Manager::IsLocked(void* pAddress) const
{
	// Get page's address (pAddress is in that page)
	void* pPage = GetPageAddress(pAddress);

	MEMORY_BASIC_INFORMATION info;
	::VirtualQuery(pPage, &info, PAGE_SIZE);
	if(info.Protect == PAGE_READONLY)
		return TRUE;

	return FALSE;
}

// Lock memory
BOOL MM_Manager::LockStorage(void* pAddress, size_t nSize) const
{
	// Get page's address (pAddress is in that page)
	void* pPage = GetPageAddress(pAddress);

	// Get page number
	nSize = (size_t)pAddress + nSize - (size_t)pPage;
	size_t nPage = size_t(nSize/PAGE_SIZE);
	if(nSize%PAGE_SIZE != 0)
		nPage++;

	DWORD dwOld = 0;
	// Make the backup memory can't be written into
	return ::VirtualProtect(pPage, PAGE_SIZE*nPage, PAGE_READONLY, &dwOld);
}

// Unlock memory
BOOL MM_Manager::UnlockStorage(void* pAddress, size_t nSize) const
{
	// Get page's address (pAddress is in that page)
	void* pPage = GetPageAddress(pAddress);

	// Get page number
	nSize = (size_t)pAddress + nSize - (size_t)pPage;
	size_t nPage = size_t(nSize/PAGE_SIZE);
	if(nSize%PAGE_SIZE != 0)
		nPage++;

	DWORD dwOld = 0;
	// Make the backup memory can be written into
	return ::VirtualProtect(pPage, PAGE_SIZE*nPage, PAGE_READWRITE, &dwOld);
}

// Backup a page memory
// return the base address of the "to" memory
void* MM_Manager::BackupAPage(void* pAddress)
{
	ASSERT(IsStorage(pAddress));

	// Get the page used to store the memory
	void* pPageStorage = GetPageAddress(pAddress);
	if(!pPageStorage)
		return NULL;

	// Allocate memory for backup
	void* pPageBackup = new char [PAGE_SIZE];

	// Backup a page that includes pAddress
	memcpy(pPageBackup, pPageStorage, PAGE_SIZE);

	// The backup memory
	return pPageBackup;
}


/************************************************************************/
/* 
Pages
 |_ <x1000-x2000>
		|_ <x1000-x1004 used = "1">
		|_ <x1005-x2000 used = "0">
*/
/************************************************************************/
// Dump m_mMemoryStorage into an xml file
#ifdef _DEBUG
void MM_Manager::Dump(LPCTSTR lpFileName)
{
	//// _Kty: the page base address
	//// _Ty: allocated memory
	//std::map< void*, std::vector<void*>* > pageMap;
	//for(std::map<void*, MM_Space*>::const_iterator it = m_mMemoryStorage.begin(); it != m_mMemoryStorage.end(); it++)
	//{
	//	void* pPage = GetPageAddress(it->first);
	//	std::map< void*, std::vector<void*>* >::iterator itPage = pageMap.find(pPage);

	//	if( itPage != pageMap.end() )
	//	{
	//		std::vector<void*>* pVect = itPage->second;
	//		ASSERT(pVect);

	//		std::vector<void*>::iterator itMem = pVect->begin();
	//		for(; itMem != pVect->end(); itMem++)
	//		{
	//			if( ULONG_PTR(*itMem) > ULONG_PTR(it->first) )
	//				break;
	//		}
	//		pVect->insert(itMem, it->first);
	//	}
	//	else
	//	{
	//		std::vector<void*>* pVect = new std::vector<void*>();
	//		pVect->push_back(it->first);
	//		pageMap[pPage] = pVect;
	//	}
	//}

	//CComPtr<MSXML2::IXMLDOMDocument> spXMLDOMDocument;
	//HRESULT hr = spXMLDOMDocument.CoCreateInstance(L"Msxml2.DOMDocument.4.0", NULL, CLSCTX_INPROC_SERVER);
	//ASSERT(SUCCEEDED(hr)); 
	//if(FAILED(hr)) 
	//	return;

	//// "Pages". Root
	//CComPtr<MSXML2::IXMLDOMElement> spXMLDOMElement = spXMLDOMDocument->createElement(_bstr_t("Pages"));
	//ASSERT(spXMLDOMElement);	if(!spXMLDOMElement)	return;
	//CComPtr<MSXML2::IXMLDOMNode> spXMLDOMElementOut = spXMLDOMDocument->appendChild(spXMLDOMElement);
	//ASSERT(spXMLDOMElementOut); if(!spXMLDOMElementOut) return;


	//for(std::map< void*, std::vector<void*>* >::const_iterator it = pageMap.begin(); it != pageMap.end(); it++)
	//{
	//	// <x1000-x2000>
	//	CString str;
	//	str.Format(_T("p_%x-%x"), ULONG_PTR(it->first), ULONG_PTR(it->first)+PAGE_SIZE-1);
	//	if(IsLocked(it->first))
	//		str += _T("_Locked");

	//	CComPtr<MSXML2::IXMLDOMNode> spXMLDOMNode = spXMLDOMDocument->createNode(CComVariant(MSXML2::NODE_ELEMENT), _bstr_t(str), _bstr_t());
	//	ASSERT(spXMLDOMNode);		if(!spXMLDOMNode)		return;
	//	CComPtr<MSXML2::IXMLDOMNode> spXMLDOMNodeOut = spXMLDOMElementOut->appendChild(spXMLDOMNode);
	//	ASSERT(spXMLDOMNodeOut);	if(!spXMLDOMNodeOut)	return;

	//	std::vector<void*>* pVect = it->second;
	//	for(std::vector<void*>::const_iterator itMem = pVect->begin(); itMem != pVect->end(); itMem++)
	//	{
	//		MM_Space* pSpace = GetStorage(*itMem);
	//		if(pSpace)
	//		{
	//			str.Format(_T("p_%x-%x"), ULONG_PTR(pSpace->GetAddress()), ULONG_PTR(pSpace->GetAddress())+pSpace->GetSize()-1);
	//			CComQIPtr<MSXML2::IXMLDOMElement> spXMLDOMElementSlot = spXMLDOMDocument->createNode(CComVariant(MSXML2::NODE_ELEMENT), 
	//				_bstr_t(str), _bstr_t());
	//			ASSERT(spXMLDOMElementSlot);if(!spXMLDOMElementSlot)return;
	//			int iTrue = pSpace->m_bUsing ? 1:0;
	//			spXMLDOMElementSlot->setAttribute(_bstr_t("size"), CComVariant(int(pSpace->GetSize())));
	//			spXMLDOMElementSlot->setAttribute(_bstr_t("used"), CComVariant(iTrue));
	//			spXMLDOMNodeOut->appendChild(spXMLDOMElementSlot);
	//		}
	//	}
	//}

	//spXMLDOMDocument->save(CComVariant(lpFileName));

	//for(std::map< void*, std::vector<void*>* >::iterator it = pageMap.begin(); it != pageMap.end(); it++)
	//	delete (it->second);
	//pageMap.clear();
}
#endif

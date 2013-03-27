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


#pragma once
#include <map>
#include <vector>

class MM_Manager
{
public:
	MM_Manager(void);
	virtual ~MM_Manager(void);

	// Get the memory manager.
	// There should be only one instance.
	static		MM_Manager* Get();

	// Exception filter
	// Backup the target page
	int			ExceptionFilter(void* exp);

	// Get one page's size
	size_t		GetPageSize() const;

	// Get page's address
	void*		GetPageAddress(void* pAddress) const;

	// Allocate memory for storing
	void*		AllocStorage(size_t nSize);

	// Deallocate memory of storage
	BOOL		FreeStorage(void* pAddress);

	// Get memory information
	BOOL		GetStorage(void* pAddress, void** p = NULL, size_t* pnSize = NULL) const;

	// Is the memory controlled by this manager
	BOOL		IsStorage(void* pAddress) const;

	// Lock all storage memory
	BOOL		LockAll() const;

	// Unlock all storage memory
	BOOL		UnlockAll() const;

	// Whether the page is locked
	BOOL		IsLocked(void* pAddress) const;

	// Lock memory
	BOOL		LockStorage(void* pAddress, size_t nSize) const;

	// Unlock memory
	BOOL		UnlockStorage(void* pAddress, size_t nSize) const;

	// Backup a page memory
	// return the base address of the "to" memory
	void*		BackupAPage(void* pAddress);

#ifdef _DEBUG
	// Dump m_mMemoryStorage into an xml file
	void		Dump(LPCTSTR lpFileName);
#endif

private:
	// Pages that have been allocated
	std::vector<void*>	m_vPageAllocated;

	// Memory that has been used
	// _Kty: the address of the memory that has been used
	std::map<void*, size_t> m_mMemoryUsed;

	// Memory that has not been used
	// _Kty: the address of the memory that has been unused
	std::map<void*, size_t> m_mMemoryUnused;
};

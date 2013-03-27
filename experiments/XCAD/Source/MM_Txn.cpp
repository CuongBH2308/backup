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
#include "mm_txn.h"
#include "mm_manager.h"

MM_Txn::MM_Txn(int iTxnId)
:m_iTxnId(iTxnId),
m_bStarted(FALSE)
{
}

MM_Txn::~MM_Txn(void)
{
	// Delete all backup memory
	std::map<void*, void*>::const_iterator itEnd = m_mMemBackup.end();
	std::map<void*, void*>::const_iterator it;
	for(it = m_mMemBackup.begin(); it != itEnd; ++it)
		delete it->second;

	m_mMemBackup.clear();
}

// Get the TxnId
int MM_Txn::GetId() const
{
	return m_iTxnId;
}

// Start the transaction
BOOL MM_Txn::Start()
{
	m_bStarted = TRUE;
	return MM_Manager::Get()->LockAll();
}

// End (commit) the transaction
// Lock all relative memory
BOOL MM_Txn::End()
{
	m_bStarted = FALSE;
	return MM_Manager::Get()->UnlockAll();
}

// Abort the transaction
BOOL MM_Txn::Abort()
{
	return TRUE;
}

// Undo the transaction
BOOL MM_Txn::Undo()
{
	if(m_bStarted)
		return FALSE;

	// Get memory manager
	MM_Manager* pMemMgr = MM_Manager::Get();

	// Get page size
	size_t nPageSize = pMemMgr->GetPageSize();

	// Restore each page
	if(m_mMemBackup.size() > 0)
	{
		std::map<void*, void*>::const_iterator it = m_mMemBackup.end();
		it--;
		for(; it != m_mMemBackup.begin(); it--)
		{
			ASSERT(it->second);
			memcpy(it->first, it->second, nPageSize);
		}
		ASSERT(it->second);
		memcpy(it->first, it->second, nPageSize);
	}

	return TRUE;
}

// Redo the transaction
BOOL MM_Txn::Redo()
{
	return TRUE;
}

// Add / Set one item into m_mMemBackup
BOOL MM_Txn::SetMap(void* pPageStorage, void* pBackup)
{
	m_mMemBackup[pPageStorage] = pBackup;
	return TRUE;
}


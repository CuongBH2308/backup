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

class MM_Txn
{
	friend class MM_TxnManager;

public:
	// Add / Set one item into m_mMemBackup
	BOOL SetMap(void* pPageStorage, void* pBackup);

protected:
	MM_Txn(int iTxnId);
	virtual ~MM_Txn(void);

	// Get the TxnId
	int		GetId() const;

	// Start the transaction
	BOOL	Start();

	// End (commit) the transaction
	BOOL	End();

	// Abort the transaction
	BOOL	Abort();

	// Undo the transaction
	BOOL	Undo();

	// Redo the transaction
	BOOL	Redo();
private:
	int m_iTxnId;

	// Start flag
	BOOL m_bStarted;

	// The key of the map is the original page 
	std::map<void*, void*> m_mMemBackup;
};

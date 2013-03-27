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
#include <vector>

class MM_Txn;
class MM_TxnManager
{
public:
	MM_TxnManager(void);
	virtual ~MM_TxnManager(void);

	// Get the transaction manager.
	// There should be only one instance.
	static MM_TxnManager* Get();

	// Create a new transaction and add it into the list
	MM_Txn* Add();

	// Get the active transaction
	MM_Txn* GetActiveTxn() const;

	// Start transaction
	BOOL	StartTxn(MM_Txn* pTxn = NULL);

	// End transaction
	BOOL	EndTxn();

	// Abort transaction
	BOOL	AbortTxn();

	// Undo transaction
	BOOL	UndoTxn();

	// Redo transaction
	BOOL	RedoTxn();

private:
	// Get a transaction from the list upon the TxnId
	MM_Txn* Get(int iTxnId) const;

	// Create a new transaction and add it into the list
	MM_Txn* Add(int iTxnId);

	// When we start transaction, this variable keeps the current transaction
	MM_Txn* m_pActiveTxn;

	// The list for storing all finished transactions
	std::vector<MM_Txn*> m_vTxn;

	// The list for storing all undone transactions
	std::vector<MM_Txn*> m_vTxnUndo;
};

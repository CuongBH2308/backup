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
#include "mm_txnmanager.h"
#include "mm_txn.h"

MM_TxnManager::MM_TxnManager(void)
{
}

MM_TxnManager::~MM_TxnManager(void)
{
	for(std::vector<MM_Txn*>::iterator it = m_vTxn.begin(); it != m_vTxn.end(); it++)
		delete (*it);
	m_vTxn.clear();

	for(std::vector<MM_Txn*>::iterator it = m_vTxnUndo.begin(); it != m_vTxnUndo.end(); it++)
		delete (*it);
	m_vTxnUndo.clear();	
}

// Get the transaction manager.
// There should be only one instance.
MM_TxnManager* MM_TxnManager::Get()
{
	static MM_TxnManager txnManager;
	return &txnManager;
}

// Create a new transaction and add it into the list
MM_Txn* MM_TxnManager::Add()
{
	MM_Txn* pTxn = NULL;
	int iTxnId = 1;
	while(true)
	{
		pTxn = Get(iTxnId);
		if(!pTxn)
			break;
		else
			iTxnId++;
	}

	return Add(iTxnId);
}

// Get the active transaction
MM_Txn* MM_TxnManager::GetActiveTxn() const
{
	return m_pActiveTxn;
}

// Start transaction
BOOL MM_TxnManager::StartTxn(MM_Txn* pTxn /*=NULL*/)
{
	if(m_pActiveTxn)
		m_pActiveTxn->Abort();
	if(!pTxn)
		pTxn = Add();
	m_pActiveTxn = pTxn;
	return pTxn->Start();
}

// End transaction
BOOL MM_TxnManager::EndTxn()
{
	BOOL bOK = FALSE;
	if(m_pActiveTxn)
	{
		bOK = m_pActiveTxn->End();
		m_pActiveTxn = NULL;
	}
	else
		ASSERT(0);

	return bOK;
}

// Abort transaction
BOOL MM_TxnManager::AbortTxn()
{
	BOOL bOK = FALSE;
	if(m_pActiveTxn)
	{
		bOK = m_pActiveTxn->Abort();
		m_pActiveTxn = NULL;
	}
	else
		ASSERT(0);

	return bOK;
}

// Undo transaction
BOOL MM_TxnManager::UndoTxn()
{
	BOOL bOK = FALSE;
	if(!m_pActiveTxn && m_vTxn.size()>0)
	{
		MM_Txn* pTxn = m_vTxn.back();
		if(pTxn)
		{
			// Undo the transaction
			bOK = pTxn->Undo();

			if(bOK)
			{
				// Erase the last item
				m_vTxn.pop_back();

				// Push the transaction into undone list
				m_vTxnUndo.push_back(pTxn);
			}
		}
	}
	return bOK;
}

// Redo transaction
BOOL MM_TxnManager::RedoTxn()
{
	BOOL bOK = FALSE;
	if(!m_pActiveTxn && m_vTxnUndo.size()>0)
	{
		std::vector<MM_Txn*>::iterator it = m_vTxnUndo.begin();
		MM_Txn* pTxn = *it;

		if(pTxn)
		{
			// Redo the transaction
			bOK = pTxn->Redo();

			if(bOK)
			{
				// Erase 
				m_vTxnUndo.erase(it);

				// Push the transaction into transaction list
				m_vTxn.push_back(pTxn);
			}
		}
	}
	return bOK;
}

// Get a transaction from the list upon the TxnId
MM_Txn* MM_TxnManager::Get(int iTxnId) const
{
	for(std::vector<MM_Txn*>::const_iterator it = m_vTxn.begin(); it != m_vTxn.end(); it++)
	{
		if((*it)->GetId() == iTxnId)
			return (*it);
	}

	return NULL;
}

// Create a new transaction and add it into the list
MM_Txn* MM_TxnManager::Add(int iTxnId)
{
	MM_Txn* pTxn = new MM_Txn(iTxnId);
	if(pTxn)
		m_vTxn.push_back(pTxn);

	return pTxn;
}
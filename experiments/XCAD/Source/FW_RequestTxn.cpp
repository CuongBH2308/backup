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
#include "fw_requesttxn.h"
#include "mm_txnmanager.h"
#include "mm_txn.h"

FW_RequestTxn::FW_RequestTxn(FW_Document* pDoc)
:FW_Request(pDoc)
{
}

FW_RequestTxn::~FW_RequestTxn(void)
{
}

HRESULT FW_RequestTxn::Execute()
{
	MM_Txn* pTxn = MM_TxnManager::Get()->Add();
	MM_TxnManager::Get()->StartTxn(pTxn);

	HRESULT hr = OnExecute();

	MM_TxnManager::Get()->EndTxn();
	return hr;
}
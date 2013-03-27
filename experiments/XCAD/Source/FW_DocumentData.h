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

class FW_Document;
class GR_DLNode;
class SL_Storage;
class SL_StreamObj;
class DR_Fragment;
class FW_DocumentData
{
public:
	FW_DocumentData(FW_Document* pDoc);
	virtual ~FW_DocumentData();

	enum EStream
	{
		eDL,
		eDR
	};

	// Initialize. Create:
	// 1. Root DL Node
	// 2. Fragment
	void Init();

	// Get the root storage
	SL_Storage*		GetStorage();

	// Get stream
	SL_StreamObj*	GetStream(EStream eStream);

	// Get root node of the doc
	GR_DLNode*		GetDLNode() const;

	// Get fragment used to store st and ct
	DR_Fragment*	GetFragment() const;
private:
	// Document that owns the data package
	FW_Document* m_pDoc;

	// Root storage of the document
	SL_Storage* m_pStorage;

	// Root node of the scene
	GR_DLNode*	m_pDLNode;

	// Fragment used to store st and ct
	DR_Fragment* m_pFragment;
};

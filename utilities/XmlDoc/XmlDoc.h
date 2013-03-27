#pragma once

#include <list>
#include <string>

namespace std
{
	typedef basic_ostream<char, char_traits<char> > ostream;
}

// This is a very simple xml write utility which only consists of 2 classes: XmlDoc, XmlNode
// 1. Take care of the encoding yourself - It will accept everything you give using a char* string
// 2. Charaters like <, > are escaped
// 
// How to use:
// XmlDoc doc;
// XmlNode* rootNode = doc.CreateRootNode("RootNode");
// rootNode->AddAttribute("count", 2);
// rootNode->AddNode("SubNode1");
// rootNode->AddNode("SubNode2");
// doc.SaveAs("C:\\test.xml");
//
//////////////////////////////////////////////////////////////////////////
class XmlNode
{
	friend class XmlDoc;

public:
	XmlNode(const char* name, const char* content): nodeName_(name), leftChild_(NULL), rightSibling_(NULL)
	{ 
		if(content) nodeContent_ = content;
	}

	// Add a new sub node
	XmlNode* AddNode(const char* name);

	// BFS find using the tag name, the first one find will be returned!
	// Use it at your own risk!
	XmlNode* FindNode(const char* name);


	// overload for basic types
	XmlNode* AddNode(const char* name, const char* content);
	XmlNode* AddNode(const char* name, bool content);
	XmlNode* AddNode(const char* name, int content);
	XmlNode* AddNode(const char* name, double content);


	// overload for basic types
	void AddAttribute(const char* name, const char* value);
	void AddAttribute(const char* name, bool value);
	void AddAttribute(const char* name, int value);
	void AddAttribute(const char* name, double value);

private:
	std::string nodeName_;
	std::string nodeContent_;

	XmlNode* leftChild_;
	XmlNode* rightSibling_;

	std::list<std::pair<std::string, std::string> > attributes_;

private:
	XmlNode* rightMost_;
};


class XmlDoc
{
public:
	// constructor for write xml
	XmlDoc():rootNode_(NULL){}

	~XmlDoc() { if(rootNode_) DeleteNode(rootNode_); }

	XmlNode* CreateRootNode(const char* name, const char* content = NULL);

	XmlNode* GetRootNode();

	XmlNode* FindNode(const char* name);

	template <class T>
	void Process(T processor);

	bool SaveAs(const char* fileName);

private:
	void SaveNode(std::ostream& xmlFile, XmlNode* pNode);

	// sort child nodes in criteria...
	void ProcessNode(XmlNode* pNode);

	void DeleteNode(XmlNode* pNode);

private:
	XmlNode* rootNode_;
};


template <class T>
void XmlDoc::Process(T processor)
{
	if(rootNode_)
	{
		this->ProcessNode(rootNode_, processor);
	}
}
#include "XmlDoc.h"

// std
#include <cassert>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>

using namespace std;

namespace
{
	// Replace special entities for node content and attribute value when write to xml files (< (&lt;) | > (&gt;) | & (&amp;) | ' (&apos;) | " (&quot;) )
	// I don't do it when add node and attribute (so I could do it latter in batch; so I don't need to transform when search a node)

	std::map<char, char*> init_escape_map()
	{
		std::map<char, char*> escapemap;

		escapemap['<'] = "&lt;";
		escapemap['>'] = "&gt;";
		escapemap['&'] = "&amp;";
		escapemap['\''] = "&apos;";
		escapemap['"'] = "&quot;";

		return escapemap;
	}

	// n * lg(m) ~= 2n = O(n)
	string escape_xml_predefined_charaters(const string& input)
	{
		string strOutput;

		static std::map<char, char*> escapemap = init_escape_map();

		size_t len = input.length();

		for(size_t i = 0; i < len; ++i)
		{
			if(escapemap.find(input[i]) != escapemap.end()) 
			{
				strOutput.append(escapemap[input[i]]);
			}
			else
			{
				strOutput.push_back(input[i]);
			}
		}

		return strOutput;
	}
}

//////////////////////////////////////////////////////////////////////////
// XmlNode
//////////////////////////////////////////////////////////////////////////
XmlNode* XmlNode::FindNode(const char* name)
{
	// Find the node by tag using BFS
	std::queue<XmlNode*> bfsQueue;
	bfsQueue.push(this);

	while(!bfsQueue.empty())
	{
		XmlNode* pCurNode = bfsQueue.front();
		bfsQueue.pop();

		if(pCurNode->nodeName_ == name) return pCurNode;

		XmlNode* pChildNode = pCurNode->leftChild_;

		while (pChildNode)
		{
			// no "visited" mark required as a node will only visited once in a tree
			bfsQueue.push(pChildNode);
			pChildNode = pChildNode->rightSibling_;
		}
	}

	return NULL;
}

XmlNode* XmlNode::AddNode(const char* name)
{
	const char* nullp = NULL;
	return AddNode(name, nullp);
}

XmlNode* XmlNode::AddNode(const char* name, const char* content)
{
	assert(name);
	XmlNode* pNode = new XmlNode(name, content);

	// insert as the last silbing
	if(this->leftChild_ == NULL)
		this->leftChild_ = pNode;
	else
		rightMost_->rightSibling_ = pNode;

	rightMost_ = pNode;

	return pNode;
}

XmlNode* XmlNode::AddNode(const char* name, bool content) // integers
{
	const char* boolText = content ? "true" : "false";
	return AddNode(name, boolText);
}

XmlNode* XmlNode::AddNode(const char* name, int content) // integers
{
	char buffer[100];
	sprintf(buffer, "%d", content);
	return AddNode(name, buffer);
}


XmlNode* XmlNode::AddNode(const char* name, double content) // float and double
{
	char buffer[100];
	sprintf(buffer, "%f", content);
	return AddNode(name, buffer);
}




void XmlNode::AddAttribute(const char* name, const char* value)
{
	assert(name && value);
	attributes_.push_back(std::make_pair(name, value));
}

void XmlNode::AddAttribute(const char* name, bool value) // boolean
{
	const char* boolText = value ? "true" : "false";
	AddAttribute(name, boolText);
}

void XmlNode::AddAttribute(const char* name, int value) // char*
{
	char buffer[100];
	sprintf(buffer, "%d", value);
	AddAttribute(name, buffer);
}

void XmlNode::AddAttribute(const char* name, double value) // char*
{
	char buffer[100];
	sprintf(buffer, "%f", value);
	AddAttribute(name, buffer);
}

//////////////////////////////////////////////////////////////////////////
// XmlDoc
//////////////////////////////////////////////////////////////////////////
XmlNode* XmlDoc::CreateRootNode(const char* name, const char* content)
{
	assert(NULL == rootNode_);

	rootNode_= new XmlNode(name, content);
	return rootNode_;
}

XmlNode* XmlDoc::FindNode(const char* name)
{
	if(!rootNode_) return NULL;

	return rootNode_->FindNode(name);
}

bool XmlDoc::SaveAs(const char* fileName)
{
	if(!rootNode_) return false;
	ostringstream xmlStream;

	xmlStream << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" << endl;
	SaveNode(xmlStream, rootNode_);


	ofstream xmlFile(fileName);
	// write all at once
	xmlFile << xmlStream.str();
	xmlFile.close();

	return true;
}

// collect all in a string, and then output it at once!
void XmlDoc::SaveNode(ostream& xmlStream, XmlNode* pNode)
{
	assert(pNode);

	static int level = -1;
	level++;

	bool hasChild = (NULL != pNode->leftChild_);
	bool hasContent = !pNode->nodeContent_.empty();

	// start tag
	string strIndent;
	if(level > 0) strIndent = string(level, '\t');
	xmlStream << strIndent << "<" << pNode->nodeName_;

	// attributes
	for(std::list<std::pair<std::string, std::string> >::const_iterator it = pNode->attributes_.begin();
		it != pNode->attributes_.end();
		++it)
	{
		xmlStream << " " << it->first << "=" << '"' << escape_xml_predefined_charaters(it->second) << '"';
	}

	// it is a simple leaf node, just use the simplified tag
	if(!hasChild && !hasContent)
	{
		xmlStream << "/>" << endl;
	}
	else
	{
		if(!hasChild && hasContent)
		{
			xmlStream << ">";
			xmlStream << escape_xml_predefined_charaters(pNode->nodeContent_);
			xmlStream << "<" << "/" << pNode->nodeName_ << ">" << endl;
		}
		else
		{
			xmlStream << ">" << endl;

			// content
			if(hasContent)
				xmlStream << '\t' << strIndent << escape_xml_predefined_charaters(pNode->nodeContent_) << endl;
		

			// sub nodes - DFS
			XmlNode* pChildNode = pNode->leftChild_;

			while(NULL != pChildNode)
			{
				SaveNode(xmlStream, pChildNode);
				pChildNode = pChildNode->rightSibling_;
			}

			// end tag
			xmlStream << strIndent << "<" << "/" << pNode->nodeName_ << ">" << endl;
		}

	}

	level--;
}

void XmlDoc::DeleteNode(XmlNode* pNode)
{
	assert(NULL != pNode);

	XmlNode* pChildNode = pNode->leftChild_;

	while(NULL != pChildNode)
	{
		XmlNode* pCurNode = pChildNode;
		pChildNode = pChildNode->rightSibling_; // move to next sibling first
		DeleteNode(pCurNode);
	}

	delete pNode;
}



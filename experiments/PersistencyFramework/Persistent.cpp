// Design.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#pragma warning( disable :4333) // warning C4333: '>>' : right shift by too large amount, data loss

// Root class
// Write, Read: classid (2 byte)
// map<id, creator>
// 1. nested objects(no id);  
// 2. referenced object(use index in object list and then fix ptrs)
// 3. each object has a pointer to document: problem!

// TODO:
// 1. Comment
// 2. Code style

char space = ' ';

class Document;
class Object
{
public:
	virtual void writeid(ofstream& s) = 0;
	virtual void write(ofstream& s) = 0;
	virtual void read(ifstream& s) = 0;
	virtual void fixPtrs(){} // not every class needs fix pointers
};

typedef unsigned short uint16_t;
typedef unsigned short uint32_t;
typedef Object* (*CreatorFunc)();
map<uint16_t, CreatorFunc> creatormap;

class CreatorRegister
{
public:
	CreatorRegister(uint16_t id, CreatorFunc creator){creatormap[id] = creator;}
};

#define DECLARE_PERSISTENT(objid)		\
	virtual void writeid(ofstream& s);	\
	static Object* CreateObject();		\
	static const uint16_t objectid = objid;	

#define IMPLEMENT_PERSISTENT(clsname)										\
	void clsname::writeid(ofstream& s) { s << objectid << space; }			\
	Object* clsname::CreateObject(){ return new clsname(); }				\
	CreatorRegister clsname##reg(clsname::objectid, clsname::CreateObject);

typedef vector<Object*> ObjectList;

class Document
{
public:
	void load(const char* szFile)
	{
		ifstream ifs(szFile);
		while (!ifs.eof())
		{
			uint16_t id = get_objectid(ifs);

			if(creatormap.find(id) == creatormap.end())
				continue;
			Object* pObj = creatormap[id]();
			pObj->read(ifs);
			this->addObject(pObj);
		}

		for (ObjectList::iterator it = _vec.begin(); it != _vec.end(); ++it)
		{
			(*it)->fixPtrs();
		}


	}
	void save(const char* szFile)
	{
		ofstream of(szFile);
		for (ObjectList::iterator it = _vec.begin(); it != _vec.end(); ++it)
		{
			(*it)->writeid(of);
			(*it)->write(of);
		}
		of.close();
	}

	void addObject(Object* obj)
	{
		_vec.push_back(obj);
	}

	uint32_t get_index(Object* pObj)
	{
		if(pObj == NULL) return -1;
		ObjectList::iterator it = std::find(_vec.begin(), _vec.end(), pObj);
		return std::distance(_vec.begin(), it);
	}


	Object* get_object(uint32_t index)
	{
		if(index == -1) return NULL;
		return _vec[index];
	}

private:
	uint16_t get_objectid(ifstream& is)
	{
		uint16_t id(0);
		is >> id;
		return id;
	}

private:
	ObjectList _vec;
};


#define MAKE_INDEX(i1, i2) ((i1 << 24) & (i2 & 0x00ffffff))
#define DOC_INDEX(x) ((x >> 24) & 0x000000ff)
#define OBJ_INDEX(x) (x & 0x00ffffffff)
typedef vector<Document*> DocList;
class Application
{
public:
	static Application* Get()
	{
		static Application _instance;
		return &_instance;
	}

	void AddDoc(Document* pDoc)
	{
		_Docs.push_back(pDoc);
	}

	uint32_t get_index(Object* pObj)
	{
		uint32_t docIndex = -1;
		uint32_t objIndex = -1;

		for(DocList::iterator it = _Docs.begin(); it != _Docs.end(); ++it)
		{
			objIndex = (*it)->get_index(pObj);
			if(objIndex != -1)
			{
				docIndex = std::distance(_Docs.begin(), it);
				return MAKE_INDEX(docIndex, objIndex);
			}
		}
		return -1;

	}

	Object* get_object(uint32_t index)
	{
		uint32_t docIndex = DOC_INDEX(index);
		uint32_t objIndex = OBJ_INDEX(index);

		Document* pDoc = _Docs[docIndex];
		return pDoc->get_object(objIndex);
	}


private:
	DocList _Docs;
};



// Point
class Point: public Object
{
public:
	DECLARE_PERSISTENT(1)

	Point(float x, float y):_x(x), _y(y){}
	Point():_x(0.0f),_y(0.0f){}

	virtual void write(ofstream& s)
	{
		s << _x << space;
		s << _y << space;
	}

	virtual void read(ifstream& s)
	{
		s >> _x;
		s >> _y;
	}

private:
	float _x;
	float _y;

};

IMPLEMENT_PERSISTENT(Point)



// Circle
class Circle: public Object
{
public:
	DECLARE_PERSISTENT(2)

	Circle(const Point& pt, float radius):_pt(pt),_radius(radius){};
	Circle():_radius(0.0f){}

	virtual void write(ofstream& s)
	{
		_pt.write(s);
		s << _radius << space;
	}

	virtual void read(ifstream& s)
	{
		_pt.read(s);
		s >> _radius;
	}

private:
	Point _pt;
	float _radius;
};
IMPLEMENT_PERSISTENT(Circle)

class DoubleCircle: public Object
{
public:
	DECLARE_PERSISTENT(3)

	DoubleCircle():_pc1(NULL), _pc2(NULL), _index1(-1), _index2(-1){}

	void setCircle1(Circle* pc1){_pc1 = pc1;}
	void setCircle2(Circle* pc2){_pc2 = pc2;}

public:
	virtual void write(ofstream& s)
	{
		s << Application::Get()->get_index(_pc1) << space;
		s << Application::Get()->get_index(_pc2) << space;
	}

	virtual void read(ifstream& s)
	{
		s >> _index1;
		s >> _index2;
	}

	virtual void fixPtrs()
	{
		_pc1 = dynamic_cast<Circle*>(Application::Get()->get_object(_index1));
		_pc2 = dynamic_cast<Circle*>(Application::Get()->get_object(_index2));
	}

private:
	Circle* _pc1; int _index1;
	Circle* _pc2; int _index2;
};
IMPLEMENT_PERSISTENT(DoubleCircle)



int _tmain(int argc, _TCHAR* argv[])
{
	// Save
	Document d;

	Application::Get()->AddDoc(&d);

	Point pt1(100, 200);
	d.addObject(new Circle(pt1, 50));

	d.addObject(new Point(15, 54));

	Point pt2(10, 45);
	d.addObject(new Circle(pt2, 3));

	DoubleCircle* pDC = new DoubleCircle();
	Circle* pC1 = new Circle(pt1, 13.3f);
	Circle* pC2 = new Circle(pt2, 16.3f);
	pDC->setCircle1(pC1);
	pDC->setCircle2(pC2);

	d.addObject(pDC);
	d.addObject(pC1);
	d.addObject(pC2);



	d.save("C:\\test.txt");

	// Load
	Document d2;
	Application::Get()->AddDoc(&d2);
	d2.load("C:\\test.txt");
	d2.save("C:\\test2.txt");


	return 0;
}


#pragma once
#include "Geometry.h"
#include <list> // use slist instead?
#include <map>
#include <fstream>

struct octnode
{
	octnode(octnode* p):parent(p)
	{
		memset(children, 0, sizeof(children));
	}
	octnode* parent;
	octnode* children[8];

	int depth;
	cube boundingbox;
	list<int> triangeindexes;
};


class octree
{
public:
	octree(triangle* input, int num):arrTriangles(input), numOfTriangles(num){}

	void Build(float loosefactor = 1.0);

	void Intersect(const ray& r, vector<point3d>& intersectionNodes);

private:
	void Subdivide(octnode* parentNode);
	void BuildNode(octnode*& thisNode,  int which, octnode* parentNode);
	void Intersect(const ray& r, octnode* pNode, vector<point3d>& intersectionNodes);

private:
	octnode* topNode;
	triangle* arrTriangles;
	int numOfTriangles;

	map<int, vector3d> centerDirs;

private:
	static const int MAX_TRIANGLE = 5; //divide until there are less than 10 triangles in a node


public:
#ifdef _DEBUG
	ofstream oTree;
	void DumpTree();
	void DumpNode(octnode* pNode);
#endif
};
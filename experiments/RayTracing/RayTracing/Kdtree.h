#pragma once
#if 0
#include "Geometry.h"
#include <list>

enum EDimension {kX = 0, kY = 1, kZ = 2};
struct kdnode
{
	// Filled when build node
	box boundingBox;
	list<int> triangeIndexes;

	// Filled when subdivide node
	EDimension splittingDim;
	float splittingValue;
	kdnode* leftNode;
	kdnode* rightNode;
};

class kdtree
{
public:
	kdtree(triangle* input, int num):arrTriangles(input), numOfTriangles(num){}

	void Build();

	void Intersect(const ray& r, vector<point3d>& intersectionNodes);

private:
	void Subdivide(kdnode* parentNode);
	kdnode* BuildNode(kdnode* parentNode, EDimension& splittingDim, float& splitingValue, bool bLeft);

	void ChooseSplit(kdnode* node, EDimension& splittingDim, float& splitingValue);
	float CalculateCost(kdnode* node, EDimension& splittingDim, float splitPos);



	void Intersect(const ray& r, kdnode* pNode, vector<point3d>& intersectionNodes);


private:
	kdnode* topnode;
	triangle* arrTriangles;
	int numOfTriangles;

	static const int MAX_TRIANGLE = 5; //divide until there are less than 10 triangles in a node

};
#endif
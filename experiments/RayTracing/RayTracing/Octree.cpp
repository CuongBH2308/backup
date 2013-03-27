#include "octree.h"

void octree::Build(float loosefactor/* = 1.0*/)
{
	// Build Top node
	topNode = new octnode(NULL);
	topNode->depth = 0;
	float halfsize = 0.0;
	for(int i = 0; i < numOfTriangles; i++)
	{
		topNode->triangeindexes.push_back(i); // store indexes
		if(halfsize < fabs(arrTriangles[i].v0.x)) halfsize = fabs(arrTriangles[i].v0.x);
		if(halfsize < fabs(arrTriangles[i].v0.y)) halfsize = fabs(arrTriangles[i].v0.y);
		if(halfsize < fabs(arrTriangles[i].v0.z)) halfsize = fabs(arrTriangles[i].v0.z);
		if(halfsize < fabs(arrTriangles[i].v1.x)) halfsize = fabs(arrTriangles[i].v1.x);
		if(halfsize < fabs(arrTriangles[i].v1.y)) halfsize = fabs(arrTriangles[i].v1.y);
		if(halfsize < fabs(arrTriangles[i].v1.z)) halfsize = fabs(arrTriangles[i].v1.z);
		if(halfsize < fabs(arrTriangles[i].v2.x)) halfsize = fabs(arrTriangles[i].v2.x);
		if(halfsize < fabs(arrTriangles[i].v2.y)) halfsize = fabs(arrTriangles[i].v2.y);
		if(halfsize < fabs(arrTriangles[i].v2.z)) halfsize = fabs(arrTriangles[i].v2.z);
	}

	topNode->boundingbox.center = point3d(0,0,0);
	topNode->boundingbox.halfsize = halfsize * loosefactor;

	// Could be optimized here:

	centerDirs[0] = vector3d(1,1,1);
	centerDirs[1] = vector3d(1,1,-1);
	centerDirs[2] = vector3d(1,-1,1);
	centerDirs[3] = vector3d(1,-1,-1);
	centerDirs[4] = vector3d(-1,1,1);
	centerDirs[5] = vector3d(-1,1,-1);
	centerDirs[6] = vector3d(-1,-1,1);
	centerDirs[7] = vector3d(-1,-1,-1);

	for (int i = 0; i < 8; i++)
	{
		BuildNode(topNode->children[i], i, topNode);
	}

	// Build octree, recursively
	#pragma omp parallel for num_threads(8)
	for (int i = 0; i < 8; i++)
	{
		Subdivide(topNode->children[i]);
	}
}

// RVO? if not, use reference as a parameter directly
void octree::Intersect(const ray& r, vector<point3d>& intersectionNodes)
{
	return Intersect(r, topNode, intersectionNodes);
}

// ray doesn't intersect with cube
// ray does intersect with triangles in the cube
// triangles are inside the cube
void octree:: Intersect(const ray& r, octnode* pNode, vector<point3d>& intersectionNodes)
{
	if(RayIntersectWithCube(r, pNode->boundingbox))
	{
		if (pNode->triangeindexes.size() > 0)
		{
			list<int>::iterator itBegin = pNode->triangeindexes.begin();
			list<int>::iterator itEnd = pNode->triangeindexes.end();
			for (list<int>::iterator it = itBegin; it != itEnd; it++)
			{
				point3d p;
				if(RayTriangleIntersection(r, arrTriangles[*it], p))
				{
				//	bool b1 = TriInCube(arrTriangles[*it], pNode->boundingbox);
					intersectionNodes.push_back(p);
				}
			}
		}

		// optimize here: no need to judge all 8 nodes
		if(pNode->children[0] != NULL)
		{
			for (int i = 0; i < 8; i++)
			{
				Intersect(r, pNode->children[i], intersectionNodes);
			}
		}
	}
}


void octree::Subdivide(octnode* parentNode)
{
	if (parentNode->triangeindexes.size() > MAX_TRIANGLE) // maybe you need depth control as well
	{
		for (int i = 0; i < 8; i++)
		{
			BuildNode(parentNode->children[i], i, parentNode);
			Subdivide(parentNode->children[i]);
		}
	}
}

void  octree::BuildNode(octnode*& thisNode, int which, octnode* parentNode)
{
	thisNode = new octnode(parentNode);
	thisNode->depth = parentNode->depth + 1;
	thisNode->boundingbox.halfsize = parentNode->boundingbox.halfsize / 2.0f;
	thisNode->boundingbox.center = parentNode->boundingbox.center + thisNode->boundingbox.halfsize * centerDirs[which];

	list<int>::iterator itBegin = parentNode->triangeindexes.begin();
	list<int>::iterator itEnd = parentNode->triangeindexes.end();
	for (list<int>::iterator it = itBegin; it != itEnd; )
	{
		if (TriInCube(arrTriangles[*it], thisNode->boundingbox))
		{
			thisNode->triangeindexes.push_back(*it);
			parentNode->triangeindexes.erase(it++);
		}
		else
			it++;
	}

}


#ifdef _DEBUG
ofstream oTree;
void octree::DumpTree()
{
	oTree.open("C:\\treelist.txt");
	DumpNode(topNode);
	oTree.close();
}
void octree::DumpNode(octnode* pNode)
{
	// Indent
	string strLine;
	for (int d = 0; d < pNode->depth; d++)
	{
		strLine.append("  ");
	}
	char temp[256];
	sprintf(temp, "%d", pNode->depth);
	strLine.append("Node");
	strLine.append(temp);
	strLine.append("(");
	sprintf(temp, "%d", pNode->triangeindexes.size());
	strLine.append("Triangles:");
	strLine.append(temp);
	strLine.append(")");
	sprintf(temp, "(%5.2f,%5.2f,%5.2f), size = %5.2f", pNode->boundingbox.center.x,pNode->boundingbox.center.y,pNode->boundingbox.center.z,pNode->boundingbox.halfsize);
	strLine.append(temp);
	strLine.append("\n");

	oTree << strLine.c_str();
	//printf(strLine.c_str());


	for (int i = 0; i < 8; i++)
	{
		octnode* subNode = pNode->children[i];
		if (subNode)
		{
			DumpNode(subNode);
		}
	}
}
#endif
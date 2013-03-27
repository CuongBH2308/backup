#include "Kdtree.h"

#if 0
void kdtree::Build()
{
	// Build Top node
	topnode = new kdnode;
	float halfsize(0.0);
	for(int i = 0; i < numOfTriangles; i++)
	{
		topnode->triangeIndexes.push_back(i); // store indexes
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

	topnode->boundingBox.minV = point3d(halfsize, halfsize, halfsize);
	topnode->boundingBox.maxV = point3d(-halfsize, -halfsize, -halfsize);


	Subdivide(topnode);

}

void kdtree::Subdivide(kdnode *parentNode)
{
	if (parentNode->triangeIndexes.size() > MAX_TRIANGLE ) // maybe you need depth control as well
	{
		EDimension splittingDim;
		float splittingValue;

		ChooseSplit(parentNode, splittingDim, splittingValue);
		parentNode->splittingDim = splittingDim;
		parentNode->splittingValue = splittingValue;

		// build left node
		kdnode* pLeftNode = BuildNode(parentNode, splittingDim, splittingValue, true);
		parentNode->leftNode = pLeftNode;
		Subdivide(pLeftNode);

		// build right node
		kdnode* pRightNode = BuildNode(parentNode, splittingDim, splittingValue, false);
		parentNode->rightNode = pRightNode;
		Subdivide(pRightNode);
	}
}

float kdtree::CalculateCost(kdnode* node, EDimension& splittingDim, float splitPos)
{
	//
	float leftarea;
	point3d ptMax = node->boundingBox.maxV;
	point3d ptMin = node->boundingBox.minV;

	float totalarea = 2 * (ptMax.x - ptMin.x) * (ptMax.y - ptMin.y) * (ptMax.z - ptMin.z);
	float portion = (splitPos - ptMin.cell[splittingDim]) / (ptMax.cell[splittingDim] - ptMin.cell[splittingDim]);

	float leftarea = totalarea * portion;
	float rightarea = totalarea * (1 - portion);

	int leftcount = 0;
	int rightcount = 0;
	for (list<int>::iterator it = node->triangeIndexes.begin(); it != node->triangeIndexes.end(); it++)
	{
		if(arrTriangles[*it].v0.cell[splittingDim] < splitPos && arrTriangles[*it].v1.cell[splittingDim] < splitPos && arrTriangles[*it].v2.cell[splittingDim] < splitPos)
		{
			leftcount++;
		}

		if(arrTriangles[*it].v0.cell[splittingDim] > splitPos && arrTriangles[*it].v1.cell[splittingDim] > splitPos && arrTriangles[*it].v2.cell[splittingDim] > splitPos)
		{
			rightcount++;
		}
	}

	
	//return costtrav + costintersect * (leftarea * leftcount + rightarea * rightcount)

}

float getleftmost(triangle& tri, EDimension axis)
{
	float leftmost = tri.v0.cell[axis] < tri.v1.cell[axis] ? tri.v0.cell[axis] : tri.v1.cell[axis];
	leftmost = leftmost < tri.v2.cell[axis] ? leftmost : tri.v2.cell[axis];
	return leftmost;
}

float getrightmost(triangle& tri, EDimension axis)
{
	float rightmost = tri.v0.cell[axis] > tri.v1.cell[axis] ? tri.v0.cell[axis] : tri.v1.cell[axis];
	rightmost = rightmost > tri.v2.cell[axis] ? rightmost : tri.v2.cell[axis];
	return rightmost;
}

void kdtree::ChooseSplit(kdnode* node, EDimension& splittingDim, float& splitingValue)
{
	// get the splitting axis
	vector3d s = node->boundingBox.maxV - node->boundingBox.minV;
	if ((s.x >= s.y) && (s.x >= s.z)) splittingDim = kX;
	else if ((s.y >= s.x) && (s.y >= s.z)) splittingDim = kY;
	else splittingDim = kZ;

	// 
	float bestpos = -1;
	float bestcost = 100000;
	for (list<int>::iterator it = node->triangeIndexes.begin(); it != node->triangeIndexes.end(); it++)
	{
		triangle& tri = arrTriangles[*it];
		float leftmost = getleftmost(tri, splittingDim);
		float rightmost = getrightmost(tri, splittingDim);
		
		float cost;
		if (cost = CalculateCost( leftmost ) < bestcost)
		{
			bestcost = cost;
			bestpos = leftmost;
		}
		if (cost = CalculateCost( rightmost ) < bestcost)
		{
			bestcost = cost;
			bestpos = rightmost;
		}
	}

	splitingValue = bestpos;

}
kdnode* kdtree::BuildNode(kdnode* parentNode, EDimension& splittingDim, float& splitingValue, bool bLeft)
{
	kdnode* pSubNode = new kdnode;
	
	// File bounding box & triangle index
	point3d ptMax = parentNode->boundingBox.maxV;
	point3d ptMin = parentNode->boundingBox.minV;
	list<int>& triangeIndexes = parentNode->triangeIndexes;


	switch(splittingDim)
	{
	case kX:
		{
			if (bLeft) // left means negative; right means postive
			{
				pSubNode->boundingBox.maxV = point3d(splitingValue, ptMax.y, ptMax.z);
				pSubNode->boundingBox.minV = ptMin;

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.x < splitingValue && arrTriangles[*it].v1.x < splitingValue && arrTriangles[*it].v2.x < splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
			else
			{
				pSubNode->boundingBox.maxV = ptMax; 
				pSubNode->boundingBox.minV = point3d(splitingValue, ptMax.y, ptMax.z);

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.x > splitingValue && arrTriangles[*it].v1.x > splitingValue && arrTriangles[*it].v2.x > splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
		}
		break;
	case kY:
		{
			if (bLeft) // left means negative; right means postive
			{
				pSubNode->boundingBox.maxV = point3d(ptMax.x, splitingValue, ptMax.z);
				pSubNode->boundingBox.minV = ptMin;

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.y < splitingValue && arrTriangles[*it].v1.y < splitingValue && arrTriangles[*it].v2.y < splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
			else
			{
				pSubNode->boundingBox.maxV = ptMax; 
				pSubNode->boundingBox.minV = point3d(ptMax.x, splitingValue, ptMax.z);

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.y > splitingValue && arrTriangles[*it].v1.y > splitingValue && arrTriangles[*it].v2.y > splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
		}
		break;

	case kZ:
		{
			if (bLeft) // left means negative; right means postive
			{
				pSubNode->boundingBox.maxV = point3d(ptMax.x, ptMax.y, splitingValue);
				pSubNode->boundingBox.minV = ptMin;

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.z < splitingValue && arrTriangles[*it].v1.z < splitingValue && arrTriangles[*it].v2.z < splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
			else
			{
				pSubNode->boundingBox.maxV = ptMax; 
				pSubNode->boundingBox.minV = point3d(ptMax.x, ptMax.y, splitingValue);

				for (list<int>::iterator it = triangeIndexes.begin(); it != triangeIndexes.end(); it++)
				{
					if(arrTriangles[*it].v0.z > splitingValue && arrTriangles[*it].v1.z > splitingValue && arrTriangles[*it].v2.z > splitingValue)
					{
						pSubNode->triangeIndexes.push_back(*it);
						triangeIndexes.erase(it);
					}
				}
			}
		}
		break;

	default:;

	}

	return pSubNode;
}
#endif
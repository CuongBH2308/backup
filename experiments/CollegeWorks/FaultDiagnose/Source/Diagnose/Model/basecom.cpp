#include "basecom.h"

//BOOL PtOnLine(long x, long y, long x1, long y1, long x2, long y2);
BOOL PtOnLine(CPoint point, CPoint start, CPoint end);

IMPLEMENT_DYNAMIC(CBaseCom, CObject)
//IMPLEMENT_DYNAMIC(IBaseCom, CObject)

//根据x计算坐标y
long CalY(long xStart, long yStart, long xEnd, long yEnd, long x)
{
	if ( x == xEnd )	//先判断end，以免出现x=c情况的直线方程
		return yEnd;

	if ( x == xStart )
		return yStart;
		
	if ( xEnd == xStart )	//在x=c方程的情况下，点(x,y)不在直线上
		//if ( x == xEnd )
		return -1;

	if ( yEnd == yStart )	//y=c的方程
		return yStart;

	long y = 0;
	y = yStart+(long)((double)((x-xStart)*(yEnd-yStart))/(double)(xEnd-xStart));
	return y;
}

//根据y计算坐标x
long CalX(long xStart, long yStart, long xEnd, long yEnd, long y)
{
	if ( y == yStart )
		return xStart;
	if ( y == yEnd )
		return xEnd;
	
	long x = 0;
	return x;
}
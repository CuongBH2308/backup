#include "basecom.h"

//BOOL PtOnLine(long x, long y, long x1, long y1, long x2, long y2);
BOOL PtOnLine(CPoint point, CPoint start, CPoint end);

IMPLEMENT_DYNAMIC(CBaseCom, CObject)
//IMPLEMENT_DYNAMIC(IBaseCom, CObject)

//����x��������y
long CalY(long xStart, long yStart, long xEnd, long yEnd, long x)
{
	if ( x == xEnd )	//���ж�end���������x=c�����ֱ�߷���
		return yEnd;

	if ( x == xStart )
		return yStart;
		
	if ( xEnd == xStart )	//��x=c���̵�����£���(x,y)����ֱ����
		//if ( x == xEnd )
		return -1;

	if ( yEnd == yStart )	//y=c�ķ���
		return yStart;

	long y = 0;
	y = yStart+(long)((double)((x-xStart)*(yEnd-yStart))/(double)(xEnd-xStart));
	return y;
}

//����y��������x
long CalX(long xStart, long yStart, long xEnd, long yEnd, long y)
{
	if ( y == yStart )
		return xStart;
	if ( y == yEnd )
		return xEnd;
	
	long x = 0;
	return x;
}
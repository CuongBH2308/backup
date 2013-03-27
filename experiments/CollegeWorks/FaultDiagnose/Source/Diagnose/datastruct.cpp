#include "datastruct.h"

#define MAX_DISTANCE 3		//����������λ�þ����߶ε�������С�ڸ�ֵ������Ϊ��������


enum MouseAction actionflag = NOTHING;	//��궯��
ModelObject * current_active_com = NULL;			//��¼��ǰ�����com�������½�
BOOL mousemoving = FALSE;							//����Ƿ����ƶ�������
BOOL mousedown = FALSE;								//����Ƿ���£�������δ�ͷ�
unsigned long delete_layer1 = 0;
unsigned long delete_layer2 = 0;


IMPLEMENT_DYNAMIC(GraphInfo, CObject)
IMPLEMENT_DYNAMIC(ModelObject, CObject);
IMPLEMENT_DYNAMIC(Node, CObject);
IMPLEMENT_DYNAMIC(Line, CObject);
IMPLEMENT_DYNAMIC(Node1, CObject);
IMPLEMENT_DYNAMIC(Line1, CObject);

//////////////////////////////////////////////////////
//GraphInfo��ʵ��
GraphInfo::GraphInfo()
{
	/*
	LOGFONT logFont;
	logFont.lfHeight=0;
	logFont.lfWidth=0;
	logFont.lfEscapement=0;
	logFont.lfOrientation=0;
	logFont.lfWeight=FW_NORMAL;
	logFont.lfItalic=0;
	logFont.lfUnderline=0;
	logFont.lfStrikeOut=0;
	logFont.lfCharSet=GB2312_CHARSET;
	logFont.lfOutPrecision=OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	logFont.lfQuality=PROOF_QUALITY;
	logFont.lfPitchAndFamily=VARIABLE_PITCH|FF_ROMAN;
	strcpy(logFont.lfFaceName,"����");	//fontName);
	font.CreateFontIndirect(&logFont);

	pointsize = 100;
	
	normal_linecolor = RGB(210, 210, 210);
	active_linecolor = RGB(100, 100, 100);
	//normal_regioncolor = RGB(230,230,230);
	normal_regioncolor = RGB(255,0,0);
	//active_regioncolor = RGB(249,232,120);
	active_regioncolor = RGB(0,0,0);
	textcolor = RGB(210, 210, 210);

	normal_linewidth = 1;
	active_linewidth = 1;
	normal_penStyle = PS_SOLID;
	active_penStyle = PS_DOT;
	normal_brushStyle =	active_brushStyle = HS_CROSS;
	*/
	
	LOGFONT logFont;
	logFont.lfHeight=-13;	//0;
	logFont.lfWidth=0;
	logFont.lfEscapement=0;
	logFont.lfOrientation=0;
	logFont.lfWeight=400;	//FW_NORMAL;
	logFont.lfItalic=0;
	logFont.lfUnderline=0;
	logFont.lfStrikeOut=0;
	logFont.lfCharSet=GB2312_CHARSET;
	logFont.lfOutPrecision=3;	//OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision=2;	//CLIP_DEFAULT_PRECIS;
	logFont.lfQuality=1;	//PROOF_QUALITY;
	logFont.lfPitchAndFamily=2;	//VARIABLE_PITCH|FF_ROMAN;
	strcpy(logFont.lfFaceName,"����");	//fontName);
	font.CreateFontIndirect(&logFont);

	pointsize = 100;
	
	normal_linecolor = RGB(210, 210, 210);
	active_linecolor = RGB(100, 100, 100);
	//normal_regioncolor = RGB(230,230,230);
	normal_regioncolor = RGB(255,0,0);
	//active_regioncolor = RGB(249,232,120);
	active_regioncolor = RGB(0,0,0);
	textcolor = RGB(210, 210, 210);

	normal_linewidth = 1;
	active_linewidth = 1;
	normal_penStyle = PS_SOLID;
	active_penStyle = PS_DOT;
	normal_brushStyle =	active_brushStyle = HS_CROSS;
}


void GraphInfo::InitGraphInfo()
{
	LOGFONT logFont;
	logFont.lfHeight=-13;	//0;
	logFont.lfWidth=0;
	logFont.lfEscapement=0;
	logFont.lfOrientation=0;
	logFont.lfWeight=400;	//FW_NORMAL;
	logFont.lfItalic=0;
	logFont.lfUnderline=0;
	logFont.lfStrikeOut=0;
	logFont.lfCharSet=GB2312_CHARSET;
	logFont.lfOutPrecision=3;	//OUT_DEFAULT_PRECIS;
	logFont.lfClipPrecision=2;	//CLIP_DEFAULT_PRECIS;
	logFont.lfQuality=1;	//PROOF_QUALITY;
	logFont.lfPitchAndFamily=2;	//VARIABLE_PITCH|FF_ROMAN;
	strcpy(logFont.lfFaceName,"����");	//fontName);
	font.DeleteObject();
	font.CreateFontIndirect(&logFont);

	pointsize = 100;
	
	normal_linecolor = RGB(210, 210, 210);
	active_linecolor = RGB(100, 100, 100);
	//normal_regioncolor = RGB(230,230,230);
	normal_regioncolor = RGB(255,0,0);
	//active_regioncolor = RGB(249,232,120);
	active_regioncolor = RGB(0,0,0);
	textcolor = RGB(210, 210, 210);

	normal_linewidth = 1;
	active_linewidth = 1;
	normal_penStyle = PS_SOLID;
	active_penStyle = PS_DOT;
	normal_brushStyle =	active_brushStyle = HS_CROSS;
}


//��������
void GraphInfo::SetFont(LOGFONT logFont)
{
	font.DeleteObject();
	font.CreateFontIndirect(&logFont);
}

void GraphInfo::SetFont(CFont f)
{
	LOGFONT logFont;
	f.GetLogFont(&logFont);
	font.DeleteObject();
	font.CreateFontIndirect(&logFont);
}

void GraphInfo::SetGraphInfo(GraphInfo & gi)
{
	if ( this == &gi )
		return;

	pointsize = gi.pointsize;
	normal_linecolor = gi.normal_linecolor;
	normal_regioncolor = gi.normal_regioncolor;
	active_linecolor = gi.active_linecolor;
	active_regioncolor = gi.active_regioncolor;
	textcolor = gi.textcolor;

	normal_linewidth = gi.normal_linewidth;
	active_linewidth = gi.active_linewidth;
	normal_penStyle = gi.normal_penStyle;
	active_penStyle = gi.active_penStyle;
	normal_brushStyle =	gi.normal_brushStyle;
	active_brushStyle = gi.active_brushStyle;

	font.DeleteObject();
	LOGFONT logFont;
	gi.font.GetLogFont(&logFont);
	font.CreateFontIndirect(&logFont);
}

void GraphInfo::SetGraphInfo(GraphInfo * pgi)
{
	if ( pgi == this )
		return ;

	pointsize = pgi->pointsize;
	normal_linecolor = pgi->normal_linecolor;
	normal_regioncolor = pgi->normal_regioncolor;
	active_linecolor = pgi->active_linecolor;
	active_regioncolor = pgi->active_regioncolor;
	textcolor = pgi->textcolor;

	normal_linewidth = pgi->normal_linewidth;
	active_linewidth = pgi->active_linewidth;
	normal_penStyle = pgi->normal_penStyle;
	active_penStyle = pgi->active_penStyle;
	normal_brushStyle =	pgi->normal_brushStyle;
	active_brushStyle = pgi->active_brushStyle;
	
	font.DeleteObject();
	LOGFONT logFont;
	pgi->font.GetLogFont(&logFont);
	font.CreateFontIndirect(&logFont);
}

///////////////////////////////////////////////////////////////////
//node��ʵ��
///////////////////////////////////////////////////////////////////

BOOL Node::PtInRgn(CPoint point)
{
	BOOL f = FALSE;
	pCom->PtInRgn((unsigned long)&point, (unsigned long)&f);
	return f;
}

BOOL Node::InOtherRect(CRect rect, float scale)
{
	BOOL f;
	pCom->InOtherRect((unsigned long)&rect, scale, (unsigned long)&f);
	return f;
}

BOOL Node::InOtherRgn(CRgn * rgn, float scale)
{
	BOOL f;
	pCom->InOtherRgn((unsigned long)rgn, scale, (unsigned long)&f);
	return f;
}

//����scrollpos��startPoint����ȥm_topleft, m_scrollpos��Ȼ�󻭳����
void Node::Draw(CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
				GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	m_scrollpos = ScrollPos;
	m_topleft = StartPoint;

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->Draw((unsigned long)m_pDC, (unsigned long)&m_topleft, m_Scale,
				(unsigned long)pGraphInfo, m_scale_flag, m_active_flag);
}

void Node::DrawOffset(CDC * m_pDC, CPoint offset, CPoint ScrollPos, double m_Scale,
					GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	//m_topleft.Offset(offset);
	CPoint xy;
	xy.x = offset.x + m_scrollpos.x - ScrollPos.x;
	xy.y = offset.y + m_scrollpos.y - ScrollPos.y;
	m_topleft.Offset(xy);
	/*
	CPoint old_topleft;
	pCom->GetTopLeft((unsigned long)&old_topleft);
	OffsetRgn(CPoint(m_topleft.x-old_topleft.x, m_topleft.y-old_topleft.y));
	*/
	m_scrollpos = ScrollPos;

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->DrawOffset((unsigned long)m_pDC, (unsigned long)&xy, m_Scale, (unsigned long)pGraphInfo, m_scale_flag, m_active_flag);
}

void Node::GetBottomCenter(CPoint & point)
{
	pCom->GetBottomCenter((unsigned long)&point);
}

void Node::GetTopCenter(CPoint & point)
{
	pCom->GetTopCenter((unsigned long)&point);
}

void Node::OffsetRgn(CPoint offset)
{
	m_topleft.Offset(offset);
	pCom->OffsetRgn((unsigned long)&offset);
}

///////////////////////////////////////////////////////////////////////////////
//line ��ʵ��
///////////////////////////////////////////////////////////////////////////////

BOOL Line::PtInRgn(CPoint point)
{
	BOOL f = FALSE;
	pCom->PtInRgn((unsigned long)&point, (unsigned long)&f);
	return f;
}

void Line::SetStartPoint(CPoint point)
{
	pCom->SetStartPoint((unsigned long)&point);
}

void Line::SetEndPoint(CPoint point)
{
	pCom->SetEndPoint((unsigned long)&point);
}

void Line::Draw(CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
				GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	//����
	m_scrollpos = ScrollPos;
	m_topleft = StartPoint;
	
	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->Draw((unsigned long)m_pDC, NULL, m_Scale,
				(unsigned long)pGraphInfo, m_scale_flag, m_active_flag);
}

void Line::DrawOffset(CDC * m_pDC, CPoint offset, CPoint ScrollPos, double m_Scale,
					GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	CPoint xy;
	xy.x = offset.x + m_scrollpos.x - ScrollPos.x;
	xy.y = offset.y + m_scrollpos.y - ScrollPos.y;

	pCom->OffsetRgn((unsigned long)&xy);
	m_topleft.Offset(xy);
	m_scrollpos = ScrollPos;

	/*
	CPoint old_topleft;
	pCom->GetTopLeft((unsigned long)&old_topleft);
	OffsetRgn(CPoint(m_topleft.x-old_topleft.x, m_topleft.y-old_topleft.y));
	*/

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->DrawOffset((unsigned long)m_pDC, NULL, m_Scale,
					(unsigned long)pGraphInfo, m_scale_flag, m_active_flag);
}


BOOL Line::InOtherRect(CRect rect, float scale)
{
	BOOL f;
	pCom->InOtherRect((unsigned long)&rect, scale, (unsigned long)&f);
	return f;
}

BOOL Line::InOtherRgn(CRgn * rgn, float scale)
{
	BOOL f;
	pCom->InOtherRect((unsigned long)rgn, scale, (unsigned long)&f);
	return f;
}
/*
void Line::GetBottomCenter(CPoint & point)
{
	pCom->GetBottomCenter((unsigned long)&point);
}

void Line::GetTopCenter(CPoint & point)
{
	pCom->GetTopCenter((unsigned long)&point);
}
*/

void Line::OffsetRgn(CPoint offset)
{
	m_topleft.Offset(offset);
	pCom->OffsetRgn((unsigned long)&offset);
}



///////////////////////////////////////////////////////////////////
//Node1��ʵ��
///////////////////////////////////////////////////////////////////

BOOL Node1::PtInRgn(CPoint point)
{
	BOOL f = FALSE;
	pCom->PtInRgn((unsigned long)&point, (unsigned long)&f);
	return f;
}

BOOL Node1::InOtherRect(CRect rect, float scale)
{
	BOOL f;
	pCom->InOtherRect((unsigned long)&rect, scale, (unsigned long)&f);
	return f;
}

BOOL Node1::InOtherRgn(CRgn * rgn, float scale)
{
	BOOL f;
	pCom->InOtherRgn((unsigned long)rgn, scale, (unsigned long)&f);
	return f;
}

//����scrollpos��startPoint����ȥm_topleft, m_scrollpos��Ȼ�󻭳����
void Node1::Draw(CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
				GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	m_scrollpos = ScrollPos;
	m_topleft = StartPoint;

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->Draw((unsigned long)m_pDC, (unsigned long)&m_topleft, m_Scale,
				(unsigned long)pGraphInfo, 0, m_active_flag);
}

void Node1::DrawOffset(CDC * m_pDC, CPoint offset, CPoint ScrollPos, double m_Scale,
					GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	//m_topleft.Offset(offset);
	CPoint xy;
	xy.x = offset.x + m_scrollpos.x - ScrollPos.x;
	xy.y = offset.y + m_scrollpos.y - ScrollPos.y;
	m_topleft.Offset(xy);
	/*
	CPoint old_topleft;
	pCom->GetTopLeft((unsigned long)&old_topleft);
	OffsetRgn(CPoint(m_topleft.x-old_topleft.x, m_topleft.y-old_topleft.y));
	*/
	m_scrollpos = ScrollPos;

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->DrawOffset((unsigned long)m_pDC, (unsigned long)&xy, m_Scale,
					(unsigned long)pGraphInfo, 0, m_active_flag);
}

void Node1::GetLeftCenter(CPoint & point)
{
	pCom->GetLeftCenter((unsigned long)&point);
}

void Node1::GetRightCenter(CPoint & point)
{
	pCom->GetRightCenter((unsigned long)&point);
}

void Node1::OffsetRgn(CPoint offset)
{
	m_topleft.Offset(offset);
	pCom->OffsetRgn((unsigned long)&offset);
}


//�������ض���;�ĺ���
void Node1::SetFromNode(Node * node)
{
	if ( node == NULL )
		return ;

	ignored = node->IsIgnored();
	deleted = FALSE;
	SetID(node->GetID());
	SetName(node->GetName());
	comment = node->comment;
	SetGraphInfo(&(node->m_GraphInfo));

	m_topleft.x = m_scrollpos.x = 0;
	m_topleft.y = m_scrollpos.y = 0;
}


///////////////////////////////////////////////////////////////////////////////
//Line1 ��ʵ��
///////////////////////////////////////////////////////////////////////////////

BOOL Line1::PtInRgn(CPoint point)
{
	BOOL f = FALSE;
	pCom->PtInRgn((unsigned long)&point, (unsigned long)&f);
	return f;
}

void Line1::SetStartPoint(CPoint point)
{
	pCom->SetStartPoint((unsigned long)&point);
}

void Line1::SetEndPoint(CPoint point)
{
	pCom->SetEndPoint((unsigned long)&point);
}

void Line1::Draw(CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
				GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	//����
	m_scrollpos = ScrollPos;
	m_topleft = StartPoint;
	
	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->Draw((unsigned long)m_pDC, NULL, m_Scale,
				(unsigned long)pGraphInfo, 0, m_active_flag);
}

void Line1::DrawOffset(CDC * m_pDC, CPoint offset, CPoint ScrollPos, double m_Scale,
					GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag )
{
	CPoint xy;
	xy.x = offset.x + m_scrollpos.x - ScrollPos.x;
	xy.y = offset.y + m_scrollpos.y - ScrollPos.y;

	pCom->OffsetRgn((unsigned long)&xy);
	m_topleft.Offset(xy);
	m_scrollpos = ScrollPos;

	/*
	CPoint old_topleft;
	pCom->GetTopLeft((unsigned long)&old_topleft);
	OffsetRgn(CPoint(m_topleft.x-old_topleft.x, m_topleft.y-old_topleft.y));
	*/

	if ( pGraphInfo != NULL )
	{
		m_GraphInfo.SetGraphInfo(pGraphInfo);
	}

	pCom->DrawOffset((unsigned long)m_pDC, NULL, m_Scale,
					(unsigned long)pGraphInfo, 0, m_active_flag);
}


BOOL Line1::InOtherRect(CRect rect, float scale)
{
	BOOL f;
	pCom->InOtherRect((unsigned long)&rect, scale, (unsigned long)&f);
	return f;
}

BOOL Line1::InOtherRgn(CRgn * rgn, float scale)
{
	BOOL f;
	pCom->InOtherRgn((unsigned long)rgn, scale, (unsigned long)&f);
	return f;
}

/*
void Line1::GetBottomCenter(CPoint & point)
{
	pCom->GetBottomCenter((unsigned long)&point);
}

void Line1::GetTopCenter(CPoint & point)
{
	pCom->GetTopCenter((unsigned long)&point);
}
*/

void Line1::OffsetRgn(CPoint offset)
{
	m_topleft.Offset(offset);
	pCom->OffsetRgn((unsigned long)&offset);
}


////////////////////////////////////////////////////////////////////////
#include <math.h>
const double PI=3.1415926535;
const int minidistance=2;	//��̾���.�ڴ˾���֮�ڱ�ʾ����.

//���������ľ���
double CalDisp(long x1,long y1,long x2,long y2)
{
	return sqrt(double((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

//����㵽ֱ�ߵľ���
//(xx,yy)�ǵ�����.(x1,y1),(x2,y2)��ʾֱ����������.
long PointToLine(long xx,long yy,long x1,long y1,long x2,long y2)
{
	double a,b,c,ang1,ang2,ang;
	a=CalDisp(x1,y1,xx,yy); if(a==0.0) return 0;
	b=CalDisp(x2,y2,xx,yy); if(b==0.0) return 0;
	c=CalDisp(x1,y1,x2,y2);
	//cout<<a<<"	"<<b<<"	"<<c<<"\n";
	//���(x1,y1)��(x2,y2)��һ����,���߶�Ϊһ����,ֱ�ӷ��ؾ���.
	if (c==0.0) return (unsigned long)a;
	if (a<b)
	{
		if (y1==y2)
		{
			if(x1<x2)
				ang1=0;
			else
				ang1=PI;
		}
		else
		{
			ang1=acos((x2-x1)/c);
			if(y2>y1) ang1=PI*2-ang1;	//(x1,y1)��(x2,y2)�ļн�.
		}
		ang2=acos((xx-x1)/a);	//(x1,y1)��(xx,yy)�ļн�.
		if(yy>y1)	ang2=PI*2-ang2;
		ang=ang2-ang1;
		if(ang<0) ang=-ang;
		if(ang>PI) ang=PI*2-ang;
		if(ang>PI/2) return 1000000;//���Ǵ���ľ���,������������.
		else
			return (unsigned long)(a*sin(ang));
	}
	else
	{
		if (y1==y2)
		{
			if(x1<x2)
				ang1=PI;
			else
				ang1=0;
		}
		else
		{
			ang1=acos((x1-x2)/c);
			if(y1>y2) ang1=PI*2-ang1;	//(x2,y2)��(x1,y1)�ļн�.
		}
		ang2=acos((xx-x2)/b);
		if(yy>y2) ang2=PI*2-ang2;	//(x2,y2)��(xx,yy)�ļн�.
		ang=ang2-ang1;
		if(ang<0) ang=-ang;
		if(ang>PI) ang=PI*2-ang;
		if(ang>PI/2) return 1000000;
		else
			return (unsigned long)(b*sin(ang));
	}
}

/*
//�жϵ�xy,�Ƿ����߶�x1y1,x2y2��
BOOL PtOnLine(long x, long y, long x1, long y1, long x2, long y2)
{
	//�ж�xx,yy�Ƿ����߶�x1,y1; x2,y2֮��
	if ( (x>x1)&&(x>x2) || (x<x1)&&(x<x2) || (y>y1)&&(y>y2) || (y<y1)&&(y<y2) )
		return FALSE;

	long dis = PointToLine(x, y, x1, y1, x2, y2);
	if ( dis > MAX_DISTANCE )
		return FALSE;
	else
		return TRUE;
}
*/

BOOL PtOnLine(CPoint point, CPoint start, CPoint end)
{
	//�ж�xx,yy�Ƿ����߶�x1,y1; x2,y2֮��
	if ( (point.x>start.x)&&(point.x>end.x) || (point.x<start.x)&&(point.x<end.x)
		|| (point.y>start.y)&&(point.y>end.y) || (point.y<start.y)&&(point.y<end.y) )
		return FALSE;

	long dis = PointToLine(point.x, point.y, start.x, start.y, end.x, end.y);
	if ( dis > MAX_DISTANCE )
		return FALSE;
	else
		return TRUE;
}


////////////////////////////////////////////////////////////////////////
//�������Ϣ

/*
��    ���� NODES_Table
�������壺 ������������з�����Ͻ��Ļ�����Ϣ��

������
����		node->GetID()
�����
�������
���		node->layer;
�������  
������	node->inline->parentNode->GetID()
�������	node->GetName()
�ڵ���������	node->GetName()
�������	node->comment
X����		node->GetTopLeft().x + node->GetScrPos().x
Y����		node->GetTopLeft().y + node->GetScrPos().y
ͼ����״
ͼ������
ͼ���߿�
����		m_model_scale
ͼ����ɫ	
����
�ֺ�
������ɫ  
�������  
�����ɫ  
��������  
������־
ɾ����־	node->IsDeleted();



��    ���� LINE_Table
�������壺 ������������н������ӹ�ϵ��

�������	line->GetID()
���ߺ�	
�����	
�������	
������	line->parentNode->GetID()
���������	
�������	line->parentNode->layer
�������к�	
�ӽ���	line->sonNode->GetID()
�ӽ������	
�ӽ����	line->sonNode->layer
�ӽ����к�	
��������	line->GetName()
������������	
��������	line->comment;
�������X	line->parentNode->GetBottomCenter().x+line->parentNode->GetScrPos().x
�������Y	line->parentNode->GetBottomCenter().y+line->parentNode->GetScrPos().y
�����յ�X	line->sonNode->GetTopCenter().x+line->sonNode->GetScrPos().x
�����յ�Y	line->sonNode->GetTopCenter().y+line->sonNode->GetScrPos().y
��������	line->m_GraphInfo.normal_penStyle
���߿��	line->m_GraphInfo.normal_linewidth
������ɫ	line->m_GraphInfo.normal_linecolor
��ͷ����	
������־	
ɾ����־	line->IsDeleted()

*/


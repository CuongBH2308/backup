#if !defined DATASTRUCT
#define DATASTRUCT

#define ULONGPNT(x) ((unsigned long)& x)	//ȡ��ַ�ĺ�
#define MAXTREE	10000

#include "stdafx.h"
#include "model\\model.h"

//���ݵĽṹ
typedef struct class_data
{
	char *type;		//���ݵ����ͣ���Ԫ����
	double value;	//���ݵ�ֵ
}class_data;
//���ݼ��ṹ
typedef struct class_dataset
{
	int data_num;
	class_data *datalist;
}class_dataset;

//��ɫ���������
class GraphInfo: public CObject
{
	DECLARE_DYNAMIC(GraphInfo);
public:
	COLORREF normal_linecolor;
	COLORREF active_linecolor;
	COLORREF normal_regioncolor;
	COLORREF active_regioncolor;
	COLORREF textcolor;
	INT pointsize;
	CFont font;

	unsigned char normal_linewidth;
	unsigned char active_linewidth;
	int normal_penStyle;	/*PS_SOLID|PS_DASH|PS_DOT|PS_DASHDOT|PS_DASHDOTDOT|PS_NULL|PS_INSIDEFRAME
							|PS_GEOMETRIC|PS_COSMETIC|PS_ALTERNATE|PS_USERSTYLE|PS_ENDCAP_ROUND
							|PS_ENDCAP_SQUARE|PS_ENDCAP_FLAT|PS_JOIN_BEVEL|PS_JOIN_MITER|PS_JOIN_ROUND*/
	int active_penStyle;
	int normal_brushStyle;	/*HS_BDIAGONAL|HS_CROSS|HS_DIAGCROSS|HS_FDIAGONAL|HS_HORIZONTAL|HS_VERTICAL	*/
	int active_brushStyle;

public:
	GraphInfo();
	//GraphInfo(COLORREF linecolor, COLORREF regioncolor, LOGFONT logFont);
	~GraphInfo(){font.DeleteObject();}
	//void SetLineColor(COLORREF lc){linecolor = lc;}
	//void SetRegionColor(COLORREF rc){regioncolor = rc;}
	void InitGraphInfo();
	void SetFont(LOGFONT logFont);
	void SetFont(CFont f);
	//void operator = (GraphInfo & gi);
	void SetGraphInfo(GraphInfo & gi);
	void SetGraphInfo(GraphInfo * pgi);
};

//��궯��
enum MouseAction {	NOTHING,	//�޶���
					NODE,		//������
					LINE,		//��������
					CLIP,		//��ѡ
					DRAG,		//�Ϸ�
					MOVE,		//һ�����λ���ƶ�����actionflag ��ΪMOVE
					NEW,		//�½����
					//SHIFT,	//shift�����
					CTRL,		//ctrl�����
					COPY		//ctrlѡ�н�㣬���϶�
				};
enum ObjectType {	MODELNODE,	//��ģ���Node��
					STATENODE,	//״̬���Node1��
					MODELLINE,	//��ģ�������Line��
					STATELINE	//״̬���ͽ�ģ���֮�������Line1��
				};

class ModelObject : public CObject
{
	DECLARE_DYNAMIC(ModelObject)
//public:
protected:
	IBaseCom * pCom;
	unsigned int deleted;
	BOOL ignored;		//��ʱû��̫�����;
	CPoint m_topleft;		//��ǰ��������
	CPoint m_scrollpos;		//��ǰ��������λ��
	
public:
	GraphInfo m_GraphInfo;
	unsigned long m_ID;
	CString m_Name;
	CString comment;	//˵��
	ObjectType type;	//�������

public:
	virtual unsigned int IsDeleted() = 0;
	virtual void SetDeleted(unsigned int f) = 0;
	virtual BOOL IsIgnored() = 0;
	virtual void SetIgnored(BOOL f) = 0;

	virtual IBaseCom * GetCom() = 0;
	virtual void SetCom(IBaseCom * com) = 0;

	//attribute setting
	virtual void SetID(unsigned long ID) = 0;
	virtual void SetName(CString name) = 0;
	virtual unsigned long GetID() = 0;
	virtual CString GetName() = 0;
	virtual void SetGraphInfo(GraphInfo * gi) = 0;
	virtual GraphInfo * GetGraphInfo() = 0;

	virtual BOOL GetActive() = 0;
	virtual void SetActive(BOOL f) = 0;

	//virtual void SetTopLeft(CPoint point) = 0;
	//virtual void SetScrPos(CPoint scrollpos) = 0;
	virtual CPoint GetTopLeft() = 0;
	virtual CPoint GetScrPos() = 0;

	//draw methods
	virtual BOOL PtInRgn(CPoint point) = 0;
	virtual BOOL InOtherRect(CRect rect, float scale) = 0;
	virtual BOOL InOtherRgn(CRgn * rgn, float scale) = 0;
	//virtual void GetBottomCenter(CPoint & point) = 0;
	//virtual void GetTopCenter(CPoint & point) = 0;
	virtual void OffsetRgn(CPoint offset) = 0;
	virtual void Draw(	CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
						GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag ) = 0;
	virtual void DrawOffset(CDC * m_pDC, CPoint Offset, CPoint ScrollPos, double m_Scale,
							GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag ) = 0;
};

class Line;
class Node : public ModelObject
{
	DECLARE_DYNAMIC(Node)
public:
	unsigned int layer;

	class_dataset NodeData;

	//Node * parentNode;
	//CTypedPtrArray <CObArray, Node *> sonNode;
	Line * inLine;
	CTypedPtrArray <CObArray, Line *> outLine;

	CString rgnName;	//������
	int rgnType;		//��������
	int point_count;	//����
	CPoint * Points;	//������

public:
	Node()
	{
		m_GraphInfo.InitGraphInfo();
		layer = 0;
		ignored = FALSE;
		deleted = FALSE;
		pCom = NULL;
		inLine = NULL;
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = MODELNODE;

		rgnName = "";
		rgnType = -1;
		point_count = 0;
		Points = NULL;
	}
	Node(IBaseCom * com)
	{
		m_GraphInfo.InitGraphInfo();

		layer = 0;
		ignored = FALSE;
		deleted = FALSE;
		pCom = com;
		if ( com != NULL )
		{
			GraphInfo gi;
			com->GetGraphInfo((unsigned long)&gi);
			m_GraphInfo.SetGraphInfo(gi);
		}
		inLine = NULL;
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = MODELNODE;

		rgnName = "";
		rgnType = -1;
		point_count = 0;
		Points = NULL;
	}
	~Node()
	{
		delete []Points;
		if ( pCom != NULL )
			pCom->Release();
	}
	virtual BOOL GetActive()
	{
		BOOL f = false;
		pCom->GetActive((unsigned long)&f);
		return f;
	}
	virtual void SetActive(BOOL f){pCom->SetActive(f);}
	virtual unsigned int IsDeleted(){return deleted;}
	virtual void SetDeleted(unsigned int f){deleted = f;}
	virtual BOOL IsIgnored(){return ignored;}
	virtual void SetIgnored(BOOL f){ignored = f;}

	virtual void SetID(unsigned long ID){m_ID=ID;pCom->SetID(ID);}
	virtual void SetName(CString name){m_Name=name;pCom->SetName((unsigned long)(LPCTSTR)name);}
	virtual unsigned long GetID(){return m_ID;}
	virtual CString GetName(){return m_Name;}

	virtual void SetGraphInfo(GraphInfo * gi)
	{
		m_GraphInfo.SetGraphInfo(gi);
		pCom->SetGraphInfo((unsigned long)gi);
	}
	virtual GraphInfo * GetGraphInfo()
	{
		//GraphInfo gi;
		//pCom->GetGraphInfo((unsigned long)&gi);
		//m_GraphInfo.SetGraphInfo(gi);
		return &m_GraphInfo;
	}
	
	virtual IBaseCom * GetCom(){return pCom;}
	virtual void SetCom(IBaseCom * com){pCom = com;}

	virtual void SetTopLeft(CPoint point){m_topleft=point;}
	virtual void SetScrPos(CPoint scrollpos){m_scrollpos=scrollpos;}
	virtual CPoint GetTopLeft(){return m_topleft;}
	virtual CPoint GetScrPos(){return m_scrollpos;}

	virtual BOOL PtInRgn(CPoint point);
	virtual BOOL InOtherRect(CRect rect, float scale);
	virtual BOOL InOtherRgn(CRgn * rgn, float scale);
	void GetBottomCenter(CPoint & point);
	void GetTopCenter(CPoint & point);
	virtual void OffsetRgn(CPoint offset);
	virtual void Draw(	CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
						GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );
	virtual void DrawOffset(CDC * m_pDC, CPoint Offset, CPoint ScrollPos, double m_Scale,
							GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );

};

class Line : public ModelObject
{
	DECLARE_DYNAMIC(Line)
public:
	Node * parentNode;
	Node * sonNode;

public:
	Line()
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		parentNode = NULL;
		sonNode = NULL;
		pCom = NULL;
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = MODELLINE;
	}
	Line(IBaseCom * com)
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		parentNode = NULL;
		sonNode = NULL;
		pCom = com;
		if ( com != NULL )
		{
			GraphInfo gi;
			com->GetGraphInfo((unsigned long)&gi);
			m_GraphInfo.SetGraphInfo(gi);
		}
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = MODELLINE;
	}
	~Line()
	{
		if ( pCom != NULL )
			pCom->Release();
	}

	virtual BOOL GetActive()
	{
		BOOL f = false;
		pCom->GetActive((unsigned long)&f);
		return f;
	}
	virtual void SetActive(BOOL f){pCom->SetActive(f);}
	virtual unsigned int IsDeleted(){return deleted;}
	virtual void SetDeleted(unsigned int f){deleted = f;}
	virtual BOOL IsIgnored(){return ignored;}
	virtual void SetIgnored(BOOL f){ignored = f;}

	virtual void SetID(unsigned long ID){m_ID=ID;pCom->SetID(ID);}
	virtual void SetName(CString name){m_Name=name;pCom->SetName((unsigned long)(LPCTSTR)name);}
	virtual unsigned long GetID(){return m_ID;}
	virtual CString GetName(){return m_Name;}

	virtual void SetGraphInfo(GraphInfo * gi)
	{
		m_GraphInfo.SetGraphInfo(gi);
		pCom->SetGraphInfo((unsigned long)gi);
	}
	virtual GraphInfo * GetGraphInfo(){return & m_GraphInfo;}

	virtual IBaseCom * GetCom(){return pCom;}
	virtual void SetCom(IBaseCom * com){pCom = com;}

	virtual void SetTopLeft(CPoint point){m_topleft=point;}
	virtual void SetScrPos(CPoint scrollpos){m_scrollpos=scrollpos;}
	virtual CPoint GetTopLeft(){return m_topleft;}
	virtual CPoint GetScrPos(){return m_scrollpos;}

	virtual BOOL PtInRgn(CPoint point);
	void SetStartPoint(CPoint point);
	void SetEndPoint(CPoint point);
	virtual BOOL InOtherRect(CRect rect, float scale);
	virtual BOOL InOtherRgn(CRgn * rgn, float scale);
	//virtual void GetBottomCenter(CPoint & point);
	//virtual void GetTopCenter(CPoint & point);
	virtual void OffsetRgn(CPoint offset);
	virtual void Draw(	CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
						GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );
	virtual void DrawOffset(CDC * m_pDC, CPoint Offset, CPoint ScrollPos, double m_Scale,
							GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );

};

class Line1;
class Node1 : public ModelObject
{
	DECLARE_DYNAMIC(Node1)
public:
	//Node * parentNode;
	//CTypedPtrArray <CObArray, Node1 *> sonNode;
	CTypedPtrArray <CObArray, Line1 *> inLine;
	CTypedPtrArray <CObArray, Line1 *> outLine;
	//fqz add
	double NormValue;
	double MinValue;
	double MaxValue;
public:
	Node1()
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		pCom = NULL;
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = STATENODE;
	}
	Node1(IBaseCom * com)
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		pCom = com;
		if ( com != NULL )
		{
			GraphInfo gi;
			com->GetGraphInfo((unsigned long)&gi);
			m_GraphInfo.SetGraphInfo(gi);
		}
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = STATENODE;
	}
	~Node1()
	{
		if ( pCom != NULL )
			pCom->Release();
	}

	virtual BOOL GetActive()
	{
		BOOL f = false;
		pCom->GetActive((unsigned long)&f);
		return f;
	}
	virtual void SetActive(BOOL f){pCom->SetActive(f);}
	virtual unsigned int IsDeleted(){return deleted;}
	virtual void SetDeleted(unsigned int f){deleted = f;}
	virtual BOOL IsIgnored(){return ignored;}
	virtual void SetIgnored(BOOL f){ignored = f;}

	virtual void SetID(unsigned long ID){m_ID=ID;pCom->SetID(ID);}
	virtual void SetName(CString name){m_Name=name;pCom->SetName((unsigned long)(LPCTSTR)name);}
	virtual unsigned long GetID(){return m_ID;}
	virtual CString GetName(){return m_Name;}

	virtual void SetGraphInfo(GraphInfo * gi)
	{
		m_GraphInfo.SetGraphInfo(gi);
		pCom->SetGraphInfo((unsigned long)gi);
	}
	virtual GraphInfo * GetGraphInfo(){return & m_GraphInfo;}
	
	virtual IBaseCom * GetCom(){return pCom;}
	virtual void SetCom(IBaseCom * com){pCom = com;}

	virtual void SetTopLeft(CPoint point){m_topleft=point;}
	virtual void SetScrPos(CPoint scrollpos){m_scrollpos=scrollpos;}
	virtual CPoint GetTopLeft(){return m_topleft;}
	virtual CPoint GetScrPos(){return m_scrollpos;}

	virtual BOOL PtInRgn(CPoint point);
	virtual BOOL InOtherRect(CRect rect, float scale);
	virtual BOOL InOtherRgn(CRgn * rgn, float scale);
	void GetLeftCenter(CPoint & point);
	void GetRightCenter(CPoint & point);
	virtual void OffsetRgn(CPoint offset);
	virtual void Draw(	CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
						GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );
	virtual void DrawOffset(CDC * m_pDC, CPoint Offset, CPoint ScrollPos, double m_Scale,
							GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );

	void SetFromNode(Node * node);	//����node��ֵ����node1��������

};

class Line1 : public ModelObject
{
	DECLARE_DYNAMIC(Line1)
public:
	Node1 * leftNode;
	Node1 * rightNode;

public:
	Line1()
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		leftNode = NULL;
		rightNode = NULL;
		pCom = NULL;
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = STATELINE;
	}
	Line1(IBaseCom * com)
	{
		m_GraphInfo.InitGraphInfo();
		ignored = FALSE;
		deleted = FALSE;
		leftNode = NULL;
		rightNode = NULL;
		pCom = com;
		if ( com != NULL )
		{
			GraphInfo gi;
			com->GetGraphInfo((unsigned long)&gi);
			m_GraphInfo.SetGraphInfo(gi);
		}
		comment = _T("");
		m_topleft.x = m_scrollpos.x = 0;
		m_topleft.y = m_scrollpos.y = 0;
		type = STATELINE;
	}
	~Line1()
	{
		if ( pCom != NULL )
			pCom->Release();
	}

	virtual BOOL GetActive()
	{
		BOOL f = false;
		pCom->GetActive((unsigned long)&f);
		return f;
	}
	virtual void SetActive(BOOL f){pCom->SetActive(f);}
	virtual unsigned int IsDeleted(){return deleted;}
	virtual void SetDeleted(unsigned int f){deleted = f;}
	virtual BOOL IsIgnored(){return ignored;}
	virtual void SetIgnored(BOOL f){ignored = f;}

	virtual void SetID(unsigned long ID){m_ID=ID;pCom->SetID(ID);}
	virtual void SetName(CString name){m_Name=name;pCom->SetName((unsigned long)(LPCTSTR)name);}
	virtual unsigned long GetID(){return m_ID;}
	virtual CString GetName(){return m_Name;}

	virtual void SetGraphInfo(GraphInfo * gi)
	{
		m_GraphInfo.SetGraphInfo(gi);
		pCom->SetGraphInfo((unsigned long)gi);
	}
	virtual GraphInfo * GetGraphInfo(){return & m_GraphInfo;}

	virtual IBaseCom * GetCom(){return pCom;}
	virtual void SetCom(IBaseCom * com){pCom = com;}

	virtual void SetTopLeft(CPoint point){m_topleft=point;}
	virtual void SetScrPos(CPoint scrollpos){m_scrollpos=scrollpos;}
	virtual CPoint GetTopLeft(){return m_topleft;}
	virtual CPoint GetScrPos(){return m_scrollpos;}

	virtual BOOL PtInRgn(CPoint point);
	void SetStartPoint(CPoint point);
	void SetEndPoint(CPoint point);
	virtual BOOL InOtherRect(CRect rect, float scale);
	virtual BOOL InOtherRgn(CRgn * rgn, float scale);
	//virtual void GetBottomCenter(CPoint & point);
	//virtual void GetTopCenter(CPoint & point);
	virtual void OffsetRgn(CPoint offset);
	virtual void Draw(	CDC * m_pDC, CPoint StartPoint, CPoint ScrollPos, double m_Scale,
						GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );
	virtual void DrawOffset(CDC * m_pDC, CPoint Offset, CPoint ScrollPos, double m_Scale,
							GraphInfo * pGraphInfo, BOOL m_scale_flag, BOOL m_active_flag );

};

//add by fqz
//ɾ���������ṹ��Ŀǰֻ�ܷ�һ�������
class DeleteArea : public CObject
{
public:
	int data_flag;	//1: line;  2:node
	int node_no_in_treeitem;
	ModelObject *pObject;
public:
	DeleteArea()
	{
		data_flag=0;
	}
	~DeleteArea(){};
};

class CMyBmp				//λͼ���õ���
{
public:
	CMyBmp(CString filename)
	{
		m_filename = filename;
		hBitmap = (HBITMAP) :: LoadImage(AfxGetInstanceHandle(), m_filename, IMAGE_BITMAP,
							0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION|LR_DEFAULTSIZE);
		if ( hBitmap != NULL )
		{
			m_cbitmap.Attach(hBitmap);
			m_cbitmap.GetBitmap(&bitmap);
		}
	}
	CString m_filename;
	HBITMAP hBitmap;
	CBitmap m_cbitmap;
	BITMAP bitmap;
	~CMyBmp()
	{
		if ( m_cbitmap.m_hObject != NULL )
			m_cbitmap.Detach();
	}
} ;

//��ʾ���ṹ
class TipShowData
{
public:
	int step_id;			//�����
	CString run_node_name;	//��ǰ���н����
	CString diagnose_type;  //�������
	long match_rule_id;		//��ǰƥ������
	CString out_node_name;	//��������
	CString rule_content;	//��������
	CString diagnose_result; //��Ͻ��
};


#endif
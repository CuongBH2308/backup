#pragma once

const UINT MAX_LEVEL = 3;
const UINT COLUMNWIDTH = 80;

struct ProfileItem
{
	ProfileItem()
	{
		strRoutineName = CString();
		dbTime = double();
		iHitCount = unsigned int();
		dbPercentage = double();
	}
	CString			strRoutineName;
	double			dbTime;
	unsigned int	iHitCount;
	double			dbPercentage;
};

class CDGItemHeaderCtrl: public CHeaderCtrl
{
	DECLARE_DYNAMIC(CDGItemHeaderCtrl)

public:
	CDGItemHeaderCtrl();
	virtual ~CDGItemHeaderCtrl();

	void SetValue(ProfileItem* pProfileData);

	virtual BOOL Create(UINT nLevel, UINT nIndent, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	UINT m_nLevel;
	UINT m_nIndent;
};
// CDGTreeCtrl

class CDGTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CDGTreeCtrl)

public:
	CDGTreeCtrl();
	virtual ~CDGTreeCtrl();

	virtual HTREEITEM InsertItem(ProfileItem* pProfileData, HTREEITEM hParent = TVI_ROOT);

	UINT GetItemLevel(HTREEITEM hItem);

protected:
	DECLARE_MESSAGE_MAP()

private:

};



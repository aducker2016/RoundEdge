#pragma once

#include <vector>

// CDialogDraw 对话框

class CDialogDraw : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDraw)

public:
	CDialogDraw(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogDraw();

// 对话框数据
	enum { IDD = IDD_DIALOG_DRAW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	std::vector<std::vector<int> > m_nodes;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();	
};


// RoundEdgeDlg.h : 头文件
//

#pragma once

#include "DialogDraw.h"

// CRoundEdgeDlg 对话框
class CRoundEdgeDlg : public CDialogEx
{
// 构造
public:
	CRoundEdgeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROUNDEDGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDialogDraw m_draw;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGenerate();
};

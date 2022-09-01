#include "ChartCtrl_source/ChartCtrl.h"		  //曲线基本设置头文件
#include "ChartCtrl_source/ChartTitle.h"	  //曲线标题设置头文件
#include "ChartCtrl_source/ChartBarSerie.h"	  //柱状图头文件
#include "ChartCtrl_source/ChartLineSerie.h"  //画线头文件
#include "ChartCtrl_source/ChartMouseListener.h"  //鼠标响应头文件
#include "ChartCtrl_source/ChartPointsSerie.h"
#include "ChartCtrl_source/ChartXYSerie.h"

// MFCDrawDlg.h: 头文件
//

#pragma once

// CMFCDrawDlg 对话框
class CMFCDrawDlg : public CDialogEx
{
// 构造
public:
	CMFCDrawDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

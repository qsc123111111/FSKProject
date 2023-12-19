
// FSKProjectDlg.h: 头文件
//
#include "SignalProcessing.h"


#include "Uxtheme.h"
#pragma comment(lib, "Uxtheme.lib")
#pragma once


// CFSKProjectDlg 对话框
class CFSKProjectDlg : public CDialogEx
{
// 构造
public:
	SignalProcessing mySignal;
	void Graph(float S[], float Frep[]);
	float findmax(float SS[], int K);           //在一个数组SS中找最大值，数组长K
	CFSKProjectDlg(CWnd* pParent = nullptr);	// 标准构造函数

	//变量定义   
	CString	stuID;            //学号
	int		noiseIntensity;       //噪音强度

	//常量定义
	const CString RECTANGLE_W = _T("矩形窗");
	const CString HANNING_W = _T("汉宁窗");
	const CString HAMING_W = _T("哈明窗");
	const CString BULAIKEMAN_W = _T("布莱克曼窗");

	const CString ASK = _T("ASK");
	const CString FSK = _T("FSK");
	const CString PSK = _T("PSK");


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FSKPROJECT_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBasesignal();
	afx_msg void OnBnClickedInputbutton();
	afx_msg void OnBnClickedLowfilter1();
	afx_msg void OnBnClickedModulate();
	afx_msg void OnBnClickedChannel();
	afx_msg void OnBnClickedNoise();
	afx_msg void OnBnClickedBandfilter();
	afx_msg void OnBnClickedDemodulate();
	afx_msg void OnBnClickedLowfilter2();
	afx_msg void OnBnClickedVerdict();
	CStatic inputText;
	CStatic outputText;
	afx_msg void OnBnClickedLowfrequencysampling1();
	afx_msg void OnBnClickedLowfrequencysampling2();
	afx_msg void OnBnClickedBandfrequencysampling();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedAutoanalysis();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedAutoanalysisp();
};

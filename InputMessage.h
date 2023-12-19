#pragma once
#include "afxdialogex.h"


// InputMessage 对话框

class InputMessage : public CDialogEx
{
	DECLARE_DYNAMIC(InputMessage)

public:
	InputMessage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InputMessage();
	CString	stuID;
	int	noiseIntensity;
	CString text1;
	CString text2;
	CString text3;

	//系统参数
	int samplingFrequency;		 //采样频率
	int carrierFrequency;		 //载波频率
	int symbolPeriod;			 //码元周期

	int filterOrder;              //滤波器阶数

	int asOfFrequency_LPF;		 //低通滤波器截至频率

	int  minimumFrequency_BPF;    //带通滤波器的截至频率(最小)
	int  maximumFrequency_BPF;    //带通滤波器的截至频率(最大)




// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_cbExamble1;
	CComboBox m_cbExamble2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_cbExamble3;
};

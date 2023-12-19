// InputMessage.cpp: 实现文件
//

#include "pch.h"
#include "FSKProject.h"
#include "afxdialogex.h"
#include "InputMessage.h"


// InputMessage 对话框

IMPLEMENT_DYNAMIC(InputMessage, CDialogEx)

InputMessage::InputMessage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

InputMessage::~InputMessage()
{
}

void InputMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_Intensity, noiseIntensity);
	DDX_Text(pDX, IDC_STUID1, stuID);

	DDX_Text(pDX, IDC_SamplingFrequency, samplingFrequency);
	DDX_Text(pDX, IDC_CarrierFrequency, carrierFrequency);
	DDX_Text(pDX, IDC_SymbolPeriod, symbolPeriod);

	DDX_Text(pDX, IDC_FilterOrder, filterOrder);

	DDX_Text(pDX, IDC_asOfFrequency_LPF, asOfFrequency_LPF);
	DDX_Text(pDX, IDC_minimumFrequency_BPF, minimumFrequency_BPF);
	DDX_Text(pDX, IDC_maximumFrequency_BPF, maximumFrequency_BPF);

	DDX_Text(pDX, IDC_CarrierFrequency2, carrierFrequency2);

	DDX_Control(pDX, IDC_COMBO2, m_cbExamble1);
	DDX_Control(pDX, IDC_COMBO3, m_cbExamble2);
	DDX_Control(pDX, IDC_COMBO1, m_cbExamble3);
	DDX_Control(pDX, IDC_COMBO4, m_cbExamble4);
}


void InputMessage::OnPaint() {

	CPaintDC   dc(this); // 创建一个绘图设备上下文
	CRect rect; // 定义客户区域矩形
	GetClientRect(&rect); // 获取对话框客户区域大小
	CDC   dcMem; // 定义内存设备上下文
	dcMem.CreateCompatibleDC(&dc); // 创建与当前设备兼容的内存设备上下文
	CBitmap   bmpBackground; // 定义背景图片位图对象
	bmpBackground.LoadBitmap(IDB_BITMAP1);  // 加载对话框的背景图片资源
	BITMAP   bitmap; // 定义位图参数结构体
	bmpBackground.GetBitmap(&bitmap); // 获取位图信息
	CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground); // 将bmpBackground对象选入内存设备上下文
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	// 在窗口客户区域中展示背景图片，StretchBlt函数是将指定坐标处的矩形区域的内容进行拉伸后显示



	SetWindowTheme(GetDlgItem(IDC_INPUT)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_SYSTEMPARAMETERS)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_PASSFILTER)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_LOWDESIGN)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_BANDDESIGN)->GetSafeHwnd(), L"", L"");

}

BEGIN_MESSAGE_MAP(InputMessage, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputMessage::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// InputMessage 消息处理程序


void InputMessage::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	int cindex1 = m_cbExamble1.GetCurSel(); // 获取选定项的序号
	m_cbExamble1.GetLBText(cindex1, text1); // 获取选定项的文本内容

	int cindex2 = m_cbExamble2.GetCurSel(); // 获取选定项的序号
	m_cbExamble2.GetLBText(cindex2, text2); // 获取选定项的文本内容

	int cindex3 = m_cbExamble3.GetCurSel();
	m_cbExamble3.GetLBText(cindex3, text3);
	
	int cindex4 = m_cbExamble4.GetCurSel();
	m_cbExamble4.GetLBText(cindex4, text4);

	CDialogEx::OnOK();
}


HBRUSH InputMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	if (pWnd->GetDlgCtrlID() == IDC_STUIDText || pWnd->GetDlgCtrlID() == IDC_IntensityText ||
		
		pWnd->GetDlgCtrlID() == IDC_STATIC
		
		)     //IDC_DEVICE_STAT为Static控件的ID
	{
		pDC->SetTextColor(RGB(0, 0, 0));    //设置控件字体颜色
		pDC->SetBkMode(TRANSPARENT);   //设置透明属性
		return (HBRUSH)GetStockObject(NULL_BRUSH);   //返回空画刷
	}




	if (pWnd->GetDlgCtrlID() == IDC_INPUT || pWnd->GetDlgCtrlID() == IDC_SYSTEMPARAMETERS ||
		pWnd->GetDlgCtrlID() == IDC_LOWDESIGN || pWnd->GetDlgCtrlID() == IDC_BANDDESIGN ||
		pWnd->GetDlgCtrlID() == IDC_PASSFILTER
		)
	{


		pDC->SetBkMode(TRANSPARENT);   //设置透明属性
		pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色


		return (HBRUSH)GetStockObject(NULL_BRUSH);   //返回空画刷
	
	}


	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

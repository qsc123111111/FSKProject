
// FSKProjectDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FSKProject.h"
#include "FSKProjectDlg.h"
#include "afxdialogex.h"
#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "InputMessage.h"
//#include "Parameter.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk) 
END_MESSAGE_MAP()


// CFSKProjectDlg 对话框
CFSKProjectDlg::CFSKProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FSKPROJECT_DIALOG, pParent)
{
	stuID = _T("");
	noiseIntensity = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFSKProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUTDISPLAY, inputText);
	DDX_Control(pDX, IDC_OUTPUTDISPLAY, outputText);
}

BEGIN_MESSAGE_MAP(CFSKProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFSKProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_INPUTBUTTON, &CFSKProjectDlg::OnBnClickedInputbutton)
	ON_BN_CLICKED(IDC_BASESIGNAL, &CFSKProjectDlg::OnBnClickedBasesignal)
	ON_BN_CLICKED(IDC_LOWFILTER1, &CFSKProjectDlg::OnBnClickedLowfilter1)
	ON_BN_CLICKED(IDC_MODULATE, &CFSKProjectDlg::OnBnClickedModulate)
	ON_BN_CLICKED(IDC_CHANNEL, &CFSKProjectDlg::OnBnClickedChannel)
	ON_BN_CLICKED(IDC_NOISE, &CFSKProjectDlg::OnBnClickedNoise)
	ON_BN_CLICKED(IDC_BANDFILTER, &CFSKProjectDlg::OnBnClickedBandfilter)
	ON_BN_CLICKED(IDC_DEMODULATE, &CFSKProjectDlg::OnBnClickedDemodulate)
	ON_BN_CLICKED(IDC_LOWFILTER2, &CFSKProjectDlg::OnBnClickedLowfilter2)
	ON_BN_CLICKED(IDC_VERDICT, &CFSKProjectDlg::OnBnClickedVerdict)
	ON_BN_CLICKED(IDC_LowFrequencySampling1, &CFSKProjectDlg::OnBnClickedLowfrequencysampling1)
	ON_BN_CLICKED(IDC_LowFrequencySampling2, &CFSKProjectDlg::OnBnClickedLowfrequencysampling2)
	ON_BN_CLICKED(IDC_BandFrequencySampling, &CFSKProjectDlg::OnBnClickedBandfrequencysampling)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_AUTOANALYSIS, &CFSKProjectDlg::OnBnClickedAutoanalysis)
	ON_BN_CLICKED(IDC_CLEAR, &CFSKProjectDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_AUTOANALYSISP, &CFSKProjectDlg::OnBnClickedAutoanalysisp)
END_MESSAGE_MAP()

// CFSKProjectDlg 消息处理程序

BOOL CFSKProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	stuID = "0195";
	noiseIntensity = 5;
	UpdateData(FALSE);

	SetWindowTheme(GetDlgItem(IDC_TRANSMITTER)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_LOWPASSFILTER1)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_BANDPASSFILTER)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_LOWPASSFILTER2)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_RECEIVER)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_TIMEDOMAIN)->GetSafeHwnd(), L"", L"");

	SetWindowTheme(GetDlgItem(IDC_FREQUENCYDOMAIN)->GetSafeHwnd(), L"", L"");
	SetWindowTheme(GetDlgItem(IDC_STATIC)->GetSafeHwnd(), L"", L"");
	

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFSKProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFSKProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();

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


	}
}

HCURSOR CFSKProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CFSKProjectDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

//信号传输过程的特性曲线
void CFSKProjectDlg::Graph(float S[], float Frep[])
{
	int M = mySignal.GetM();

	CWnd* pWnd = GetDlgItem(IDC_TIMEDOMAINDISPLAY);
	CDC* pDC = pWnd->GetDC();
	CRect rect;
	pWnd->GetClientRect(rect);
	int W = rect.Width();//画图区域宽度
	int H = rect.Height();//画图区域高度
	RedrawWindow();
	//设置背景色
	CBrush newbrush;
	newbrush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->Rectangle(rect);

	int StepX = int((W - 1) / (16 * M));
	double maxt = findmax(S, 16 * M);
	double StepY = (H / 2 - 20) / (fabs(maxt));//纵坐标步长

	//确定画图起始位置
	int ox = int((W - (16 * M) * StepX) / 20) + 22.5;
	int oyt = rect.bottom - int(H / 2);
	//画坐标
	CPen CoordinatePen, pen;
	CoordinatePen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->SelectObject(&CoordinatePen);
	pDC->MoveTo(rect.left, oyt);
	pDC->LineTo(rect.left + W, oyt);
	pDC->TextOut(ox + 10 * 2.6 - 5, oyt + 115, L"8");
	pDC->TextOut(ox + 30 * 2.6 - 5, oyt + 115, L"4");
	pDC->TextOut(ox + 50 * 2.6 - 5, oyt + 115, L"2");
	pDC->TextOut(ox + 70 * 2.6 - 5, oyt + 115, L"1");
	pDC->TextOut(ox + 90 * 2.6 - 5, oyt + 115, L"8");
	pDC->TextOut(ox + 110 * 2.6 - 5, oyt + 115, L"4");
	pDC->TextOut(ox + 130 * 2.6 - 5, oyt + 115, L"2");
	pDC->TextOut(ox + 150 * 2.6 - 5, oyt + 115, L"1");
	pDC->TextOut(ox + 170 * 2.6 - 5, oyt + 115, L"8");
	pDC->TextOut(ox + 190 * 2.6 - 5, oyt + 115, L"4");
	pDC->TextOut(ox + 210 * 2.6 - 5, oyt + 115, L"2");
	pDC->TextOut(ox + 230 * 2.6 - 5, oyt + 115, L"1");
	pDC->TextOut(ox + 250 * 2.6 - 5, oyt + 115, L"8");

	pDC->TextOut(ox + 270 * 2.6 - 5, oyt + 115, L"4");

	pDC->TextOut(ox + 290 * 2.6 - 5, oyt + 115, L"2");

	pDC->TextOut(ox + 310 * 2.6 - 5, oyt + 115, L"1");
	pDC->SelectObject(&pen);
	pDC->MoveTo(ox, oyt);
	for (int i = 0; i < (16 * M); i++)
	{
		//pDC->LineTo(ox + i * 1.6 * StepX, int(oyt - StepY * S[i]));
		pDC->LineTo(ox + i *1.3* StepX, int(oyt - StepY * S[i]));

	}

	//频谱图
	CWnd* pWnd1 = GetDlgItem(IDC_FREQUENCYDOMAINDISPLAY);
	CDC* pDC1 = pWnd1->GetDC();
	CRect rect1;
	pWnd1->GetClientRect(rect1);
	int W1 = rect1.Width();//画图区域宽度
	int H1 = rect1.Height();//画图区域高度
	CBrush newbrush1;
	newbrush1.CreateSolidBrush(RGB(255, 255, 255));
	pDC1->Rectangle(rect1);
	//坐标定位
	int StepX1 = int(2 * (W1 - 1) / (16 * M));//横坐标步长
	float maxt1 = findmax(Frep, int((16 * M) / 2));
	float StepY1 = (8 * H1 / 10) / (fabs(maxt1));//纵坐标步长
	//确定画图起始位置
	int oxf = int((W1 - (16 * M) * StepX1 / 2) / 2) - 15;
	int oyf = rect1.bottom - int(H1 / 10);
	CPen CoordinatePen1, pen1;
	CoordinatePen1.CreatePen(PS_SOLID, 1, RGB(0, 255, 0, ));
	pen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDC1->SelectObject(&CoordinatePen1);
	//画坐标
	pDC1->MoveTo(rect1.left, oyf);
	pDC1->LineTo(rect1.left + W1, oyf);
	pDC1->TextOut(oxf, oyf + 5, L"0");
	pDC1->TextOut((oxf + StepX1 * 16 * M / 2 - StepX1 * 3) / 2, oyf + 5, L"π/2");

	pDC1->TextOut(oxf + StepX1 * 16 * M / 2 - StepX1 * 3, oyf + 5, L"π");
	pDC1->SelectObject(&pen1);
	pDC1->MoveTo(oxf, oyf);
	for (int i = 0; i < (16 * M) / 2; i++)
	{
		pDC1->MoveTo(oxf + StepX1 * i, oyf);
		pDC1->LineTo(oxf + StepX1 * i, int(oyf - StepY1 * Frep[i]));
	}
}

//在一个数组SS中找最大值，数组长K
float CFSKProjectDlg::findmax(float SS[], int K)
{
	float A;
	A = SS[0];
	for (int i = 0; i < K; i++)
	{
		if (SS[i] >= A)
			A = SS[i];
	}
	return A;
}

//信息输入按钮
void CFSKProjectDlg::OnBnClickedInputbutton()
{
	InputMessage im;
	if (im.DoModal() == IDOK) {
		noiseIntensity = im.noiseIntensity;
		stuID = im.stuID;

		CString a = im.text1;
		CString b = im.text2;
		CString c = im.text3;

		int result = a.Compare(RECTANGLE_W);
		int result1 = a.Compare(HANNING_W);
		int result2 = a.Compare(HAMING_W);
		int result3 = a.Compare(BULAIKEMAN_W);

		if (result == 0) {
			mySignal.SetWindowFunction_LPF(0);
		}
		else if (result1 == 0) {
			mySignal.SetWindowFunction_LPF(2);
		}
		else if (result2 == 0) {
			mySignal.SetWindowFunction_LPF(1);
		}
		else if (result3 == 0) {
			mySignal.SetWindowFunction_LPF(3);
		}

		result = b.Compare(RECTANGLE_W);
		result1 = b.Compare(HANNING_W);
		result2 = b.Compare(HAMING_W);
		result3 = b.Compare(BULAIKEMAN_W);

		if (result == 0) {
			mySignal.SetWindowFunction_BPF(0);
		}
		else if (result1 == 0) {
			mySignal.SetWindowFunction_BPF(2);
		}
		else if (result2 == 0) {
			mySignal.SetWindowFunction_BPF(1);
		}
		else if (result3 == 0) {
			mySignal.SetWindowFunction_BPF(3);
		}

		result = c.Compare(ASK);
		result1 = c.Compare(FSK);
		result2 = c.Compare(PSK);

		if (result == 0) {
			mySignal.SetSelectModulation(0);  //ASK
		}
		else if (result1 == 0) {
			mySignal.SetSelectModulation(1);  //FSK

		}
		else if (result2 == 0) {
			mySignal.SetSelectModulation(2);  //PSK
		}

		CString strIntensity;
		strIntensity.Format(_T("%d"), noiseIntensity);

		inputText.SetWindowTextW(_T("学号：") + stuID + _T("    噪音强度：") + strIntensity
			+ _T("\n低通滤波器：") + a + _T("\n带通滤波器：") + b + _T("\n调制方式：") + c);

		mySignal.init(im.samplingFrequency, im.carrierFrequency, im.symbolPeriod, im.filterOrder, im.asOfFrequency_LPF, im.minimumFrequency_BPF, im.maximumFrequency_BPF);
	}
}

//基带信号按钮
void CFSKProjectDlg::OnBnClickedBasesignal()
{
	mySignal.SetSignal(_ttoi(stuID), noiseIntensity);
	mySignal.BaseBandSignal();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//低通滤波器按钮1：窗函数
void CFSKProjectDlg::OnBnClickedLowfilter1()
{
	mySignal.LPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//低通滤波器按钮1：频率采样
void CFSKProjectDlg::OnBnClickedLowfrequencysampling1()
{
	mySignal.LPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());

}

//调制按钮
void CFSKProjectDlg::OnBnClickedModulate()
{
	if (mySignal.GetSelectModulation() == 0) {
		mySignal.ASKModulate();
	}
	else if (mySignal.GetSelectModulation() == 1 ) {
		mySignal.FSKModulate();
	}
	else if (mySignal.GetSelectModulation() == 2) {
		mySignal.PSKModulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//信道按钮
void CFSKProjectDlg::OnBnClickedChannel()
{
	mySignal.Channel();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//噪音按钮
void CFSKProjectDlg::OnBnClickedNoise()
{
	mySignal.Noise(mySignal.GetNoiseIntensity());
	this->Graph(mySignal.GetNo(), mySignal.GetFDD());
}

//带通滤波器按钮：窗函数
void CFSKProjectDlg::OnBnClickedBandfilter()
{
	mySignal.BPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//带通滤波器按钮：频率采样
void CFSKProjectDlg::OnBnClickedBandfrequencysampling()
{
	mySignal.BPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//解调按钮
void CFSKProjectDlg::OnBnClickedDemodulate()
{
	if (mySignal.GetSelectModulation() == 0 || mySignal.GetSelectModulation() == 2) {
		mySignal.ASKDemodulate();
	}
	else if (mySignal.GetSelectModulation() == 1) {
		mySignal.FSKDemodulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());

}

//低通滤波器按钮2：窗函数
void CFSKProjectDlg::OnBnClickedLowfilter2()
{
	mySignal.LPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//低通滤波器按钮2：频率采样
void CFSKProjectDlg::OnBnClickedLowfrequencysampling2()
{
	mySignal.LPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
}

//恢复判决按钮
void CFSKProjectDlg::OnBnClickedVerdict()
{

	mySignal.Adjust();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	mySignal.Display();

	int* send = mySignal.GetS();
	int* receive = mySignal.GetH();

	int size = sizeof(receive) * 2;
	CString  sendSignal;
	CString receiveSignal;


	//误码判决
	int errorNumber = 0;   //误码数

	for (int i = 0; i < size; i++) {
		if (send[i] != receive[size - i - 1]) {
			errorNumber++;
		}
	}

	double ber = (double)errorNumber / 16 * 100; //误码率

	CString bitErrorsNumber;
	bitErrorsNumber.Format(_T("%d"), errorNumber);

	CString bitErrorsRate;
	bitErrorsRate.Format(_T("%.2f"), ber);

	for (int i = 0; i < size; i++) {

		sendSignal.AppendFormat(_T("%d "), send[i]);
	}

	for (int i = size - 1; i >= 0; i--) {

		receiveSignal.AppendFormat(_T("%d "), receive[i]);
	}
	outputText.SetWindowTextW(_T("发送信号：") + sendSignal +
		_T("\n接收信号：") + receiveSignal +
		_T("\n误码数：") + bitErrorsNumber +
		_T("\n误码率：") + bitErrorsRate + "%");
}

//自动分析按钮（窗函数）
void CFSKProjectDlg::OnBnClickedAutoanalysis()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	mySignal.SetSignal(_ttoi(stuID), noiseIntensity);
	mySignal.BaseBandSignal();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.LPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	if (mySignal.GetSelectModulation() == 0) {
		mySignal.ASKModulate();
	}
	else if (mySignal.GetSelectModulation() == 1) {
		mySignal.FSKModulate();
	}
	else if (mySignal.GetSelectModulation() == 2) {
		mySignal.PSKModulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.Channel();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.BPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	if (mySignal.GetSelectModulation() == 0 || mySignal.GetSelectModulation() == 2) {
		mySignal.ASKDemodulate();
	}
	else if (mySignal.GetSelectModulation() == 1) {
		mySignal.FSKDemodulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.LPF();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);


	//恢复判决
	mySignal.Adjust();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	mySignal.Display();

	int* send = mySignal.GetS();
	int* receive = mySignal.GetH();

	int size = sizeof(receive) * 2;
	CString  sendSignal;
	CString receiveSignal;


	//误码判决
	int errorNumber = 0;   //误码数

	for (int i = 0; i < size; i++) {
		if (send[i] != receive[size - i - 1]) {
			errorNumber++;
		}
	}

	double ber = (double)errorNumber / 16 * 100; //误码率

	CString bitErrorsNumber;
	bitErrorsNumber.Format(_T("%d"), errorNumber);

	CString bitErrorsRate;
	bitErrorsRate.Format(_T("%.2f"), ber);

	for (int i = 0; i < size; i++) {

		sendSignal.AppendFormat(_T("%d "), send[i]);
	}

	for (int i = size - 1; i >= 0; i--) {

		receiveSignal.AppendFormat(_T("%d "), receive[i]);
	}
	outputText.SetWindowTextW(_T("发送信号：") + sendSignal +
		_T("\n接收信号：") + receiveSignal +
		_T("\n误码数：") + bitErrorsNumber +
		_T("\n误码率：") + bitErrorsRate + "%");


}

//频率采样(自动分析)
void CFSKProjectDlg::OnBnClickedAutoanalysisp()
{
	mySignal.SetSignal(_ttoi(stuID), noiseIntensity);
	mySignal.BaseBandSignal();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.LPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	if (mySignal.GetSelectModulation() == 0) {
		mySignal.ASKModulate();
	}
	else if (mySignal.GetSelectModulation() == 1) {
		mySignal.FSKModulate();
	}
	else if (mySignal.GetSelectModulation() == 2) {
		mySignal.PSKModulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.Channel();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.BPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	if (mySignal.GetSelectModulation() == 0 || mySignal.GetSelectModulation() == 2) {
		mySignal.ASKDemodulate();
	}
	else if (mySignal.GetSelectModulation() == 1) {
		mySignal.FSKDemodulate();
	}
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);

	mySignal.LPFFS();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	Sleep(1000);


	//恢复判决
	mySignal.Adjust();
	this->Graph(mySignal.GetTDD(), mySignal.GetFDD());
	mySignal.Display();

	int* send = mySignal.GetS();
	int* receive = mySignal.GetH();

	int size = sizeof(receive) * 2;
	CString  sendSignal;
	CString receiveSignal;


	//误码判决
	int errorNumber = 0;   //误码数

	for (int i = 0; i < size; i++) {
		if (send[i] != receive[size - i - 1]) {
			errorNumber++;
		}
	}

	double ber = (double)errorNumber / 16 * 100; //误码率

	CString bitErrorsNumber;
	bitErrorsNumber.Format(_T("%d"), errorNumber);

	CString bitErrorsRate;
	bitErrorsRate.Format(_T("%.2f"), ber);

	for (int i = 0; i < size; i++) {

		sendSignal.AppendFormat(_T("%d "), send[i]);
	}

	for (int i = size - 1; i >= 0; i--) {

		receiveSignal.AppendFormat(_T("%d "), receive[i]);
	}
	outputText.SetWindowTextW(_T("发送信号：") + sendSignal +
		_T("\n接收信号：") + receiveSignal +
		_T("\n误码数：") + bitErrorsNumber +
		_T("\n误码率：") + bitErrorsRate + "%");
}

//清空按钮
void CFSKProjectDlg::OnBnClickedClear()
{

	CDialog dlg(IDD_DIALOG2);
	dlg.DoModal();   //

	// TODO: 在此添加控件通知处理程序代码
	inputText.SetWindowTextW(_T(""));
	outputText.SetWindowTextW(_T(""));

	//UpdateData(FALSE);

	RedrawWindow();

}

//设置格式
HBRUSH CFSKProjectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	if (pWnd->GetDlgCtrlID() == IDC_INPUTDISPLAY || pWnd->GetDlgCtrlID() == IDC_OUTPUTDISPLAY ||
		pWnd->GetDlgCtrlID() == IDC_TIMEDOMAINDISPLAY || pWnd->GetDlgCtrlID() == IDC_FREQUENCYDOMAINDISPLAY)  
	{
		pDC->SetTextColor(RGB(0, 0, 0));    //设置控件字体颜色
		pDC->SetBkMode(TRANSPARENT);		 //设置透明属性
		return (HBRUSH)GetStockObject(NULL_BRUSH); 
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC) {

		// 获取原有字体
		CFont* pFont = pWnd->GetFont();

		// 获取原有字体信息
		LOGFONT lf;
		pFont->GetLogFont(&lf);

		// 修改字体粗细
		lf.lfWeight = FW_BOLD;  // 加粗

		// 修改字体大小
		lf.lfHeight = 24;    // 字体大小（负值表示像素高度）

		// 创建新字体
		CFont font;
		font.CreateFontIndirect(&lf);

		

		pDC->SetTextColor(RGB(0, 0, 0));    //设置控件字体颜色
		pDC->SetBkMode(TRANSPARENT);   //设置透明属性

		// 设置字体
		CFont* pOldFont = pDC->SelectObject(&font);


		return (HBRUSH)GetStockObject(NULL_BRUSH);   //返回空画刷


		// 恢复原来的字体
		pDC->SelectObject(pOldFont);
	
	}

	if (pWnd->GetDlgCtrlID() == IDC_INPUTBUTTON) {


		pDC->SetBkMode(TRANSPARENT);   //设置透明属性
		pDC->SetTextColor(RGB(255, 0, 0));    //设置控件字体颜色
		return (HBRUSH)GetStockObject(NULL_BRUSH);

	}


	if (pWnd->GetDlgCtrlID() == IDC_TRANSMITTER || pWnd->GetDlgCtrlID() == IDC_LOWPASSFILTER1 ||
		pWnd->GetDlgCtrlID() == IDC_BANDPASSFILTER|| pWnd->GetDlgCtrlID() == IDC_LOWPASSFILTER2 ||
		pWnd->GetDlgCtrlID() == IDC_RECEIVER || pWnd->GetDlgCtrlID() == IDC_TIMEDOMAIN||
		pWnd->GetDlgCtrlID() == IDC_FREQUENCYDOMAIN) 
	{
		
		pDC->SetBkMode(TRANSPARENT);					//设置透明属性
		pDC->SetTextColor(RGB(255, 0, 0));				//设置字体颜色
		return (HBRUSH)GetStockObject(NULL_BRUSH);		//返回空画刷

	}

	return hbr;
}




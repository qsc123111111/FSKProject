#include "pch.h"
#include "SignalProcessing.h"

#include "Stadfx.h"
#include "math.h"
#include <random>
#include <iostream>
#include <iterator>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


SignalProcessing::SignalProcessing()
{
	windowFunction_LPF = 0;
	windowFunction_BPF = 0;
	selectModulation = 0;

	M = 20;					
	N = 127;					
	freq = 4000;			
	fhd = 1400;			
	fld = 600;		
	fh = 200;			
	fc = 1000;  
}

SignalProcessing::~SignalProcessing()
{


}

void SignalProcessing::init(int samplingFrequency, int carrierFrequency, int symbolPeriod, int filterOrder, int asOfFrequency_LPF, int minimumFrequency_BPF, int maximumFrequency_BPF)
{
	freq = samplingFrequency;
	fc = carrierFrequency;
	M = symbolPeriod;
	N = filterOrder;
	fh = asOfFrequency_LPF;
	fld = minimumFrequency_BPF;
	fhd = maximumFrequency_BPF;
}

//离散傅里叶变换
void SignalProcessing::DFT(float x[], int m)
{
	float fDDR[16 * 30];
	float fDDI[16 * 30];

	for (int k = 0; k < m; k++)
	{
		fDDR[k] = 0;
		fDDI[k] = 0;
		for (int i = 0; i < m; i++)
		{
			fDDR[k] = fDDR[k] + x[i] * cos(2 * PI1 * k * i / m);
			fDDI[k] = fDDI[k] + x[i] * sin(2 * PI1 * k * i / m);
		}
		fDD[k] = sqrt(fDDR[k] * fDDR[k] + fDDI[k] * fDDI[k]);
	}
}

//逆离散傅里叶变换
void SignalProcessing::IDFT(float h[]) {

	for (int k = 0; k < 16 * M; k++)
	{  //float r[1000],i[1000];
		H2[k] = 0.0;
		for (int i = 0; i < N; i++)
		{

			H2[k] += h[i] * cos(PI1 * i / N * ((N - 1) - 2 * k)) / N;//存在误差!!!!!!!!

		}
	}
	for (int k = 0; k < 16 * M; k++)
		//{H2[k] = H2[k];}
	{
		H2[k] = H2[k] - 0.0039;
	}//误差纠正!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!经验值

}

//卷积
void SignalProcessing::Conv(float array1[], float array2[])
{
	int L = 16 * M + N;
	float y[1000] = {0};
	for (int i = 0; i < L; i++)
	{
		y[i] = 0.0;
		for (int j = 0, k = i; k >= 0; j++, k--)
		{
			if (j >= 16 * M || k >= N)
				y[i] += 0;
			else y[i] += array1[j] * array2[k];
		}
	}

	for (int i = 0; i < 16 * M; i++)
		tDD[i] = y[i + (N - 1) / 2];
}

//基带信号
void SignalProcessing::BaseBandSignal()
{
	float tDD1[16 * 30];       //存放采样数组

	//将ID变成int型数组
	int a[4] = { 0 };
	a[0] = stuID % 10;
	a[1] = stuID / 10 % 10;
	a[2] = stuID / 100 % 10;
	a[3] = stuID / 1000;
	int i = 0;
	int k = 15;
	int temp = 0;
	for (int j = 0; j < 4; j++)
	{
		//int i=0;
		temp = a[j];
		for (int i = 0; i < 4; i++)
		{
			stuID_Binary[k] = temp & 0x1;
			temp = temp >> 1;
			k--;
		}
	}
	//采样
	k = 0;
	for (i = 0; i < 16; i++)
	{
		for (int j = 0; j < M; j++)
		{
			tDD1[k] = stuID_Binary[i];
			k++;
		}
	}
	for (i = 0; i < 16 * M; i++)  //编成双极性非归零码
	{
		if (tDD1[i] == 0)
			tDD[i] = -1;
		//	Sa[i] = 0;           //编成单极性非归零码
		else
			tDD[i] = 1;
	}
	DFT(tDD, 16 * M);    //频域
}

//窗函数法低通滤波器
void SignalProcessing::LPF()
{
	int i;
	float a = (N - 1) / 2;
	float Wn1[127] = { 0 };      //窗的长度
	float H10[127];
	switch (GetWindowFunction_LPF())
	{
	case 0:   //矩形窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 1;
	}
	break;
	case 1:  //哈明窗
	{
		for (i = 0; i < N; i++)
		{
			Wn1[i] = 0.5 * (1.0 - cos(2.0 * PI1 * i / (N - 1)));
		}
	}
	break;
	case 2:  //汉宁窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 0.54 - 0.46 * cos(2.0 * PI1 * i / (N - 1));
	}
	break;
	case 3: //布莱克曼窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 0.42 - 0.5 * cos(2.0 * PI1 * i / (N - 1)) + 0.08 * cos(4.0 * PI1 * i / (N - 1));
	};
	}

	//生成理想低通滤波器的单位取样响应
	for (i = 0; i < N; i++)
	{
		if (i == a)
			H10[i] = 0.1;
		else
			H10[i] = sin(2 * PI1 * fh / freq * (i - a)) / (float)(PI1 * (i - a));
	}

	for (i = 0; i < N; i++)
		H10[i] = H10[i] * Wn1[i];

	for (i = 0; i < N; i++)
		H1[i] = H10[i];


	Conv(tDD, GetH1());    //基带信号通过低通滤波器
	DFT(tDD, 16 * M);      //频域
}

//频率采样低通滤波器
void SignalProcessing::LPFFS() {
	int k;
	float Hb0[127];
	for (k = 0; k < N; k++)
		Hb0[k] = 0.0;
	for (k = 0; k < N; k++)
	{
		int  const freq = 4000;


		if ((float)freq * k / N < 100)
			Hb0[k] = 1;
		if (((float)freq * k / N > 100) && ((float)freq * k / N < 300))//K点数，freq/N变到0到2pai
			Hb0[k] = (300 - (float)freq * k / N) / 200;//归一化

	}
	SetHb(Hb0);
	IDFT(GetHb());


	Conv(tDD, GetH2());
	DFT(tDD, 16 * M);
}

//调制(FSK)
void SignalProcessing::FSKModulate()
{
	float a1 = 0.0;
	float a2 = 0.0;

	for (int i = 0; i < 16 * M; i++)
	{
		a1 = 2.0 * PI1 * f11 * i / freq; // 计算第一个频率的相位
		a2 = 2.0 * PI1 * f22 * i / freq; // 计算第二个频率的相位

		Mod[i] = tDD[i] * cos(a1 + a2); // 应用两个频率进行调制
	}

	for (int i = 0; i < 16 * M; i++)
		tDD[i] = Mod[i];

	DFT(tDD, 16 * M);
}

//调制(ASK)
void SignalProcessing::ASKModulate(){

	float c = (float) fc / freq;
	float a = 0.0;
	for (int i = 0; i < 16 * M; i++)
	{
		a = 2.0 * PI1 * c * i;

		//a = 2.0 * PI1 * 0.25 * i;

		Mod[i] = tDD[i] * cos(a);
	}
	for (int i = 0; i < 16 * M; i++)
		tDD[i] = Mod[i];
	DFT(tDD, 16 * M);

}

//调制(PSK)
void SignalProcessing::PSKModulate() {

	float c = (float)fc / freq;
	float I[16 * 15]{};
	float Q[16 * 15]{};
	float It[16 * 30]{};
	float Qt[16 * 30]{};
	int k = 0;
	float a = 0;
	for (int i = 0; i < 21 * M; i++)
	{
		if (i % 2 == 1)
		{
			Q[(i - 1) / 2] = tDD[i];//奇数位存进Q中
		}
		else
		{
			I[i / 2] = tDD[i];//偶数位存进I中
		}
	}
	for (int i = 0; i < 21 * M / 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			It[k] = I[i];
			Qt[k] = Q[i];
			k++;
		}
	}
	for (int i = 0; i < 21 * M; i++)
	{
		float a = 2 * PI1 * c * i;
		tDD[i] = It[i] * cos(a) - Qt[i] * sin(a);

	}
	DFT(tDD, 16 * M);
}

//信道
void SignalProcessing::Channel()
{
	Noise(noiseIntensity);
	for (int i = 0; i < 16 * M; i++)
		tDD[i] = tDD[i] + No[i];
	DFT(tDD, 16 * M);
}

//噪音（时频域）
void SignalProcessing::Noise(int inten)
{
	int  k;
	const float mean = 0.0;//均值
	const float stddev = 0.1;//标准差
	default_random_engine generator;
	normal_distribution<float> dist(mean, stddev);
	for (k = 0; k < 16 * M; k++)
	{
		No[k] = inten * dist(generator);
	}
	DFT(No, 16 * M);


	/*int i,k;
	float r0=0.0;
	float r[12];
	for(k=0; k<16*M; k++)
	{
		for(i=0; i<12; i++)
		{

			r[i] = (float)(2*rand()-RAND_MAX)/RAND_MAX;
			r0 += r[i];
			r0 = float(inten*r0/12.0);
		}
		No[k] = r0;
	}*/

}

//窗函数法带通滤波器
void SignalProcessing::BPF()
{

	int i;
	float a = (N - 1) / 2;
	float Wn1[127] = { 0 };
	float H10[127];
	switch (GetWindowFunction_BPF())
	{
	case 0:  //矩形窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 1;
	}
	break;
	case 1:   //哈明窗
	{
		for (i = 0; i < N; i++)
		{
			Wn1[i] = 0.5 * (1.0 - cos(2.0 * PI1 * i / (N - 1)));
		}
	}
	break;
	case 2:  //汉宁窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 0.54 - 0.46 * cos(2.0 * PI1 * i / (N - 1));
	}
	break;
	case 3:  //布莱克曼窗
	{
		for (i = 0; i < N; i++)
			Wn1[i] = 0.42 - 0.5 * cos(2.0 * PI1 * i / (N - 1)) + 0.08 * cos(4.0 * PI1 * i / (N - 1));
	};
	}

	//生成理想带通滤波器的单位取样响应
	for (i = 0; i < N; i++)
	{
		if (i == a)
			H10[i] = 0.4;
		else
			H10[i] = sin(0.7 * PI1 * (i - a)) / (float)(PI1 * (i - a)) - sin(0.3 * PI1 * (i - a)) / (float)(PI1 * (i - a));
	}

	for (i = 0; i < N; i++)
		H10[i] = H10[i] * Wn1[i];

	SetHb(H10);
	Conv(tDD, GetHb());
	DFT(tDD, 16 * M);
}

//频率采样带通滤波器
void SignalProcessing::BPFFS() {
	int k;
	float Hb0[127];
	for (k = 0; k < N; k++)
		Hb0[k] = 0.0;
	for (k = 0; k < (N - 1) / 2; k++)
	{
		if (((float)freq * k / N > 700) && ((float)freq * k / N < 900))
			Hb0[k] = ((float)freq * k / N - 700) / 200;
		//Hb0[k] = 0;//改
		if (((float)freq * k / N > 900) && ((float)freq * k / N < 1100))
			Hb0[k] = 1;
		if (((float)freq * k / N > 1100) && ((float)freq * k / N < 1300))
			Hb0[k] = (1300 - (float)freq * k / N) / 200;
		//Hb0[k] = 0;//改
	//else Hb0[k]=0;
		Hb0[N - 1 - k] = Hb0[k];
	}
	SetHb(Hb0);
	IDFT(GetHb());
	Conv(tDD, GetH2());
	DFT(tDD, 16 * M);
}

//解调(FSK)
void SignalProcessing::FSKDemodulate() {

	float a1 = 0.0;
	float a2 = 0.0;

	for (int i = 0; i < 16 * M; i++)
	{
		a1 = 2.0 * PI1 * f11 * i / freq; // 计算第一个频率的相位
		a2 = 2.0 * PI1 * f22 * i / freq; // 计算第二个频率的相位

		Mod[i] = tDD[i] * cos(a1);
		Mod[i] += tDD[i] * cos(a2); // 应用两个频率进行解调
	}

	for (int i = 0; i < 16 * M; i++)
		tDD[i] = Mod[i];

	DFT(tDD, 16 * M);
}

//解调(ASK) FSK
void SignalProcessing::ASKDemodulate() {

	float c = (float)fc / freq;
	TRACE(_T("%lf\n"), c);
	float a = 0.0;
	for (int i = 0; i < 16 * M; i++)
	{
		a = 2.0 * PI1 * c * i;

		//a = 2.0 * PI1 * 0.25 * i;

		Mod[i] = tDD[i] * cos(a);
	}
	for (int i = 0; i < 16 * M; i++)
		tDD[i] = Mod[i];
	DFT(tDD, 16 * M);
}

//抽样判决
void SignalProcessing::Adjust()
{
	int H[16] = { 0 };
	int k = 0;
	int j = 0;
	for (int i = 0; i < 16; i++)
	{
		S1[i] = 0;
		for (j = 0; j < M; j++)
		{
			S1[i] += tDD[k];
			k++;
		}
	}
	k = 0;
	for (int i = 0; i < 16; i++)
	{
		for (j = 0; j < M; j++)
		{
			//if(S1[i]>0)改
			if (S1[i] > 0)
			{
				tDD[k] = 1;
				k++;
			}
			else
			{
				tDD[k] = -1;
				//Sa[k] = 0;改
				k++;
			}
		}
	}
	for (int i = 0; i < 16; i++)
	{
		H[i] = tDD[i];
	}

	DFT(tDD, 16 * M);
}

//显示
void SignalProcessing::Display()
{
	//发送的学号十六进制； 
	int a[4] = { 0 };
	a[0] = stuID % 10;//个
	a[1] = stuID / 10 % 10;//十
	a[2] = stuID / 100 % 10;//百
	a[3] = stuID / 1000;//千
	int i = 0;
	int k = 15;
	int temp = 0;
	for (int j = 0; j < 4; j++)
	{
		//int i=0;
		temp = a[j];
		for (int i = 0; i < 4; i++)
		{
			S[k] = temp & 0x1;
			temp = temp >> 1;
			k--;
		}
	}

	// 接收信号；	
	k = 0;
	int j = 0;
	for (int i = 0; i < 16; i++)
	{
		S1[i] = 0;
		for (j = 0; j < M; j++)
		{
			S1[i] += tDD[k];
			k++;
		}
	}
	k = 15;
	for (i = 0; i < 16; i++)
	{


		if (S1[i] > 0)
		{
			tDD[k] = 1;
			k--;
		}
		if (S1[i] < 0)
		{
			tDD[k] = 0;
			k--;
		}

	}
	for (i = 0; i < 16; i++)
	{
		H[i] = tDD[i];
	}
}

void SignalProcessing::SetSignal(int id, int intensty) {
	stuID = id;
	noiseIntensity = intensty;
}

void SignalProcessing::SetWindowFunction_LPF(int c) {
	windowFunction_LPF = c;
}

void SignalProcessing::SetWindowFunction_BPF(int c) {
	windowFunction_BPF = c;
}

void SignalProcessing::SetHb(float H[]) {

	for (int i = 0; i < N; i++)
		Hb[i] = H[i];
}

int SignalProcessing::GetWindowFunction_LPF() {
	return windowFunction_LPF;
}

int SignalProcessing::GetWindowFunction_BPF() {
	return windowFunction_BPF;
}

int SignalProcessing::GetNoiseIntensity() {
	return noiseIntensity;
}

float* SignalProcessing::GetH1() {
	return H1;
}

float* SignalProcessing::GetHb() {
	return Hb;
}

float* SignalProcessing::GetTDD() {
	return tDD;
}

float* SignalProcessing::GetFDD() {
	return fDD;
}

float* SignalProcessing::GetNo() {
	return No;
}

int* SignalProcessing::GetS() {
	return S;
}

int* SignalProcessing::GetH() {
	return H;
}

int SignalProcessing::GetM() {
	return M;
}

float* SignalProcessing::GetH2() {
	return H2;
}

int SignalProcessing::GetSelectModulation() {
	return selectModulation;
}

void SignalProcessing::SetSelectModulation(int sM) {
	selectModulation = sM;
}

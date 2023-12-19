#pragma once

double const PI1 = 3.1415926;

//FSK常量
float const f11 = 1000.0;   //第一个频率
float const f22 = 2000.0;   //第二个频率

class SignalProcessing
{
public:

	SignalProcessing();
	virtual ~SignalProcessing();

	void init(int samplingFrequency, int carrierFrequency, int symbolPeriod, int filterOrder, int asOfFrequency_LPF, int minimumFrequency_BPF, int maximumFrequency_BPF);;
	void SetSignal(int id,int intensty);

	void DFT(float x[], int m);    //离散傅里叶变换

	void IDFT(float h[]);          //逆离散傅里叶变换

	void Conv(float array1[], float array2[]);  //卷积


	void BaseBandSignal();
	void LPF();
	
	void FSKModulate();
	void ASKModulate();
	void PSKModulate();

	void Channel();
	void Noise(int inten);
	void BPF();

	void FSKDemodulate();
	void ASKDemodulate();

	void Adjust();
	void Display();



	//频率采样
	void LPFFS();
	void BPFFS();

	int GetWindowFunction_LPF();
	int GetWindowFunction_BPF();
	int GetNoiseIntensity();

	void SetWindowFunction_LPF(int c);
	void SetWindowFunction_BPF(int c);

	int GetM();

	float* GetH1();
	void SetHb(float H[]);
	float* GetHb();
	float* GetTDD();
	float* GetFDD();
	float* GetNo();
	float* GetH2();

	int* GetS();
	int* GetH();

	int GetSelectModulation();
	void SetSelectModulation(int sM);


private:
	int stuID;					//学号
	int noiseIntensity;			//噪音强度

	int windowFunction_LPF;     //低通窗函数选择
	int windowFunction_BPF;     //带通窗函数选择

	float stuID_Binary[16];     //存放二进制学号

	float fDD[16 * 30];         //频域数据
	float tDD[16 * 30];         //存放双极性非归零码(-1,1) 时域数据
	
	float S1[16];               //抽样判决的临时变量
	float H2[16 * 30];          //逆傅里叶变换使用

	float H1[16 * 30];         //窗的系统响应函数（低通）
	float Hb[127];             //窗的系统响应函数（带通）

	float Mod[16 * 30];        //存放调制后的信号
	float No[16 * 30];         //噪音

	int S[16];				   //二进制输入学号
	int H[16];                 //二进制输出学号

	int M;						//码元周期
	int N;						//滤波器阶数
	int freq;					//采样频率
	int fhd;					//带通的截至频率
	int fld;					//带通的截至频率
	int fh;						//低通的截至频率
	int fc ;					//载波频率


	int selectModulation;                //调制方式选择

};


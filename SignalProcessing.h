#pragma once

double const PI1 = 3.1415926;

//FSK����
float const f11 = 1000.0;   //��һ��Ƶ��
float const f22 = 2000.0;   //�ڶ���Ƶ��

class SignalProcessing
{
public:

	SignalProcessing();
	virtual ~SignalProcessing();

	void init(int samplingFrequency, int carrierFrequency, int symbolPeriod, int filterOrder, int asOfFrequency_LPF, int minimumFrequency_BPF, int maximumFrequency_BPF);;
	void SetSignal(int id,int intensty);

	void DFT(float x[], int m);    //��ɢ����Ҷ�任

	void IDFT(float h[]);          //����ɢ����Ҷ�任

	void Conv(float array1[], float array2[]);  //���


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



	//Ƶ�ʲ���
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
	int stuID;					//ѧ��
	int noiseIntensity;			//����ǿ��

	int windowFunction_LPF;     //��ͨ������ѡ��
	int windowFunction_BPF;     //��ͨ������ѡ��

	float stuID_Binary[16];     //��Ŷ�����ѧ��

	float fDD[16 * 30];         //Ƶ������
	float tDD[16 * 30];         //���˫���Էǹ�����(-1,1) ʱ������
	
	float S1[16];               //�����о�����ʱ����
	float H2[16 * 30];          //�渵��Ҷ�任ʹ��

	float H1[16 * 30];         //����ϵͳ��Ӧ��������ͨ��
	float Hb[127];             //����ϵͳ��Ӧ��������ͨ��

	float Mod[16 * 30];        //��ŵ��ƺ���ź�
	float No[16 * 30];         //����

	int S[16];				   //����������ѧ��
	int H[16];                 //���������ѧ��

	int M;						//��Ԫ����
	int N;						//�˲�������
	int freq;					//����Ƶ��
	int fhd;					//��ͨ�Ľ���Ƶ��
	int fld;					//��ͨ�Ľ���Ƶ��
	int fh;						//��ͨ�Ľ���Ƶ��
	int fc ;					//�ز�Ƶ��


	int selectModulation;                //���Ʒ�ʽѡ��

};


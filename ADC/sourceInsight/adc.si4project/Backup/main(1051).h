#ifndef __MAIN_H
#define __MAIN_H




//��λʱ��λ�����ֵ�����ڴ�ֵ����0
#define lungThreshold 58
//��ѹϵ��A
#define coefficientB 19.3
//��ѹϵ��A
#define coefficientA 90.48
//��ΪSTM8�Ը�����֧�ֲ��ã��������еĸ����͵����ݶ�ת��������
#define PRECISION 100.00

//���³�ѹ�¿����ܶ�Ϊ1.3g/L
#define AIRDENSITY 1.3
//����ʱʹ�õ�Ƥ�����Ϊ30.19 mm*mm
#define PIPESIZE 30.19
//Ƥ�й�ϵ���ݶ���1.0��������Ҫ���Ը���
#define PITOT 2.364684



typedef struct
{
   //�λ���
   float lungCapacity;
   //�����ܶ�
   float airDensity;
   //�ܵ����
   float pipeSize;
    //Ƥ�й�ϵ��
   float Pitot;
   //��ǰ��ѹ��Ӧ����ѹֵ
   float airPressure;
   //��λʱ������������
   float unitGasFlow;
}spirometer;

#endif /* __MAIN_H*/

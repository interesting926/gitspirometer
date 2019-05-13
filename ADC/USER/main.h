#ifndef __MAIN_H
#define __MAIN_H



//��ΪSTM8�Ը�����֧�ֲ��ã��������еĸ����͵����ݶ�ת��������
#define PRECISION 100

//���³�ѹ�¿����ܶ�Ϊ1.3g/L
#define AIRDENSITY 130
//����ʱʹ�õ�Ƥ�����Ϊ30.19 mm*mm
#define PIPESIZE 3019
//Ƥ�й�ϵ���ݶ���1.0��������Ҫ���Ը���
#define PITOT 100


typedef struct
{
   //�λ���
   u32 lungCapacity;
   //�����ܶ�
   u32 airDensity;
   //�ܵ����
   u32 pipeSize;
    //Ƥ�й�ϵ��
   u32 Pitot;
   //��ǰ��ѹ��Ӧ����ѹֵ
   u32 airPressure;
   //��λʱ������������
   u32 unitGasFlow;
   

}spirometer;

#endif /* __MAIN_H*/
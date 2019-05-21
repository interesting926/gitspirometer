#ifndef __MAIN_H
#define __MAIN_H




//单位时间肺活量阈值，低于此值都是0
#define lungThreshold 58
//气压系数A
#define coefficientB 19.3
//气压系数A
#define coefficientA 90.48
//因为STM8对浮点数支持不好，所以所有的浮点型的数据都转换成整形
#define PRECISION 100.00

//常温常压下空气密度为1.3g/L
#define AIRDENSITY 1.3
//测试时使用的皮管面积为30.19 mm*mm
#define PIPESIZE 30.19
//皮托管系数暂定是1.0，后续需要测试更改
#define PITOT 2.364684



typedef struct
{
   //肺活量
   float lungCapacity;
   //空气密度
   float airDensity;
   //管道面积
   float pipeSize;
    //皮托管系数
   float Pitot;
   //当前电压对应的气压值
   float airPressure;
   //单位时间内气体流量
   float unitGasFlow;
}spirometer;

#endif /* __MAIN_H*/

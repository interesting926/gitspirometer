#ifndef __MAIN_H
#define __MAIN_H



//因为STM8对浮点数支持不好，所以所有的浮点型的数据都转换成整形
#define PRECISION 100

//常温常压下空气密度为1.3g/L
#define AIRDENSITY 130
//测试时使用的皮管面积为30.19 mm*mm
#define PIPESIZE 3019
//皮托管系数暂定是1.0，后续需要测试更改
#define PITOT 100


typedef struct
{
   //肺活量
   u32 lungCapacity;
   //空气密度
   u32 airDensity;
   //管道面积
   u32 pipeSize;
    //皮托管系数
   u32 Pitot;
   //当前电压对应的气压值
   u32 airPressure;
   //单位时间内气体流量
   u32 unitGasFlow;
   

}spirometer;

#endif /* __MAIN_H*/
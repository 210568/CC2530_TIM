/*
*项目目标：利用定时器T1，LED灯五秒钟闪烁一次
*项目编写时间：2022年3月16日
*项目编写人：李俊辉
*/


#include "ioCC2530.h"
#define LED1 P1_0               //P1_0端口
unsigned int count = 0;         //定义中断

/*
*函数名称：Initail_T1()
*函数功能：初始化T1中断
*函数入口：void initail_T1()
*函数返回值：无
*函数形参：无
*/
void Initail_T1()
{
  T1IE = 1;                     //使能T1中断
  T1CTL = 0x05;                 //启动定时器1，设置8分频自由运行模式
  TIMIF |= 0x40;                //使能T1溢出中断
  EA = 1;                       //使能全局中断
}

/*
*函数名称：T1_ISR()
*函数功能：T1中断服务函数
*函数入口：__interrupt void T1_ISR(void)
*函数形参：无
*/
#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
  IRCON = 0x00;                 //清中断标志位，硬件会自动清零
  if(count > 312)               //312 * 0.016 = 5
  {
    count = 0x00;               //程序计数器清零
    LED1 = !LED1;               //LED1状态反转
  }
  else
  {
    count++;
  }
}

/*
*函数名称：Initail_GPIO()
*函数功能：初始化GPIO口
*函数入口：void Initail_GPIO()
*函数返回值：无
*函数形参：无
*/
void Initail_GPIO()
{
  P1SEL &= ~0x01;               //设置P1_0为GPIO口
  P1DIR |= 0x01;                //定义P1_0端口为输出
}

/*
*函数名称：main()
*函数功能：主函数，程序入口
*函数入口：void main(void)
*函数返回值：无
*函数形参：无
*/
void main(void)
{
  CLKCONCMD &= ~0x7F;           //设置晶振为32Mhz
  while(CLKCONCMD & 0x40);     //等待晶振稳定
  Initail_T1();                  //调用T1初始化函数
  Initail_GPIO();               //调用GPIO初始化函数
  LED1 = 0;                     //关闭LED1
  while(1);
}
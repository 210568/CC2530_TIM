/*
*��ĿĿ�꣺���ö�ʱ��T1��LED����������˸һ��
*��Ŀ��дʱ�䣺2022��3��16��
*��Ŀ��д�ˣ����
*/


#include "ioCC2530.h"
#define LED1 P1_0               //P1_0�˿�
unsigned int count = 0;         //�����ж�

/*
*�������ƣ�Initail_T1()
*�������ܣ���ʼ��T1�ж�
*������ڣ�void initail_T1()
*��������ֵ����
*�����βΣ���
*/
void Initail_T1()
{
  T1IE = 1;                     //ʹ��T1�ж�
  T1CTL = 0x05;                 //������ʱ��1������8��Ƶ��������ģʽ
  TIMIF |= 0x40;                //ʹ��T1����ж�
  EA = 1;                       //ʹ��ȫ���ж�
}

/*
*�������ƣ�T1_ISR()
*�������ܣ�T1�жϷ�����
*������ڣ�__interrupt void T1_ISR(void)
*�����βΣ���
*/
#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
  IRCON = 0x00;                 //���жϱ�־λ��Ӳ�����Զ�����
  if(count > 312)               //312 * 0.016 = 5
  {
    count = 0x00;               //�������������
    LED1 = !LED1;               //LED1״̬��ת
  }
  else
  {
    count++;
  }
}

/*
*�������ƣ�Initail_GPIO()
*�������ܣ���ʼ��GPIO��
*������ڣ�void Initail_GPIO()
*��������ֵ����
*�����βΣ���
*/
void Initail_GPIO()
{
  P1SEL &= ~0x01;               //����P1_0ΪGPIO��
  P1DIR |= 0x01;                //����P1_0�˿�Ϊ���
}

/*
*�������ƣ�main()
*�������ܣ����������������
*������ڣ�void main(void)
*��������ֵ����
*�����βΣ���
*/
void main(void)
{
  CLKCONCMD &= ~0x7F;           //���þ���Ϊ32Mhz
  while(CLKCONCMD & 0x40);     //�ȴ������ȶ�
  Initail_T1();                  //����T1��ʼ������
  Initail_GPIO();               //����GPIO��ʼ������
  LED1 = 0;                     //�ر�LED1
  while(1);
}
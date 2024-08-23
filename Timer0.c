#include <REGX52.H>

void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值	1ms值溢出
	TH0 = 0xFC;				//设置定时初始值  值溢出则进入中断函数
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

/*定时器中断函数模板,配合使用
void Timer0_Routine() interrupt 1
{
	static unsigned int T0count;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
		T0count++;
		if(T0count>=1000)
		{
				T0count=0;
				P2=~P2; //LED亮灭				
		}
}
*/
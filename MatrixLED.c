#include <REGX52.H>
#include "Delay.h"

#define MATRIX_LED_PORT  P0

sbit SCK=P3^6;      //SRCLK 上升沿移位
sbit RCK=P3^5;      //RCLK，上升沿锁存 
sbit SER=P3^4;

/**
  * @brief 点阵屏初始化
  * @param 无
  * @retval 无
  */

void MatrixLED_Init()
{
		RCK=0;											//上升沿锁存 初始高电平清零
		SCK=0;											//上升沿移位 初始高电平清零

}

/**
  * @brief 74HC595显示函数 写入一个字节
  * @param Byte 要写入的字节
  * @retval 无
  */


void _74HC595_WriteByte(unsigned char Byte)// 声明显示函数
{
		unsigned char i;						//char 位数小
		for(i=0;i<8;i++)						//定义i，循环8次，串行输入；一起发送，并行输出
		{
				SER=Byte&(0x80>>i);			//0x80按位右移
				SCK=1;									//上升沿移位，读取SER
				SCK=0;									//清零，等待下次
		}
																/*Byte是8位，SER是一位，非0即1
																让SER依次得到8位，
																用Byte&1000 0000(0x80),0100 0000(0x40),
																依次排位确认各个位的数字
																*/
		
		RCK=1;											//并行输出
		RCK=0;											//清零
		
}

/**
  * @brief LED点阵屏选取函数
	* @param column 要选择的列 范围：左数0~7 0为选取
	* @param Date 列上的显示数据 高位在上 1为亮
	* @retval 无
  */

void MatrixLED_Show (unsigned char column,Date)//声明选取函数，位选，段选两个形参
{
		_74HC595_WriteByte(Date);		//Date数据1亮	  段选  共阳极
		P0=~(0x80>>column);					//列数取反0给P0 位选	共阴极
		Delay(1);										//消影
		MATRIX_LED_PORT=0xff;				//位选清零
}

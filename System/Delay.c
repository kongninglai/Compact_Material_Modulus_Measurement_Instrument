// #include "stm32f10x.h"

// /**
//   * @brief  微秒级延时
//   * @param  xus 延时时长，范围：0~233015
//   * @retval 无
//   */
// void Delay_us(uint32_t xus)
// {
// 	SysTick->LOAD = 72 * xus;				//设置定时器重装值
// 	SysTick->VAL = 0x00;					//清空当前计数值
// 	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
// 	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
// 	SysTick->CTRL = 0x00000004;				//关闭定时器
// }

// /**
//   * @brief  毫秒级延时
//   * @param  xms 延时时长，范围：0~4294967295
//   * @retval 无
//   */
// void Delay_ms(uint32_t xms)
// {
// 	while(xms--)
// 	{
// 		Delay_us(1000);
// 	}
// }
 
// /**
//   * @brief  秒级延时
//   * @param  xs 延时时长，范围：0~4294967295
//   * @retval 无
//   */
// void Delay_s(uint32_t xs)
// {
// 	while(xs--)
// 	{
// 		Delay_ms(1000);
// 	}
// } 

#include "Delay.h"
#include "misc.h"
 
static u8  fac_us=0;
static u16 fac_ms=0;

void delay_init(u8 SYSCLK)
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}								    

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;          
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;         	    
}   
	    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 	 
	SysTick->VAL=0x00;        
	SysTick->CTRL=0x01 ;      	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));   
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;      	 
}



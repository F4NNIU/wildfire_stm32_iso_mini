/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   dht11温湿度传感器测试实验
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 ISO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_dht11.h"
#include "bsp_usart1.h"
#include "bsp_ili9341_lcd.h"

DHT11_Data_TypeDef DHT11_Data;

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{
	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();
	
	LCD_Init();	
	LCD_Clear(0, 0, 240, 320, BACKGROUND);
	LCD_DispStr(10, 90, (uint8_t *)"This is a dht11 test demo", WHITE);

	USART1_Config();
	printf("\r\n***野火ISO dht11 温湿度传感器实验***\r\n");
	
	/*初始化DTT11的引脚*/
	DHT11_GPIO_Config(); 	

	/*调用Read_DHT11读取温湿度，若成功则输出该信息*/
	if( Read_DHT11(&DHT11_Data)==SUCCESS)
	{
		printf("\r\n读取DHT11成功!\r\n\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n",\
		DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
		printf("\r\n 湿度:%d,温度:%d \r\n" ,DHT11_Data.humi_int,DHT11_Data.temp_int);
		
		LCD_DispStr(10, 110, (uint8_t *)"humidity:", WHITE);
		LCD_DisNum(64, 110, DHT11_Data.humi_int, WHITE);
		
		LCD_DispStr(10, 130, (uint8_t *)"temperature:", WHITE);
		LCD_DisNum(82, 130, DHT11_Data.temp_int, WHITE);
	}
	else
	{
		printf("Read DHT11 ERROR!\r\n");
		LCD_DispStr(10, 110, (uint8_t *)"Read DHT11 ERROR", WHITE);
	}
	while(1); 	
}
/*********************************************END OF FILE**********************/

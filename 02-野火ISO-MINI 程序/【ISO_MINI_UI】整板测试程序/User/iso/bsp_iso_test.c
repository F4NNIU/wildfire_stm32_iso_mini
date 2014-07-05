/**
  ******************************************************************************
  * @file    bsp_iso_test.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ISO 整板测试程序 bsp
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_iso_test.h"
#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_usart1.h"
#include "bsp_i2c_ee.h"
#include "bsp_touch.h"
#include "bsp_led.h" 
#include "bsp_key.h" 
#include "bsp_spi_flash.h"
#include "bsp_dht11.h"
#include "bsp_ds18b20.h"
#include "bsp_ov7725.h"
#include "bsp_adc.h"
#include "bsp_breathing.h" 
//#include "bsp_rda5807m.h"
#include "enc28j60_test.h"
#include "bsp_can.h"
#include "bsp_rtc.h"
//#include "bsp_fsmc_sram.h"
//#include "bsp_fsmc_nor.h"
//#include "bsp_nand.h"
#include "bsp_UsbMassStorage.h"
//#include "mp3.h"
#include "app_ui.h"
#include "bsp_bmp.h"
//#include "bsp_sdfs_app.h"


extern volatile uint8_t rec_cmd;
extern TESTING_STATE testing_state;			//播放器状态标志位，指示切歌，正在播放，暂停等状态

/*
 * 系统软件复位
 */
void Soft_Reset(void)
{
  __set_FAULTMASK(1);   /* 关闭所有中断 */  
  NVIC_SystemReset();   /* 系统复位 */
}

static void delay(uint16_t t)
{
	uint8_t i;
	while(t--)
	{
		for(i=0;i<250;i++);
	}
}

/* 
 * ISO 整板测试菜单 
 */
void Test_Menu(void)
{
	printf("\r\n[~~~~~~~~~~~~野火 ISO STM32 整板测试程序~~~~~~~~~~~~~~~]\r\n");
	printf("[------------请选择操作命，命令必须是小写字母----------]\r\n");

	printf("1 - 流水灯\r\n");
	printf("2 - 按键\r\n");
	printf("3 - EEPROM\r\n");
  printf("4 - RTC(万年历)\r\n");
  printf("5 - DHT11温湿度\r\n");
  printf("6 - DS18b20温度传感器\r\n");
  printf("7 - 摄像头(火眼ov7725)\r\n");
  printf("8 - CAN(Loopback)\r\n");
  printf("9- 呼吸灯\r\n");
  printf("a - 以太网ENC28J60\r\n");
  printf("b - Usb-Mass-Storage 测试\r\n");
  
  printf("请输入命令，字母命令必须小写\r\n");
  printf("\r\n");
}


/*
 * 根据串口不同的命令执行不同的程序
 * 用户也可以自行添加相应的程序
 */
void Board_Test(void)
{  
  while( 1 )
  {    
		
		
    switch( rec_cmd )
    {
		
			
			case 1:					//来自液晶触摸
      case '1':				//来自串口数据
        printf("按回车返回菜单 \r\n");
        printf("实验现象:LED1 LE2 LED3 轮流闪烁 \r\n");
				Lcd_Note(1);
				LCD_DispEnCh(20,110,"实验现象:LED1 LE2 LED3 轮流闪烁",BLUE);		
        LED_Test();         
        break;
      
			case 2:
      case '2':
        printf("按回车返回菜单 \r\n");
        printf("实验现象:KEY1控制LED1反转,KEY2控制LE2反转 \r\n");
				Lcd_Note(2);
				LCD_DispEnCh(20,110,"实验现象:KEY1控制LED1反转,KEY2控制LE2反转",BLUE);		
        Key_Test();        
        break;
      
			case 3:
      case '3':
        printf("按回车返回菜单 \r\n");
        printf("实验现象:串口打印出:eeprom读写测试成功 \r\n");
				Lcd_Note(3);
        Eeprom_Test();
        break;
      
			case 4:
      case '4':
        printf("按回车返回菜单 \r\n");
        printf("实验步骤 \r\n");
        printf("1-按照提示在串口中输入时间\r\n");
        printf("实验现象:串口输出新历农历和时间戳\r\n");
				Lcd_Note(4);
				LCD_DispEnCh(20,110,"实验说明:初始时间为程序固定的时间,若下面显示的时间每秒更新一次则说明RTC模块正常",BLUE);		

        RTC_Test();
        break;
      
			case 5:
      case '5':
        printf("按回车返回菜单 \r\n");
        printf("实验步骤 \r\n");
        printf("1-在ISO上插上DHT11模块 \r\n");
        printf("实验现象:串口打印出:湿度为xxxRH,温度为xxx℃ \r\n");
				Lcd_Note(5);
				LCD_DispEnCh(20,110,"实验说明:把DHT11模块接入开发板,正常时在屏幕显示温湿度",BLUE);		
				DHT11_Test(); 				
		            
        break;
			
			case 6:
      case '6':
        printf("按回车返回菜单 \r\n");
        printf("实验步骤 \r\n");
        printf("1-在ISO上插上DS18b20模块 \r\n");
        printf("实验现象:串口每隔1s打印一次温度值，同时led1闪烁一次\r\n");
				Lcd_Note(6);
				LCD_DispEnCh(20,110,"实验说明:把DS18b20模块接入开发板,正常时在屏幕显示温度,同时LED闪烁",BLUE);		
				DS18B20_Test(); 
        break;
      
			case 7:
      case '7':
				printf("按回车返回菜单 \r\n");
        printf("实验步骤 \r\n");
        printf("1-在ISO上插上摄像头模块(火眼OV7725)\r\n");
        printf("实验现象:液晶实时显示摄像头拍回来的图像\r\n");
				Lcd_Note(7);
				LCD_DispEnCh(20,110,"实验说明:把摄像头模块接入到ISO开发板中,正常时稍后液晶会显示摄像头拍回来的图像,使用硬件复位退出",BLUE);		
        delay(0xFFFF);
//				delay(0xFFFF);
//				delay(0xFFFF);
//				delay(0xFFFF);
				Camera_Test();   //采用二、三级代码优化会出错
        break;
      
			case 8:
      case '8':
        printf("按回车返回菜单 \r\n");
        printf("实验现象:串口打印信息:CAN回环测试成功同时LED1和LED2亮\r\n");
				Lcd_Note(8);
				LCD_DispEnCh(20,110,"实验说明:CAN回环测试,不需要外部接线",BLUE);		
				CAN_Loopback_Test();   
        break;
      
			case 9:
      case '9':
        printf("按回车返回菜单 \r\n");
        printf("实验现象:LED1在PWM信号的控制下在呼吸\r\n");
				Lcd_Note(9);
				LCD_DispEnCh(20,110,"实验说明:LED1在PWM信号的控制下在呼吸",BLUE);		
        Breathing_Test();  
      
        break;
      
			case 10:
      case 'a':
				printf("按回车返回菜单 \r\n");
        printf("实验步骤 \r\n");
        printf("1-在ISO上插上ENC28J60以太网模块，以太网模块用网线连接电脑或者路由器\r\n");
        printf("2-在DOS模式下输入命令: ping 192.168.1.15 \r\n");
        printf("3-电脑的IP地址或者局域网内的电脑的IP地址必须是192.168.1.x\r\n  但不能是192.168.1.15 \r\n");
        Lcd_Note(10);
				LCD_DispEnCh(20,110,"实验说明:1-在ISO上插上以太网模块,以太网模块用网线连接电脑或者路由器",BLUE);	
				LCD_DispEnCh(20,160,"2-在DOS模式下输入命令: ping 192.168.1.15  (能ping通表示正常)",BLUE);	
				LCD_DispEnCh(20,193,"3-电脑IP地址或者局域网内电脑的IP地址必须是192.168.1.x",BLUE);	

				ENC28J60_Test(); 
        break;
      
			case 11:
      case 'b': 
				printf("按回车返回菜单 \r\n");
        printf("实验步骤\r\n");
        printf("1-在ISO上插上SD卡，容量需小于32GB\r\n");
        printf("2-用microusb线连接电脑和ISO上的供电的microusb口(并不是 usb to uart) \r\n");
        printf("实验现象:串口会打印出:野火 ISO STM32 USB MASS STORAGE 实验\r\n         LED1闪烁，同时SD卡会在电脑上模拟出一个U盘\r\n");
        Lcd_Note(11);
				LCD_DispEnCh(20,110,"实验说明:1-在ISO上插上SD卡，容量需小于32GB",BLUE);		
				LCD_DispEnCh(20,150,"2-用microusb线连接电脑和ISO上的供电的microusb口(并不是 usb to uart)",BLUE);		
				LCD_DispEnCh(20,195,"正常时LED1闪烁,同时SD卡会在电脑上模拟出一个U盘",BLUE);		
				UsbMassStorage_Test();

        break;		
			
                        
      default:       
        break;
    }
  }
}

/*
 * 初始化液晶，串口，触摸屏，flash及sd卡 * 
 */
void ISO_Init(void)
{
	uint8_t k;
	
  /* 液晶初始化先于串口，不然会有bug，至于是什么原因我也不知道:( */
  LCD_Init();
  
  USART1_Config();		

	/* 初始化sd卡文件系统，因为汉字的字库放在了sd卡里面 */
	Sd_fs_init();	

  /* 显示界面图片 */
	Lcd_show_bmp(0, 0,"/boardtest/ISO_MINI/ui_boardtest.bmp");
	
	Lcd_List(1);
	
	/* 初始化外部FLASH */
	SPI_FLASH_Init();
	//SPI_FLASH_SectorErase(0);
  
	/* 触摸屏IO和中断初始化 */
	Touch_Init();		
		
		
		/*-------------------------------------------------------------------------------------------------------*/  
		#if 1
		SPI_FLASH_BufferRead(&cal_flag, 0, 1);
		if( cal_flag == 0x55 )
		{
			SPI_FLASH_BufferRead((void*)cal_p, 1, sizeof(cal_p));
			SPI_FLASH_CS_HIGH();
			for( k=0; k<6; k++ )
						printf("\r\n rx = %LF \r\n",cal_p[k]);
		}
		else
		{
			/* 等待触摸屏校正完毕 */
			while(Touch_Calibrate() !=0);
		}
		#elif 0
		/* 等待触摸屏校正完毕 */
		while(Touch_Calibrate() !=0);
		#endif
	


}


uint8_t key_state = 0;

/* 
 * ISO-MINI 自动整板测试 
 */
void ISO_AutoTest(void)
{
	uint32_t i=0x9ffff;
	uint8_t board_state = 1;
	uint8_t board_test = 0x55;
	
  /* 液晶初始化先于串口，不然会有bug，至于是什么原因我也不知道:( */
  LCD_Init();
  
	LCD_Clear(0,0,240,320,WHITE);
	
	LCD_DispStr(50,10,"ISO-MINI Auto Detect... ",BLUE);
	
  USART1_Config();			
	
	SysTick_Init();
	
	/* LED 端口初始化 */
	LED_GPIO_Config();	
	LED1_ON;
	LED2_ON;
	LED3_ON;
	
	/*按键*/
	Key1_GPIO_Config();
  Key2_GPIO_Config();
	
	
	/* EEPROM测试 */
	LCD_DispStr(20,40,"1.EEPROM checking...",BLUE);
	/*-----------------------------------------------------------------------------------*/  
  if (EEPROM_AutoTest() == 0) //坏
	{
		board_state = 0;	
		LCD_DispStr(20,40,"1.EEPROM check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,40,"1.EEPROM check success!",BLUE);

	}		

	/* FLASH 测试 */
	
	LCD_DispStr(20,60,"2.FLASH checking...",BLUE);
	
	if(FLASH_AutoTest() == 0) //坏
	{
		board_state = 0;
		LCD_DispStr(20,60,"2.FLASH check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,60,"2.FLASH check success!",BLUE);

	}
	
	/* RTC测试 */
	
	LCD_DispStr(20,80,"3.RTC checking...",BLUE);
	
	if(RTC_AutoTest() == 0) //坏
	{
		board_state = 0;
		LCD_DispStr(20,80,"3.RTC check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,80,"3.RTC check success!",BLUE);

	}
		
	if(board_state == 0)// 测试不通过
	{
			LCD_DispStr(20,200,"Board checking fail!!!",RED);
			while(1);
		}
		
	/* 按键测试 */
	LCD_DispStr(20,100,"4.Please check the key and led ",BLUE);	
		

		
	while(i--)
	{
		/* 按键测试 */
		if(	Key_Scan(GPIOA,GPIO_Pin_0) == KEY_ON)
		{	
				//key_state =~key_state;
				LED1_TOGGLE;
				LED2_TOGGLE;
				LED3_TOGGLE;
			
			}
		
		if(	Key_Scan(GPIOC,GPIO_Pin_13)== KEY_ON)
		{
				//key_state =~key_state;
				LED1_TOGGLE;
				LED2_TOGGLE;
				LED3_TOGGLE;

			}
	}	
	
	/* 关闭systick定时器 以免影响IIc写入*/
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	i2c_CheckDevice();
	ee_WriteBytes(&board_test,0x0,1); //自测成功，写入标记
	Soft_Reset();	

}

/* 
 * ISO 整板测试 
 */
void ISO_Test(void)
{ 
	uint8_t board_test=0;	 

	i2c_CheckDevice();
	delay(0xff); 
	ee_ReadBytes(&board_test, 0x0, 1);
	
	if(board_test != 0x55) //自检未通过 
	{
		ISO_AutoTest();		
	}
	else
	{
		ISO_Init();	
		Test_Menu();
		Board_Test();
	}

	while( 1 ){}
}
/* ---------------------------------------end of file------------------------------------- */

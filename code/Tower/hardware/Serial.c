#include "stm32f10x.h"
#include "serial.h"
#include "oled.h"
#include "delay.h"

#include "string.h"

#define  SHT30_TX_CLK		(RCC_APB2Periph_GPIOA)
#define  SHT30_TX_PORT		(GPIOA)
#define  SHT30_TX_PIN 		(GPIO_Pin_9)
#define  SHT30_RX_PORT  	(GPIOA)
#define  SHT30_RX_PIN		(GPIO_Pin_10)

uint8_t Serial_RxData[64];		//定义串口接收的数据变量
uint8_t Serial_RxFlag;		    //定义串口接收的标志位变量

static void USART1_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(SHT30_TX_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = SHT30_TX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SHT30_TX_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = SHT30_RX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SHT30_RX_PORT,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	
	NVIC_InitTypeDef NVIC_InitStructure;					
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);						
	
	USART_Cmd(USART1, ENABLE);	
}

void SHT30_init(void)
{
	USART1_init();
	
	USART1_Send_String("Hand\r\n");
}

static void Serial_RxData_clear(void)
{
	for(uint8_t i = 0; i < 64; i++)
	{
		Serial_RxData[i] = 0;
	}
}

static void USART1_Send_Char(uint16_t data)
{
	USART_SendData(USART1, data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void USART1_Send_String(char *pstr)
{
	while(*pstr != '\0')
	{
		USART1_Send_Char(*pstr);
		pstr++;
	}
}

static uint16_t USART1_Recieve_Char(void)
{
	uint16_t RECIEVE_data;
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		RECIEVE_data = USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
	
	return RECIEVE_data;
}

void USART1_IRQHandler(void)
{
	static uint8_t i = 0;
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		
	{
		uint8_t RECIEVE_Data = USART_ReceiveData(USART1);
		if(Serial_RxFlag == 0)
		{
			if(RECIEVE_Data == '\r')
			{
				Serial_RxFlag = 1;
			}
			else
			{
				Serial_RxData[i] = RECIEVE_Data;
				i++;
			}
		}
		else if(Serial_RxFlag == 1)
		{
			if(RECIEVE_Data == '\n')
			{
				Serial_RxFlag = 2;
				i = 0;			
			}
			else
			{
				Serial_RxData[i] =  '\r'; 			//如果不是连续的\r\n则继续读数据
				i++;
				Serial_RxData[i] = RECIEVE_Data;
				i++;
				Serial_RxFlag = 0;
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);			
	}
}

void Get_temperature_humidity(char *humidity, char *temperature)
{	
	USART1_Send_String("Read\r\n");
	Delay_ms(50);
	
	if(Serial_RxFlag == 2)
	{	
		memcpy(humidity, &Serial_RxData[3], 4);
		memcpy(temperature, &Serial_RxData[11], 5);
		
		Serial_RxData_clear();
		Serial_RxFlag = 0;
	}
}

void Display_temperature_humidity(char *humidity, char *temperature)
{
	OLED_ShowString(3, 1, "humi:");
	OLED_ShowString(4, 1, "temp:");
	OLED_ShowString(3, 6, (char *)humidity);
	OLED_ShowString(4, 6, (char *)temperature);
}

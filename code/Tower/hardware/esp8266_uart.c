#include "stm32f10x.h"                  // Device header
#include "esp8266_uart.h"

#define  ESP_TX_CLK		(RCC_APB2Periph_GPIOA)
#define  ESP_TX_PORT	(GPIOA)
#define  ESP_TX_PIN 	(GPIO_Pin_2)
#define  ESP_RX_PORT  	(GPIOA)
#define  ESP_RX_PIN		(GPIO_Pin_3)

uint8_t esp_RxData[64];		//定义串口接收的数据变量
uint8_t esp_RxFlag;		    //定义串口接收的标志位变量

static void USART2_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(ESP_TX_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = ESP_TX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ESP_TX_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = ESP_RX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ESP_RX_PORT,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStruct);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);			
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
	
	NVIC_InitTypeDef NVIC_InitStructure;					
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);						
	
	USART_Cmd(USART2, ENABLE);	
}


void esp8266_init(void)
{
	USART2_init();
}

static void USART2_RxData_clear(void)
{
	for(uint8_t i = 0; i < 64; i++)
	{
		esp_RxData[i] = 0;
	}
}

static void USART2_Send_Char(uint16_t data)
{
	USART_SendData(USART2, data);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void USART2_Send_String(char *pstr)
{
	while(*pstr != '\0')
	{
		USART2_Send_Char(*pstr);
		pstr++;
	}
}

static uint16_t USART2_Recieve_Char(void)
{
	uint16_t RECIEVE_data;
	
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
	{
		RECIEVE_data = USART_ReceiveData(USART1);
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
	
	return RECIEVE_data;
}

void USART2_IRQHandler(void)
{
	static uint8_t i = 0;
	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)		
	{
		uint8_t RECIEVE_Data = USART_ReceiveData(USART2);
		if(esp_RxFlag == 0)
		{
			if(RECIEVE_Data == '\r')
			{
				esp_RxFlag = 1;
			}
			else
			{
				esp_RxData[i] = RECIEVE_Data;
				i++;
			}
		}
		else if(esp_RxFlag == 1)
		{
			if(RECIEVE_Data == '\n')
			{
				esp_RxFlag = 2;
				i = 0;			
			}
			else
			{
				esp_RxData[i] =  '\r'; 			//如果不是连续的\r\n则继续读数据
				i++;
				esp_RxData[i] = RECIEVE_Data;
				i++;
				esp_RxFlag = 0;
			}
		}
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);			
	}
}

#ifndef __Serial_H_
#define __Serial_H_

void USART1_init(void);
void Serial_RxData_clear(void);

void USART1_Send_Char(uint16_t data);
void USART1_Send_String(char *pstr);

uint16_t USART1_Recieve_Char(void);

void Get_temperature_humidity(char *humidity, char *temperature);
void Display_temperature_humidity(char *humidity, char *temperature);

#endif

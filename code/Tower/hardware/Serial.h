#ifndef __Serial_H_
#define __Serial_H_

void SHT30_init(void);
void USART1_Send_String(char *pstr);
void Get_temperature_humidity(char *humidity, char *temperature);
void Display_temperature_humidity(char *humidity, char *temperature);

#endif

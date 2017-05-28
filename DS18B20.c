#define F_CPU 8000000Ul
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "DS18B20.h"

_Bool ds18b20_init()
{	
	char error_connect = 0;
	_Bool flag = true;
	do 
	{
		if(error_connect == 10) return false;
		DS18B20_PIN_0;
		_delay_us(500);
		DS18B20_PIN_1;
		_delay_us(70);
		if(!(DS18B20_PIN&(1<<ONE_WIRE_PIN)))
		{
			flag = false;
			error_connect = 0;
		}
		else error_connect++;
	} 
	while (flag);	
	while (!(DS18B20_PIN&(1<<ONE_WIRE_PIN)));
	return true;
}

void ds18b20_write_byte(char command)
{
	for(unsigned char i = 0; i < 8; i++)
	{
		DS18B20_PIN_0;
		if(command&(1<<i)) _delay_us(10);
		else _delay_us(62);
		DS18B20_PIN_1;
		_delay_us(60);
	}
}

unsigned char ds18b20_read_byte()
{
	unsigned char data = 0;
	for(unsigned char i = 0; i < 8; i++)
	{
		DS18B20_PIN_0;
		_delay_us(2);
		DS18B20_PIN_1;
		_delay_us(15);
		if(DS18B20_PIN&(1<<ONE_WIRE_PIN)) data|=(1<<i);
		_delay_us(62);
	}
	return data;
}

void ds18b20_write_scrathpad(unsigned char scratchpad[])
{	
	for(unsigned char i = 0; i < 9; i++) scratchpad[i] = ds18b20_read_byte();	
}

float ds18b20_temperature_calculate(unsigned char scratchpad[])
{
 	float temperature = 0;
	short temp = 0;
	for(unsigned char i = 0; i < 2; i++)
	{
		temp |= (scratchpad[i]<<(i*8));
	}		
	if(temp < 0) temp -= 1;
	return temperature = temp*.0625;
}

_Bool ds18b20_crc_calculate(unsigned char scratchpad[])
{
	unsigned char crc = 0;
	for (unsigned char i = 0; i < 8; i++)
	{
		crc = crc ^ scratchpad[i];
		for (unsigned char j = 0; j < 8; j++)
		{
			if (crc & 0x01) crc = (crc >> 1) ^ 0x8C;
			else crc >>= 1;
		}
	}
	if(!(crc - scratchpad[8])) return true;
	else return false;
}

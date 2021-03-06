/*
 * SPI.c
 *
 * Created: 10/30/2020 12:44:55 PM
 *  Author: Mohamed Salem
 */ 


 #define F_CPU	8000000
 #include <util/delay.h>
#include "SPI.h"


void SPI_Master_Init(void)
{
	DIO_SetPinDir(DIO_PORTB , DIO_PIN4 , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN5 , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN6 , DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN7 , DIO_PIN_OUTPUT);
	
	SPI->SPCR = 0x53 ;
}

void SPI_Slave_Init(void)
{
	DIO_SetPinDir(DIO_PORTB , DIO_PIN4 , DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN5 , DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN6 , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB , DIO_PIN7 , DIO_PIN_INPUT);
	
	SPI->SPCR = 0x40;
}

void SPI_Master_Init_Trans(void)
{
	DIO_SetPinValue(DIO_PORTB , DIO_PIN4 , DIO_PIN_LOW);
}

void SPI_Master_Ter_Trans(void)
{
	DIO_SetPinValue(DIO_PORTB , DIO_PIN4 , DIO_PIN_HIGH);
}

uint8 SPI_Transiver(uint8 data)
{
	SPI_Master_Init_Trans();
	_delay_ms(50);
	
	SPI->SPDR = data ;
	
	while(GET_BIT(SPI->SPSR , 7) == 0);
	
	SPI_Master_Ter_Trans();
	
	return SPI->SPDR;
}


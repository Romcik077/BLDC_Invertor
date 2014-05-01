#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "global.h"
#include "hal/uart/uart.h"
#include "hal/psc/psc_drv.h"
#include "driver/bldc_ctrl/bldc_ctrl.h"
//#include "driver/rprintf/rprintf.h"

void clearTerminal(void);
//// Initialization of stdout
static int uart_putchar(char c, FILE* stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

const char clearT[] = {27, '[','2', 'J', 27, '[', 'H'};

int main(void)
{
//	char temp = 5;
//	char tempStr[16];

	sbi(DDRC, PC4);
	sbi(PORTC, PC4);

	// Initialization of communication
	uartInit();
	uartSetBaudRate(115200);
//	rprintfInit(uartSendByte);
	stdout = &mystdout;

	// Initialization of PSC module
	bldcInit();
	bldcSetPwmDuty(45);
	bldcStart();

//	 Send message
	clearTerminal();
	printf("Hello World!!!\n");
	_delay_ms(1000);

	while(1)
	{
////		clearTerminal();
////		temp = uartGetByte();
		if(bit_is_set(PINC, PC4))
			cbi(PORTC, PC4);
		else
			sbi(PORTC, PC4);
		_delay_ms(1000);
	}
}

inline void clearTerminal(void)
{
	putchar(12);
//	rprintfChar(12);
//	for(int i = 0; i < 7; i++)
//	{
//		putchar(clearT[i]);
//	}
}

static int uart_putchar(char c, FILE* stream)
{
	if (c == '\n')
		uart_putchar('\r', stream);
	uartSendByte(c);
	return 0;
}

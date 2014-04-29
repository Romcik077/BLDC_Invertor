/*! \file uart.c \brief UART driver with buffer support. */
// *****************************************************************************
//
// File Name	: 'uart.c'
// Title		: UART driver with buffer support
// Author		: Pascal Stang - Copyright (C) 2000-2002
// Created		: 11/22/2000
// Revised		: 06/09/2003
// Version		: 1.3
// Target MCU	: ATMEL AVR Series
// Editor Tabs	: 4
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
// *****************************************************************************

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

// UART global variables
// flag variables
volatile uint8_t uartReadyTx;			///< uartReadyTx flag
volatile uint8_t uartReadyRx;
volatile uint8_t uartDataRx;

typedef void (*voidFuncPtru08)(unsigned char);
volatile static voidFuncPtru08 UartRxFunc;

// enable and initialize the uart
void uartInit(void)
{
	// initialize user receive handler
	UartRxFunc = 0;

	// enable RxD/TxD and interrupts
	outb(UCR, BV(RXCIE)|BV(TXCIE)|BV(RXEN)|BV(TXEN));

	// set default baud rate
	uartSetBaudRate(UART_DEFAULT_BAUD_RATE);  
	// initialize states
	uartReadyTx = TRUE;
	uartReadyRx = FALSE;
	// enable interrupts
	sei();
}

// redirects received data to a user function
void uartSetRxHandler(void (*rx_func)(unsigned char c))
{
	// set the receive interrupt to run the supplied user function
	UartRxFunc = rx_func;
}

// set the uart baud rate
void uartSetBaudRate(uint32_t baudrate)
{
	// calculate division factor for requested baud rate, and set it
	uint16_t bauddiv = ((F_CPU+(baudrate*8L))/(baudrate*16L)-1);
	outb(UBRRL, bauddiv);
	#ifdef UBRRH
	outb(UBRRH, bauddiv>>8);
	#endif
}

// transmits a byte over the uart
void uartSendByte(uint8_t txData)
{
	// wait for the transmitter to be ready
	while(!uartReadyTx);
	// send byte
	outb(UDR, txData);
	// set ready state to FALSE
	uartReadyTx = FALSE;
	return;
}

// gets a single byte from the uart receive buffer (getchar-style)
int uartGetByte(void)
{
	if(uartReadyRx)
		return uartDataRx;
	else
		return -1;
}

// UART Transmit Complete Interrupt Handler
ISR(USART_TX_vect)
{
	// we're using single-byte tx mode
	// indicate transmit complete, back to ready
	uartReadyTx = TRUE;
}

// UART Receive Complete Interrupt Handler
ISR(USART_RX_vect)
{
	uint8_t c;
	
	// get received char
	c = inb(UDR);

	// if there's a user function to handle this receive event
	if(UartRxFunc)
	{
		// call it and pass the received data
		UartRxFunc(c);
	}
	else
	{
		uartDataRx = c;
		uartReadyRx = TRUE;
	}
}

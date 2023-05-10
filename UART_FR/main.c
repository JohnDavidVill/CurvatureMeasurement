#include <msp430.h>
#include "msp430fr2433.h"
#include <stdint.h>
#include <stdio.h>

#define BAUDRATE 9600 // Set the baud rate
#define UART_CLK 8000000 // Set the UART clock frequency

void uart_init() {

    UCA1CTLW0 |= UCSWRST; // Put the UART module in reset mode
    UCA1CTLW0 |= UCSSEL__SMCLK; // Set the clock source to SMCLK
    UCA1BRW = 8; // Set the baud rate
    UCA1MCTLW = 0xD600; // Set the modulation

    //PM5CTL0 &= ~LOCKLPM5;
    P1SEL1 &= ~BIT4;
    P1SEL0 &= BIT4;

    UCA1CTLW0 &= ~UCSWRST; // Take the UART module out of reset mode

}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	uart_init();

	int i;
	while(1) {

	    UCA1TXBUF = 0x69;
	    for(i = 0; i<10000; i++){}

	}

	return 0;
}

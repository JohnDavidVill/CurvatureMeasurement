#include <msp430.h>
#include "msp430fr2433.h"
#include <stdint.h>
#include <stdio.h>

#define BAUDRATE 9600 // Set the baud rate
#define UART_CLK 8000000 // Set the UART clock frequency

void uart_init() {

    UCA0CTLW0 = UCSWRST; // Put the UART module in reset mode
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set the clock source to SMCLK
    UCA0BRW = UART_CLK/BAUDRATE; // Set the baud rate
    UCA0MCTLW = UCBRF_0 | 0x01 | UCOS16; // Set the modulation
    UCA0CTLW0 &= ~UCSWRST; // Take the UART module out of reset mode

}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	uart_init();
	//printf("Hello\r\n");

	while(1) {

	    int i = 0;
	    while(i <= 100) {
	        printf(i);
	        //i++;
	    }

	    while(i >= 0) {
            printf(i);
            //i--;
        }

	}

	return 0;
}

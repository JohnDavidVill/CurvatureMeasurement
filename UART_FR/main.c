#include <msp430.h>
#include "msp430fr2433.h"
#include <stdint.h>
#include <stdio.h>

#define BAUDRATE 9600 // Set the baud rate
#define UART_CLK 8000000 // Set the UART clock frequency

void uart_init() {

    UCA0CTLW0 |= UCSWRST; // Put the UART module in reset mode
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set the clock source to SMCLK
    UCA0BRW = 8; // Set the baud rate
    UCA0MCTLW = 0xD600; // Set the modulation

    //PM5CTL0 &= ~LOCKLPM5;
    P1SEL1 &= ~BIT5;
    P1SEL0 &= BIT5;

    UCA0CTLW0 &= ~UCSWRST; // Take the UART module out of reset mode

}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    uart_init();

    int i;
    while(1) {

        UCA0TXBUF = 0x69;
        for(i = 0; i<10000; i++){}

    }

    return 0;
}

/*
 * PMODALS_setup.c
 *
 *      Author: John David Villarreal
 */

#include <msp430.h>
#include "msp430fr2433.h"
#include "PMODALS_setup.h"
#include <stdint.h>
#include <stdio.h>

#define P2_4_BIT BIT4 // SCLK pin for SPI communication
#define P2_5_BIT BIT6 // MISO pin for SPI communication

void spi_init() {

  P2SEL0 |= P2_4_BIT | P2_5_BIT;                    // Set P2.4 and P2.5 as SPI pins
  P2SEL1 |= P2_4_BIT | P2_5_BIT;

  UCA0CTL1 |= UCSWRST;                              // Disable Serial Interface
  UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;      // Configure SPI mode
  UCA0CTL1 |= UCSSEL_2;                             // Select SMCLK clock
  UCA0BR0 = 0x02;                                   // Set Frequency
  UCA0BR1 = 0x00;
  UCA0CTL1 &= ~UCSWRST;                             // Initialize USCI State Machine

}

void write(uint8_t data) {
    while(!(UCA0IFG & UCTXIFG));                    // Wait for transmit buffer to be empty
    UCA0TXBUF = data;                               // Write data to transmit buffer
}

void config_write_PMODALS(uint8_t config) {

    write(PMODALS_CONFIG_REG);                      // Send command saying we want to write to register
    write(config);                                  // Send configuration data

}

uint8_t read() {

    while(!(UCA0IFG & UCRXIFG));                    // Wait for receive buffer to be full
    return UCA0RXBUF;                               // Read and return data from receive buffer

}

uint16_t config_read_PMODALS() {

    write(PMODALS_DATA_REG);                        // Initialize to read data in data register
    write(0x00);                                    // Send the low dummy data

    uint16_t temp_read = read();
    uint16_t data = temp_read;                      // Read the upper 8 bits of data
    data = (data << 8) | temp_read;                 // Read the lower 8 bits of data

    return(data);

}

void uart_init() {

    UCA0CTLW0 = UCSWRST;                            // Reset UART
    UCA0CTLW0 |= UCSSEL__SMCLK;                     // Select SMCLK
    UCA0BRW = 52;                                   // Set baud rate to 4800
    UCA0MCTLW = UCA0BR0 | UCA0BR1;                // Set modulation UCBRSx=1, UCBRFx=0
    UCA0CTLW0 &= ~UCSWRST;                          // Exit Reset Mode

}

void uart_print(int data) {
    printf("AmbientA: %d\n", data);
}

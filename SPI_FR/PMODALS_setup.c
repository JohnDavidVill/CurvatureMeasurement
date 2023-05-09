/*
 * PMODALS_setup.c
 *
 *      Author: John David Villarreal
 */

#include <msp430.h>
#include "msp430fr2433.h"
#include "PMODALS_setup.h"
#include <stdint.h>

#define P2_4_BIT BIT4 // SCLK pin for SPI communication
#define P2_5_BIT BIT6 // MISO pin for SPI communication

void spi_init() {

  P2SEL0 |= P2_4_BIT | P2_5_BIT;                    // Set P2.4 and P2.5 as SPI pins
  P2SEL1 |= P2_4_BIT | P2_5_BIT;

  UCB0CTL1 |= UCSWRST;                              // Disable Serial Interface
  UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;      // Configure SPI mode
  UCB0CTL1 |= UCSSEL_2;                             // Select SMCLK clock
  UCB0BR0 = 0x02;                                   // Set Frequency
  UCB0BR1 = 0x00;
  UCB0CTL1 &= ~UCSWRST;                             // Initialize USCI State Machine

}

void write(uint8_t data) {
    while(!(UCB0IFG & UCTXIFG));                    // Wait for transmit buffer to be empty
    UCB0TXBUF = data;                               // Write data to transmit buffer
}

void config_write_PMODALS(uint8_t config) {

    write(PMODALS_CONFIG_REG);                      // Wait for transmit buffer to empty
    write(config);                                  // Write to transmit buffer

}

uint8_t read() {

    while(!(UCB0IFG & UCRXIFG));                    // Wait for receive buffer to be full
    return UCB0RXBUF;                               // Read data from receive buffer

}

uint16_t config_read_PMODALS() {

    write(PMODALS_DATA_REG);                        // Initialize to read data in data register
    write(0x00);                                    // Send the low dummy data

    uint16_t temp_read = read();
    uint16_t data = temp_read;                      // Read the upper 8 bits of data
    data = (data << 8) | temp_read;                 // Read the lower 8 bits of data

    return(data);

}

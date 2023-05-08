#include <msp430.h>
#include "msp430fr2433.h"
#include <stdint.h>

#define P2_1_CS BIT2 // Chip Select (CS) pin for PmodALS
#define P3_1_CS BIT3 // Chip Select (CS) pin for PmodALS

#define P2_4_BIT BIT4 // SCLK pin for SPI communication
#define P2_5_BIT BIT6 // MISO pin for SPI communication

void spi_init() {
  UCB0CTL1 |= UCSWRST;                              // Disable Serial Interface
  UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;      // Configure SPI mode
  UCB0CTL1 |= UCSSEL_2;                             // Select SMCLK as clock source
  UCB0BR0 = 0x02;                                   // Set clock divider to 2
  UCB0BR1 = 0x00;
  UCB0CTL1 &= ~UCSWRST;                             // Take SPI module out of reset state
}

uint16_t spi_read() {
  uint16_t data = 0;
  P2OUT &= ~P2_1_CS;                               // Set CS pin low to enable PmodALS
  UCB0TXBUF = 0x00;                                 // Send dummy byte to start SPI transaction
  while (!(UCB0IFG & UCRXIFG));                     // Wait for RX buffer to fill
  data = UCB0RXBUF;                                 // Read first byte of data
  UCB0TXBUF = 0x00;                                 // Send another dummy byte to continue SPI transaction
  while (!(UCB0IFG & UCRXIFG));                     // Wait for RX buffer to fill
  data = (data << 8) | UCB0RXBUF;                   // Read second byte of data
  P2OUT |= P2_1_CS;                                // Set CS pin high to disable PmodALS
  return data;
}


int main(void) {
  WDTCTL = WDTPW | WDTHOLD;         // Stop watchdog timer
  P2SEL0 |= P2_4_BIT | P2_5_BIT;     // Set P2.4 and P2.5 as SPI pins
  P2SEL1 |= P2_4_BIT | P2_5_BIT;

  P2DIR |= P2_1_CS;                // Set P2.1 as output for CS pin
  P2OUT |= P2_1_CS;                // Set CS pin high to start with
  spi_init();                       // Initialize SPI module

  int value = 0;
  while (1) {
    uint16_t data = spi_read();     // Read data from PmodALS
    // Process data here
    if(data != 0)
        value = data;
  }
}


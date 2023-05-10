#include <msp430.h>
#include "msp430fr2433.h"
#include <stdint.h>
#include "PMODALS_setup.h"

#define P2_1_CS BIT2 // Chip Select (CS) pin for PmodALS
#define P3_1_CS BIT3 // Chip Select (CS) pin for PmodALS


int main(void) {
  WDTCTL = WDTPW | WDTHOLD;         // Stop watchdog timer

  P2DIR |= P2_1_CS;                 // Set P2.1 as output for CS pin
  P2OUT |= P2_1_CS;                 // Set CS pin high to start with

  spi_init();                       // Initialize SPI module

  config_write_PMODALS(0x00);

  while(1) {

      uint16_t data = read();

      printf("Ambient_A: %d\n", data);
      __delay_cycles(1000);

  }

}

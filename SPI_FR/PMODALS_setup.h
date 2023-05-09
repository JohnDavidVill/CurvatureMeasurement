/*
 * PMODALS_setup.h
 *
 *      Author: John David Villarreal
 */

#ifndef PMODALS_SETUP_H_
#define PMODALS_SETUP_H_

#include <stdint.h>

#define PMODALS_CONFIG_REG 0x80
#define PMODALS_DATA_REG 0x81

uint16_t spi_read();
void spi_init();
void write(uint8_t data);
void config_write_PMODALS(uint8_t config);
uint8_t read();
uint16_t config_read_PMODALS();


#endif /* PMODALS_SETUP_H_ */

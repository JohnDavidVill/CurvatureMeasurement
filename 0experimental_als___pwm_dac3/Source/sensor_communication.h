#ifndef SENSOR_COMMUNICATION_H_
#define SENSOR_COMMUNICATION_H_

#include "i2c_driver.h"

#define OPT3001_SLAVE_ADDR  0x44
#define TMP117_SLAVE_ADDR   0x48
#define HDC2080_SLAVE_ADDR  0x40

uint32_t getOpt3001LuxData(void);
int8_t getTmp117TemperatureData(void);
uint8_t getHdc2080HumidityData(void);
void opt3001Init();
void hdc2080Init();
#endif /* SENSOR_COMMUNICATION_H_ */

#ifndef SENSOR_COMMUNICATION_H_
#define SENSOR_COMMUNICATION_H_

#include "i2c_driver.h"

#define OPT3001_SLAVE_ADDR  0x44

uint32_t getOpt3001LuxData(void);
void opt3001Init();
#endif /* SENSOR_COMMUNICATION_H_ */

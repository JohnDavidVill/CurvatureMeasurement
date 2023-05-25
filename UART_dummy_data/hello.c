/*
 * Author: John David Villarreal
 * Code meant for HiFive1-RevB Board
 *
 * This code is simply a UART example and shows how the MSP430 will implement the sensor readings
 * This code is meant to test the code for MatLab found in the repository
 *
 * This code simply counts down from 255 to 0 
 *
 */
#include <stdio.h>

void main() {

	for(int i = 255; i > 0; i--) {

		printf("A%d\r\n", i);
		for(int j = 0; j <= 1000000; j++);

	}

	for(int j = 0; j <= 10000000; j++);

	for(int i = 255; i > 0; i--) {

		printf("B%d\r\n", i);
		for(int j = 0; j <= 1000000; j++);

	}

}

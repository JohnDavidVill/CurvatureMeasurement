# Curvature Measurement
The goal of this project is to measure the curvature of the Earth by calculating the radius of the Earth given simulation data.
## Code
This repository contains four separate code sections. Two projects, SPI_FR and UART_FR, feature *Code Composer Studio Projects* of SPI and UART code attempted to be implemented with the sensors. *SerialScrape.m* is a MatLab file that collects sensor data or simulated data from a Serial Port and calculates the radius of the Earth as explained in **Calculations**. UART_dummy_data sends in sample UART data that simulates sensor data being fed in from the physical device.

## Calculations
The radius of the Earth can be found using the equation below.
$$
Radius = \frac{2}{t^2}*(\frac{86400}{2\pi})^2(\sqrt{h_2}-\sqrt{h_1})
$$
where $t$ is the timed elapsed between the sensor values reaching a set threshold, $h_2$ is the height of the second sensor off the ground, and $h_1$ is the height of the first sensor off of the ground.

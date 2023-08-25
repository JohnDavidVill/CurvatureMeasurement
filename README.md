# Curvature Measurement
The goal of this project is to measure the curvature of the Earth by calculating the radius of the Earth given simulation data.
## Code
The primary project, to be built on the MSP430FR2433, can be found under the 0experimental folder. *SerialScrape.m* is a MatLab file that collects sensor data from the MSP430 running the project, via a Serial Port, and calculates the radius of the Earth as explained in **Calculations**. 

## Calculations
The radius of the Earth can be found using the equation below.
$$
Radius = \frac{2}{t^2}*(\frac{86400}{2\pi})^2(\sqrt{h_2}-\sqrt{h_1})
$$
where $t$ is the timed elapsed between the sensor values reaching a set threshold, $h_2$ is the height of the second sensor off the ground, and $h_1$ is the height of the first sensor off of the ground.

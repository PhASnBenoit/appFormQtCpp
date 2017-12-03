#ifndef CSPIIOCTL_H
#define CSPIIOCTL_H

#include <fcntl.h>				//Needed for SPI port
#include <sys/ioctl.h>			//Needed for SPI port
#include <linux/spi/spidev.h>	//Needed for SPI port
#include <unistd.h>			//Needed for SPI port
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>

class CSpiIoctl
{
public:
    CSpiIoctl();
    int SpiOpenPort(int spi_device);
    int SpiClosePort(int spi_device);
    int SpiWriteAndRead(int spi_device, unsigned char *data, int length);
private:
    int spi_cs0_fd;				//file descriptor for the SPI device
    int spi_cs1_fd;				//file descriptor for the SPI device
    unsigned char spi_mode;
    unsigned char spi_bitsPerWord;
    unsigned int spi_speed;
};

#endif // CSPIIOCTL_H

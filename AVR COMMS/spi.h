/*SPI stands for Serial Peripheral Interface,
and it is a communication protocol used for short-distance communication between microcontrollers and peripheral devices.*/

#ifndef spi.h
#define spi.h

#include <avr32/io.h>

#define spi_timeOut 1000 //this is so that the spi doesn't get stuck in a loop and skips after the first 1000 iterations

typedef enum{
  SPI_ERROR =-1,
  SPI_OK = 0,
  SPI_ERROR_TIMEOUT = 1,
  SPI_ERROR_ARGUMENT,
  SPI_ERROR_OVERRUN,
  SPI_ERROR_MODE_FAULT,
  SPI_ERROR_OVERRUN_AND_MODE_FAULT
}spi_status_t;


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

typedef struct{
  unsigned char reg; //identifies which SPI register to use
  unsigned int baurate; //Stores the desires clock frequency in Hz (bits per second)
  unsigned char bits; //Sets the number of transmitted charecters, from 8-16
  unsigned char spck_delay; //sets delay between selecting slave and first clock pulse
  unsigned char trans_delay; //sets delay between successive spi transfers
  unsigned char stay_act; //decides if the slave-select signal stays active after a transfer
  unsigned char spi_mode; //selects spi clock mode
  unsigned char modfdis; //checks if SPI mode fault is disabled.
}spi_options_t;

#if defined(__AVR32__)
extern void spi_reset(volatile avr32_spi_t *spi); //declears a function that resets SPI periphs


#elif defined(__AVR_ATmega328P__)
void spi_reset (void);

#else
 #error "UNSUPPORTED MCU"
#endif

//loading...

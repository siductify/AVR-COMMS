/*SPI stands for Serial Peripheral Interface,
and it is a communication protocol used for short-distance communication between microcontrollers and peripheral devices.*/

#ifndef __SPI_H__
#define __SPI_H__

#include <avr32/io.h>

#define SPI_TIMEOUT 1000 //this is so that the spi doesn't get stuck in a loop and skips after the first 1000 iterations

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

extern spi_status_t spi_init_reset(volatile avr32_spi_t *spi);

extern spi_status_t spi_init_slave(volatile avr32_spi_t *spi, unsigned char bits, unsigned char spi_mode);

extern spi_status_t spi_init_test(volatile avr32_spi_t *spi); 

extern spi_status_t spi_initMaster(volatile avr32_spi_t *spi, const spi_options_t *options);

extern spi_status_t spi_selectionMode(volatile avr32_spi_t *spi, unsigned char variable_ps, unsigned char pcs_decode, unsigned char delay);

extern spi_status_t spi_selectChip(volatile avr32_spi_t *spi, unsigned char chip);

extern spi_status_t spi_unselectChip(volatile avr32_spi_t *spi, unsigned char chip);

extern spi_status_t spi_setUpChipReg(volatile avr32_spi_t *spi, const spi_options *options, unsigned int pba_hz); //configures SPI pheripheral using pheripheral bus clock frequency 

extern spi_status_t spi_enable(volatile avr32_spi_t *spi);

extern spi_status_t spi_disable(volatile avr32_spi_t *spi);

extern spi_status_t spi_is_enable(volatile avr32_spi_t *spi);

extern unsigned char spi_writeRegisterEmptyCheck(volatile avr32_spi_t *spi);

extern spi_status_t spi_write(volatile avr32_spi_t *spi, unsigned short data);

extern spi_status_t spi_variableSlaveWrite(volatile avr32_spi_t *spi, unsigned short data, unsigned char pcs, unsigned char lastxfer);

extern spi_status_t spi_writeEndCheck(volatile avr32_spi_t *spi);

extern spi_status_t spi_readRegisterFullCheck(volatile avr32_spi_t *spi);

extern spi_status_t spi_read(volatile avr32_spi_t *spi, unsigned short *data); // data points to a place where the function can store data collected from spi

extern unsigned char spi_getStatus(volatile avr32_spi_t *spi);

#endif

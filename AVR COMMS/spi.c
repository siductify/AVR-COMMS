#include <avr32/spi.h>

typedef union{
    unsigned long cr;
    avr32_spi_cr_t CR;
} u_avr32_spi_cr_t;

typedef union{
    unsigned long mr;
    avr32_mr_t MR;
} u_avr32_spi_mr_t;

typedef union{
    unsigned long tdr;
    avr_tdr_t TDR;
} u_avr32_spi_tdr_t;

typedef union{
    unsigned long ier;
    avr32_ier_t IER;
} u_avr32_spi_ier_t;

typedef union{
    unsigned long idr;
    avr32_idr_t IDR;
} u_avr32_spi_idr_t;

typedef union{
    unsigned long csr;
    avr32_csr_t CSR;
} u_avr32_spi_csr_t;

static int getBaudDiv(constant spi_options_t *options, unsigned int pba_hz) //baud rate determines hoe fast the Data transfer takes place.
{
    int baudDiv = (pba_hz + options->baudrate/2)/options->baudrate;
    if (baudDiv<=0 || baudDiv > 255){                                     //input validation 
        return -1;
    } 
    return baudDiv;
}

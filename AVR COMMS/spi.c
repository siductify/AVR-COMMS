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

void spi_reset(volatile spi32_avr_t *spi){
    spi->cr = AVR32_SPI_CR_SWRT_MASK;   //activates the software reset command
}
spi_status_t spi_initSlave(volatile avr32_spi_t *spi, unsigned char bits, unsigned char spi_mode)
{
    if(spi_mode > 3 || bits<8 || bits>16){
        return SPI_ERROR_ARGUMENT;
    }
    //reset
    spi->cr = AVR32_SPI_CR_SWRST_MASK;
    //
    ((spi_mode>>1)<<AVR32_SPI_CSR0_CPOL_OFFSET)|              //extracts CPOL from spi_mode, shifts it into register's CPOL field and writes the result in CSR0
    (((spi_mode & 0x1)^0x1)<<AVR32_SPI_CSR0_NCPHA_OFFSET)|   //extracting the lowest bit (0x1 is the hexadecimal for 1)and flipping that bit
    ((bits-8)<<AVR32_SPICSR0_BITS_OFFSET);

    return SPI_OK;
}

spi_status_t spi_initTest(volatile avr32_spi_t *spi){
    spi->cr = AVR32_SPI_CR_SWRST_MASK;                                        //software reset command
    spi->mr |= AVR32_SPI_MR_MSTR_MASK|                                       //sets the master mode bit and 
               AVR32_SPI_MR_LLB_MASK;                                       //local feedback loop bit. the | operation combines both into 1 value
    return SPI_OK;
}
//loading...

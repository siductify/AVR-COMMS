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
    
}

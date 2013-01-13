/**
 * \file
 *
 *   spi1 write routines
 *
 * \author
 *
 *   Semen Tarakanov tarakanov.sv@gmail.com
 *   
 */
#include <stdlib.h>
#include <string.h>

#include "cc253x.h"
#include "dev/uart1.h"

#if (USART1_ENABLE && !USART1_UART_ENABLE)
/*---------------------------------------------------------------------------*/
/* SPI1 initialization */
void
spi1_init()
{

#if !USART1_ALTERNATIVE
  PERCFG &= ~PERCFG_U1CFG; /*initial location = P0.5-2*/
#if SPI1_SLAVE_ENABLE
  U1CSR |= UCSR_SLAVE; /*Set SPI1 to slave*/
  P0SEL |= 0x3C;    /*peripheral select for MI, MO, C, SS*/
  P0DIR |= 0x20;    /*MI out*/
  P0DIR &= ~0x1C;   /*MO, C, SS in*/
#else
  U1CSR &= ~UCSR_SLAVE; /*Set SPI1 to master*/
  P0SEL |= 0x38;    /*peripheral select for MI, MO, C*/
  P0DIR |= 0x18;    /*MO, C out*/
  P0DIR &= ~0x20;   /*MI in*/
#endif
#else
  PERCFG |= PERCFG_U1CFG;  /*alternative location = P1.7-4*/
#if SPI1_SLAVE_ENABLE
  U1CSR |= UCSR_SLAVE; /*Set SPI1 to slave*/
  P1SEL |= 0xF0;    /*peripheral select for MI, MO, C, SS*/
  P1DIR |= 0x80;    /*MI out*/
  P1DIR &= ~0x70;   /*MO, C, SS in*/
#else
  U1CSR &= ~UCSR_SLAVE; /*Set SPI1 to master*/
  P1SEL |= 0xE0;    /*peripheral select for MI, MO, C*/
  P1DIR |= 0x60;    /*MO, C out*/
  P1DIR &= ~0x80;   /*MI in*/
#endif
#endif /*USART_ALTERNATIVE*/

 /*take 115200 bps for the test*/
  UART_SET_SPEED(1, UART_115_M, UART_115_E);

#if SPI1_CPOL /*SPI clock polarity */
  U1GCR |= UGCR_CPOL; /* Positive clock polarity */
#else
  U1GCR &= ~UGCR_CPOL; /*Negative clock polarity*/
#endif

#if SPI1_CPHA  /* SPI Clock phase */
  U1GCR |= UGCR_CPHA;
#else
  U1GCR &= ~UGCR_CPHA;
#endif

#if SPI1_ORDER
  U1GCR |= UGCR_ORDER; /* MSB first */
#else
  U1GCR &= ~UGCR_ORDER; /* LSB first */
#endif

  U1CSR &= ~UCSR_MODE; /* SPI mode */
  U1DBUF = 0;
  UTX1IE = 1;

}
/*---------------------------------------------------------------------------*/
/* Write one byte over the SPI1. */
void
spi1_writeb(uint8_t byte)
{
  UTX1IF = 0;
  U1DBUF = byte;
  while(!UTX1IF); /* Wait until byte has been transmitted. */
  UTX1IF = 0;
}
/*---------------------------------------------------------------------------*/
#endif

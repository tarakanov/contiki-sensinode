#ifndef UART_1_H
#define UART_1_H

#include "contiki-conf.h"

#include "cc253x.h"
#include "sfr-bits.h"
#include "8051def.h"
#include "uart.h"

/*---------------------------------------------------------------------------*/
/* USART1 Enable - Disable */
#ifdef USART1_CONF_ENABLE
#define USART1_ENABLE USART1_CONF_ENABLE
#else
#define USART1_ENABLE 0
#endif
/*---------------------------------------------------------------------------*/
/* Choosing initial (0) or alternative location (1) for peripheral pins */
#ifdef USART1_CONF_ALTERNATIVE
#define USART1_ALTERNATIVE USART1_CONF_ALTERNATIVE
#else
#define USART1_ALTERNATIVE 0
#endif
/*---------------------------------------------------------------------------*/
/* Select SPI (0) or UART (1) */
#ifdef USART1_CONF_UART_ENABLE
#define USART1_UART_ENABLE USART1_CONF_UART_ENABLE
#else
#define USART1_UART_ENABLE 0
#endif
/*---------------------------------------------------------------------------*/
/* Select SPI master (0) or slave (1) */
#ifdef SPI1_SLAVE_CONF_ENABLE
#define SPI1_SLAVE_ENABLE SPI1_SLAVE_CONF_ENABLE
#else
#define SPI1_SLAVE_ENABLE 0
#endif
/*---------------------------------------------------------------------------*/
/* Select Clock polarity: Negative (0) or slave (1) */
#ifdef SPI1_CPOL_CONF
#define SPI1_CPOL SPI1_CPOL_CONF
#else
#define SPI1_CPOL 0
#endif
/*---------------------------------------------------------------------------*/
/* Select Clock Phase: 
 * (0): Data is output on MOSI when Clock goes from CPOL inverted to CPOL, and
 *      data input is sampled on MISO when Clock goes from CPOL to CPOL inv 
 * (1): Data is output on MOSI when Clock goes from CPOL to CPOL inverted, and
 *      data input is sampled on MISO when Clock goes from CPOL inv to CPOL 
 */
#ifdef SPI1_CPHA_CONF
#define SPI1_CPHA SPI1_CPHA_CONF
#else
#define SPI1_CPHA 0
#endif
/*---------------------------------------------------------------------------*/
/* Bit order for transfers: LSB first (0) or MSB first (1) */
#ifdef SPI1_ORDER_CONF
#define SPI1_ORDER SPI1_ORDER_CONF
#else
#define SPI1_ORDER 0
#endif

/*---------------------------------------------------------------------------*/
#if USART1_ENABLE
/* USART1_USART Function Declarations */
#if USART1_UART_ENABLE
void uart1_init();
void uart1_writeb(uint8_t byte);

void uart1_set_input(int (* input)(unsigned char c));
#if UART1_CONF_WITH_INPUT
void uart1_rx_isr(void) __interrupt(URX1_VECTOR);
/* Macro to turn on / off UART RX Interrupt */
#define UART1_RX_INT(v) do { URX1IE = v; } while(0)
#else
#define UART1_RX_INT(v)
#endif /* UART1_CONF_WITH_INPUT */

#else  /* USART1_USART_ENABLE */
#define uart1_init(...)
#define uart1_writeb(...)
#define uart1_set_input(...)
#define UART1_RX_INT(v)
/*---------------------------------------------------------------------------*/
/* USART1_SPI Function Declarations */
void spi1_init();
void spi1_writeb(uint8_t byte);

#endif /* USART1_USART_ENABLE */
#endif /* USART1_ENABLE */
#endif /* UART_1_H */

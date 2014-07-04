/* 
 * File:   uart.h
 * Author: kilnaar
 *
 * Created on July 3, 2014, 6:13 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

void uart1_init(void);
void uart1_putc(char ch);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */


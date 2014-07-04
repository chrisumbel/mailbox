/* 
 * File:   spi.h
 * Author: kilnaar
 *
 * Created on July 3, 2014, 6:27 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

void spi_init(void);
void spi_transmit_async(unsigned char * data, unsigned int length);
void spi_transmit_sync(unsigned char * data, unsigned int length);
void spi_transfer_sync(unsigned char * dataout, unsigned char * datain, unsigned int length);
unsigned char spi_fast_shift(unsigned char data);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */


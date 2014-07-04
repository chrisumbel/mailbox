/*
 *      2013 Elia Ritterbusch
 *      http://eliaselectronics.com
 *      2014 Chris Umbel
 *      http://www.chriumbel.com
 *
 *      This work is licensed under the Creative Commons Attribution 3.0 Unported License.
 *      To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
 */
#include <xc.h>
#include <p24FV16KM202.h>
#include "spi.h"
#include "hardware_configuration.h"

void spi_init(void) {
    // disable MSSP
    SSP1CON1bits.SSPEN = 0;
    // SDI1 set
    WL_MISO_TRIS = 1;
    // SS1 set
    WL_CSN_TRIS = 0;
    // SDO1 cleared
    // SCK1 cleared
    WL_MOSI_TRIS = 0;
    WL_SCK_TRIS = 0;

    // SPI mode 0
    SSP1CON1bits.CKP = 0; // Idle state for clock is a low level
    SSP1STATbits.CKE = 1; // Transmit occurs on transition from active to Idle clock state
    SSP1STATbits.SMP = 1; // Input data sampled at end of data output time (took me 5 friggin' hours)
    SSP1CON1bits.SSPM = 0; // SPI Master mode, SCK = FOSC/2
    SSP1CON1bits.SSPEN = 1; // enable MSSP1
}

void spi_transmit_async(unsigned char * data, unsigned int length) {
    unsigned char tmp;

    while(length) {
	SSP1BUF = *data;
        tmp = SSP1BUF; // read out data
        length--;
	data++;
    }
}

void spi_transmit_sync(unsigned char * data, unsigned int length){
    unsigned char tmp;

    while(length) {
	SSP1BUF = *data;
	while(!SSP1STATbits.BF); // wait for buffer full
        tmp = SSP1BUF; // read out data
        length--;
	data++;
    }
}

void spi_transfer_sync(unsigned char * dataout, unsigned char * datain, unsigned int length){
    while(length){
	SSP1BUF = *dataout;
	while(!SSP1STATbits.BF); // wait for buffer full
        *datain = SSP1BUF; // read out data
        length--;
	dataout++;
        datain++;
    }
}

unsigned char spi_fast_shift(unsigned char data){
    SSP1BUF = data;
    while(!SSP1STATbits.BF); // wait for buffer full
    return SSP1BUF;
}

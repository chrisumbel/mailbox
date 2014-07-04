
#include <p24FV16KM202.h>
#include "uart.h"

void uart1_init(void) {
    TRISBbits.TRISB7 = 0;

    U1BRG = 25;                     //Baud rate set to 9600
    U1STA = 0;

    U1MODE = 0;                     //8-bit data, no parity, 1 stop bit
    U1MODEbits.UARTEN = 1;          //enable the module

    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 1;         //interrupt generated transmit is complete
    IFS0bits.U1RXIF = 0;            //clear receive interrupt flag

    U1STAbits.UTXEN = 1;            //enable transmission
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
}

void uart1_putc(char ch) {
    while(U1STAbits.UTXBF);         //transmit only if TX buffer is empty
    U1TXREG = ch;
}

void uart1_puts(char *s) {
    while(*s) {
        uart1_putc(*s);
        s++;
    }
}

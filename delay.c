#include <p24FV16KM202.h>
#include "delay.h"

void __delay_tick(int t) {
    int pr1 = t;

    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1  = pr1;
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCKPS = 0b00;
    IEC0bits.T1IE = 0;
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;

    while(!IFS0bits.T1IF);

    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}

void __delay_ms(int ms) {
    int pr1 = 31.25 * ms;

    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1  = pr1;
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCKPS = 0b00;
    IEC0bits.T1IE = 0;
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;

    while(!IFS0bits.T1IF);

    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}

void __delay_10ms() {
    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1  = 0x0c35;
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCKPS = 0b00;
    IEC0bits.T1IE = 0;
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;

    while(!IFS0bits.T1IF);

    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}

void __delay_s(int s) {
    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1  = 0x7a12;
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCKPS = 0b00;
    IEC0bits.T1IE = 0;
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;

    while(!IFS0bits.T1IF);

    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}

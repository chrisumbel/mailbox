#include <xc.h>
#include <p24FV16KM202.h>

#include "hardware_configuration.h"
#include "switch.h"
#include "delay.h"

extern volatile char alert;
extern volatile int until_eligable;

void switch_init(void) {
    SWITCH_TRIS = 1;

    /* have to read these to update state */
    volatile int t1 = PORTB;
    volatile int t2 = LATB;
    t1 = PORTB;

    if(SWITCH_READ) {
        INTCON2bits.INT1EP = 1;
    } else {
        INTCON2bits.INT1EP = 0;
    }

    IFS1bits.INT1IF = 0;
    IPC5bits.INT1IP = 6;
    IEC1bits.INT1IE = 1;
}

void __attribute__((interrupt, auto_psv)) _ISR _INT1Interrupt(void) {
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 0;

    if(INTCON2bits.INT1EP == 1 && !until_eligable) {
        alert = 1;
    }

    until_eligable = 2;
}

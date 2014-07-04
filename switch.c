#include <xc.h>
#include <p24FV16KM202.h>

#include "hardware_configuration.h"
#include "switch.h"

extern volatile char alert;

void switch_init(void) {
    INTCON2bits.INT1EP = 1;
    IFS1bits.INT1IF = 0;
    IPC5bits.INT1IP = 6;
    IEC1bits.INT1IE = 1;
}

void __attribute__((interrupt, auto_psv)) _ISR _INT1Interrupt(void) {
    alert = 1;
    IFS1bits.INT1IF = 0;
}
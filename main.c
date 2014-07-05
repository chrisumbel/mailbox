#include <xc.h>
#include <p24FV16KM202.h>
#include <stdlib.h>
#include "hardware_configuration.h"
#include "delay.h"
#include "switch.h"
#include "wl_module.h"
#include "nRF24L01.h"

#pragma config FNOSC = FRC
#pragma config FWDTEN = OFF

#define DEVICE_ID 0x0002

volatile char alert;
volatile char clear;
volatile int until_eligable = 0;

void status_timer_run(void) {
    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1  = 0x7a12;
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 0b10;
    T1CONbits.TCKPS = 0b01;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;
}

void main() {
    WL_POWER_LAT = 0;
    WL_POWER_TRIS = 0;
    
    FLOOD_LAT = 0;
    FLOOD_TRIS = 0;

#ifdef SWITCH_ANS
    SWITCH_ANS = 0;
#endif
    SWITCH_TRIS = 1;

    alert = 0;
    clear = 0;

    unsigned char payload[wl_module_PAYLOAD];

    payload[0] = DEVICE_ID << 8;
    payload[1] = DEVICE_ID;
    
    logging_init();
    
    while(1) {
        FLOOD_LAT = 0;
        switch_init();
        status_timer_run();
        Sleep();

        if(alert) {
            FLOOD_LAT = 1;

            logging_log("alert");

            payload[2] = 0x01;
            wl_module_radio_enable();
            wl_module_send(payload, wl_module_PAYLOAD);
            wl_module_radio_disable();
        } else if (clear) {
            logging_log("clear");
            payload[2] = 0x00;

            wl_module_radio_enable();
            wl_module_send(payload, wl_module_PAYLOAD);
            wl_module_radio_disable();
        }

        clear = alert = 0;
    }
}


void __attribute__((interrupt, auto_psv)) _ISR _T1Interrupt(void) {
    /* have to read these to update state */
    volatile int t1 = PORTB;
    volatile int t2 = LATB;
    t1 = PORTB;

    if(SWITCH_READ) {
        clear = 1;
    } else {
        alert = 1;
    }

    if(until_eligable) {
        until_eligable--;
    }

    IFS0bits.T1IF = 0;
}
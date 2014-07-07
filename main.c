#include <xc.h>
#include <p24FV16KM202.h>
#include <stdlib.h>
#include "hardware_configuration.h"
#include "delay.h"
#include "switch.h"
#include "wl_module.h"
#include "nRF24L01.h"

#pragma config FNOSC = FRC
#pragma config FWDTEN = ON, WDTPS = PS32768, FWPSA = PR32

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

unsigned char payload[wl_module_PAYLOAD];

void payload_send() {
    wl_module_radio_enable();

    wl_module_CSN_lo; // Pull down chip select
    int status = spi_fast_shift(NOOP); // Read status register
    wl_module_CSN_hi; // Pull up chip select

    if (status & (1<<TX_DS)){ // IRQ: Package has been sent
                wl_module_config_register(STATUS, (1<<TX_DS)); //Clear Interrupt Bit
    }

    if (status & (1<<MAX_RT)){ // IRQ: Package has not been sent, send again
            wl_module_config_register(STATUS, (1<<MAX_RT));	// Clear Interrupt Bit
            wl_module_CE_hi; // Start transmission
            __delay_ms(1);
            wl_module_CE_lo;
    }

    wl_module_tx_flush();

    wl_module_send(payload, wl_module_PAYLOAD);
    wl_module_radio_disable();
}

unsigned int post_post_scalar;

void main() {
    WL_POWER_LAT = 0;
    WL_POWER_TRIS = 0;

#ifdef SWITCH_ANS
    SWITCH_ANS = 0;
#endif
    SWITCH_TRIS = 1;

    alert = 0;
    clear = 0;
    post_post_scalar = 0;

    payload[0] = DEVICE_ID << 8;
    payload[1] = DEVICE_ID;
    payload[2] = 0x01;

    logging_init();
    payload_send();

    while(1) {
        switch_init();
        status_timer_run();
        Sleep();

        if(alert) {
            logging_log("alert");

            payload[2] = 0x01;
            payload_send();
        } else if (clear) {
            logging_log("clear");
            payload[2] = 0x00;

            payload_send();
        }

        clear = alert = 0;
        ClrWdt();
    }
}


void __attribute__((interrupt, auto_psv)) _ISR _T1Interrupt(void) {
    post_post_scalar++;

    if(post_post_scalar >= 1) {
         /* have to read these to update state */
        volatile int t1 = PORTB;
        volatile int t2 = LATB;
        t1 = PORTB;

        if(SWITCH_READ) {
            clear = 1;
        } else {
            alert = 1;
        }

        post_post_scalar = 0;
    }

    if(until_eligable) {
        until_eligable--;
    }

    IFS0bits.T1IF = 0;
}
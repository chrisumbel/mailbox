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

volatile char alert;

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

    unsigned char payload[wl_module_PAYLOAD];

    payload[0] = 0x00;
    payload[1] = 0x01;
    payload[2] = 0x02;
    payload[3] = 0x03;
    payload[4] = 0x04;
    
    logging_init();
    switch_init();

    while(1) {
        FLOOD_LAT = 0;
        Sleep();
        FLOOD_LAT = 1;

        if(alert) {
            wl_module_radio_enable();
            wl_module_send(payload, wl_module_PAYLOAD);
            wl_module_radio_disable();

            alert = 0;
        }
    }
}


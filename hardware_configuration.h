/* 
 * File:   hardware_configuration.h
 * Author: kilnaar
 *
 * Created on July 3, 2014, 6:36 PM
 */

#ifndef HARDWARE_CONFIGURATION_H
#define	HARDWARE_CONFIGURATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FLOOD_TRIS  TRISAbits.TRISA2
#define FLOOD_LAT   LATAbits.LATA2

#define SWITCH_TRIS TRISBbits.TRISB14   // pin 25
#define SWITCH_ANS  ANSBbits.ANSB14     // pin 25

#define WL_CE_TRIS      TRISBbits.TRISB5  // pin 14
#define WL_CSN_TRIS     TRISBbits.TRISB15 // pin 26
#define WL_SCK_TRIS     TRISBbits.TRISB11 // pin 22
#define WL_MOSI_TRIS    TRISBbits.TRISB13 // pin 24
#define WL_MISO_TRIS    TRISBbits.TRISB10 // pin 21
// #define WL_IRQ_TRIS     TRISBbits.TRISB14 // pin 25
#define WL_POWER_TRIS     TRISBbits.TRISB6  // pin 15

#define WL_CE_LAT      LATBbits.LATB5  // pin 14
#define WL_CSN_LAT     LATBbits.LATB15 // pin 26
#define WL_SCK_LAT     LATBbits.LATB11 // pin 22
#define WL_MOSI_LAT    LATBbits.LATB13 // pin 24
#define WL_POWER_LAT     LATBbits.LATB6  // pin 15
    
#ifdef	__cplusplus
}
#endif

#endif	/* HARDWARE_CONFIGURATION_H */


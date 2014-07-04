/* 
 * File:   delay.h
 * Author: kilnaar
 *
 * Created on July 3, 2014, 6:14 PM
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

void __delay_ms(int ms);
void __delay_10ms();
void __delay_s(int s);
void __delay_tick(int t);

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */


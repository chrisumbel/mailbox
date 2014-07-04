/* 
 * File:   logging.h
 * Author: kilnaar
 *
 * Created on July 3, 2014, 10:27 PM
 */

#ifndef LOGGING_H
#define	LOGGING_H

#ifdef	__cplusplus
extern "C" {
#endif

void logging_init();
void logging_log(unsigned char *message);

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGING_H */


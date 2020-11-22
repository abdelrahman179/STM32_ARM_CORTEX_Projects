/*****************************************************/
 /* Author      : AbdElrahman I.Zaki                 */
 /* Version     : v01                                */
 /* date        : 14/8/2020                          */
/*****************************************************/
#ifndef _DELAY_H_
#define _DELAY_H_

/* To assure that SYSTEMCORECLOCK is not defined anywhere else */
#ifndef SYSTEMCORECLOCK 
	#define SYSTEMCORECLOCK 8000000
#endif

/* i.e: 6000 for keil and 12000 for eclipce
   System clock must be defined first if not the default is 8 MHZ */
void delay_ms(u32 ms);


#endif 
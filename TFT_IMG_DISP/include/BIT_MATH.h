/*********************************************************/
/* Author : AbdElrahman I.Zaki                           */
/* Date   : 29 July 2020                                 */
/* Version: V01                                          */
/* Desc.  : Bit Math Header File                         */
/*********************************************************/

/* Header File Guard to define the header file if it's not define
Otherwise, it will not be defined to avoid multiple header file definitions */

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BIT)    VAR |=  (1 << (BIT))
#define CLR_BIT(VAR,BIT)    VAR &= ~(1 << (BIT))
#define GET_BIT(VAR,BIT)    ((VAR >> BIT) & 1)
#define TOG_BIT(VAR,BIT)    VAR ^=  (1 << (BIT))

#endif
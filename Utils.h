/*****************************************************************************
* Task: AVR_DRIVERS
* File Name: Utils.h
* Description: File for Important Macros
* Author: Amr Mohamed
* Date: 8/7/2021
******************************************************************************/

#ifndef __UTILS__
#define __UTILS__


#define GET_BIT(reg,bit)	((reg>>bit) & 1)
#define SET_BIT(reg,bit)	(reg |= (1<<bit))
#define CLR_BIT(reg,bit)	(reg &= ~(1<<bit))
#define TOG_BIT(reg,bit)    (reg^= (1<<bit))


#endif /* __UTILS__ */
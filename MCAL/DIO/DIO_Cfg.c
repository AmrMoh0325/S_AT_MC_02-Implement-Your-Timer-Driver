/*****************************************************************************
* Task: AVR_DRIVERS
* File Name: DIO.h
* Description: configuration File for DIO driver
* Author: Amr Mohamed
* Date: 8/7/2021
******************************************************************************/

#include "DIO.h"

//array of micro controller pins and the configuration of each one 
const enuDIOPinType_t DIOConfigParameters[DIO_MC_PINS] =
{	
   INPLUP,      /* Port A Pin 0 ADC0*/
	OUTPUT,      /* Port A Pin 1 ADC1*/
	OUTPUT,      /* Port A Pin 2 */
	OUTPUT,      /* Port A Pin 3 */
	OUTPUT,      /* Port A Pin 4 */
	OUTPUT,      /* Port A Pin 5 */
	OUTPUT,      /* Port A Pin 6 */
	OUTPUT,      /* Port A Pin 7 */
	OUTPUT,      /* Port B Pin 0   / */
	OUTPUT,      /* Port B Pin 1   /*/
	INFREE,		 /* Port B Pin 2 / INT2*/
	OUTPUT,		 /* Port B Pin 3   /OC0*/
	OUTPUT,		 /* Port B Pin 4 */
	OUTPUT,		 /* Port B Pin 5 */
	OUTPUT,		 /* Port B Pin 6 */
	OUTPUT,		 /* Port B Pin 7 */
	OUTPUT,		 /* Port C Pin 0 */
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT,		 /* Port C Pin 3 */
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */
	OUTPUT,		 /* Port C Pin 6 */
	OUTPUT,		 /* Port C Pin 7 */
	OUTPUT,		 /* Port D Pin 0 */
	OUTPUT,		 /* Port D Pin 1 */
   OUTPUT,      /* Port D Pin 2 /INT0*/
	OUTPUT,      /* Port D Pin 3 / INT1 */
	OUTPUT,   	 /* Port D Pin 4 */
	OUTPUT,		 /* Port D Pin 5 */
	OUTPUT,		 /* Port D Pin 6 /   ICP*/
	OUTPUT		 /* Port D Pin 7 */
	
};

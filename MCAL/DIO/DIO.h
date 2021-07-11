/*****************************************************************************
* Task: AVR_DRIVERS
* File Name: DIO.h
* Description: File for DIO.c prototypes
* Author: Amr Mohamed
* Date: 8/7/2021
******************************************************************************/

#ifndef __DIO__
#define __DIO__


#include "DataTypes.h"
#include "Utils.h"

#define DIO_MC_PINS    ALL_PINS

typedef enum {OUTPUT,INPLUP,INFREE} enuDIOPinType_t;
typedef enum {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
              PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
              PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
              PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,ALL_PINS} enuDIOPinNo_t;

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize all the DIO groups according to the configuration
************************************************************************************/
enuErrorStatus_t DIO_Init(void);

/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t u8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to write a digital value into the selected DIO u8pin
************************************************************************************/
enuErrorStatus_t DIO_Write(enuDIOPinNo_t PinId, uint8_t u8Data);

/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t* pu8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to read a digital value from the selected DIO u8pin
************************************************************************************/
enuErrorStatus_t DIO_Read(enuDIOPinNo_t PinId, uint8_t* pu8Data);

/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t* pu8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to toggle the digital value of the selected DIO pin
************************************************************************************/
enuErrorStatus_t DIO_Toggle(enuDIOPinNo_t PinId);

#endif /* __DIO__ */
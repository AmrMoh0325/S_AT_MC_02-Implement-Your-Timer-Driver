/*****************************************************************************
* Task: AVR_DRIVERS
* File Name: DIO.c
* Description: Functions for DIO driver
* Author: Amr Mohamed
* Date: 8/7/2021
******************************************************************************/
//included files
#include "Register.h"
#include "Utils.h"
#include "DataTypes.h"
#include "DIO.h"

//Private macros used within the driver 
#define DIO_PORT_NO  4u
#define DIO_PINS_NO  8u

#define M_PORTA  0
#define M_PORTB  1
#define M_PORTC  2
#define M_PORTD  3

extern const enuDIOPinType_t DIOConfigParameters[DIO_MC_PINS];

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize all the DIO groups according to the configuration
************************************************************************************/
enuErrorStatus_t DIO_Init(void)
{
   uint8_t u8i;
   uint8_t u8port,u8pin;
   //traverse the array of pins the user have used
   for (u8i=0;u8i<DIO_MC_PINS;u8i++)
   {
      //calculate the port and pin number for each pin
      u8port=u8i / DIO_PINS_NO;
      u8pin=u8i % DIO_PINS_NO;
      
      //if port number is invalid
      if (u8port>=DIO_PORT_NO)
      {
         //return FAIL
         return 0;
      }
      
      //decide which port are we working with
      switch (u8port)
      {
         case M_PORTA:
            //clear the pin bit in the DDRx and PORTx registers of each port  
            CLR_BIT(DDRA_R,u8pin);
            CLR_BIT(PORTA_R,u8pin);
            //if the pin is set as output
            if(DIOConfigParameters[u8i]==OUTPUT)
            {
               //set its equivalent bit in the DDRx register
               SET_BIT(DDRA_R,u8pin);
            }
            else
            {
               //if the pin is set as input, check if its pullup resistor will be used
               if (DIOConfigParameters[u8i]==INPLUP);
               {
                  //if so, set it's equivalent bit in the PORTx register
                  SET_BIT(PORTA_R,u8pin);
               }
            }
         break;

         case M_PORTB:
            //clear the pin bit in the DDRx and PORTx registers of each port  
            CLR_BIT(DDRB_R,u8pin);
            CLR_BIT(PORTB_R,u8pin);
            //if the pin is set as output
            if(DIOConfigParameters[u8i]==OUTPUT)
            {
               //set its equivalent bit in the DDRx register
               SET_BIT(DDRB_R,u8pin);
            }
            else
            {
               //if the pin is set as input, check if its pullup resistor will be used
               if (DIOConfigParameters[u8i]==INPLUP);
               {
                  //if so, set it's equivalent bit in the PORTx register
                  SET_BIT(PORTB_R,u8pin);
               }
            }
         break;

         case M_PORTC:
            //clear the pin bit in the DDRx and PORTx registers of each port  
            CLR_BIT(DDRC_R,u8pin);
            CLR_BIT(PORTC_R,u8pin);
            //if the pin is set as output
            if(DIOConfigParameters[u8i]==OUTPUT)
            {
               //set its equivalent bit in the DDRx register
               SET_BIT(DDRC_R,u8pin);
            }
            else
            {
               //if the pin is set as input, check if its pullup resistor will be used
               if (DIOConfigParameters[u8i] == INPLUP);
               {
                  //if so, set it's equivalent bit in the PORTx register
                  SET_BIT(PORTC_R,u8pin);
               }
            }
         break;

         case M_PORTD:
            //clear the pin bit in the DDRx and PORTx registers of each port  
            CLR_BIT(DDRD_R,u8pin);
            CLR_BIT(PORTD_R,u8pin);
            //if the pin is set as output
            if(DIOConfigParameters[u8i]==OUTPUT)
            {
               //set its equivalent bit in the DDRx register
               SET_BIT(DDRD_R,u8pin);
            }
            else
            {
               //if the pin is set as input, check if its pullup resistor will be used
               if (DIOConfigParameters[u8i]==INPLUP);
               {
                  //if so, set it's equivalent bit in the PORTx register
                  SET_BIT(PORTD_R,u8pin);
               }
            }
         break;         
      }    
   }
   //return success status
   return SUCCESS;
}



/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t u8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to write a digital value into the selected DIO u8pin
************************************************************************************/
enuErrorStatus_t DIO_Write(enuDIOPinNo_t PinId, uint8_t u8Data)
{
   uint8_t u8port,u8pin;
   //calculate the port and pin number of the selected object
   u8port=PinId / DIO_PINS_NO;
   u8pin =PinId % DIO_PINS_NO;
   
   //if port number is invalid or the pin is set as input 
   if(u8port >= DIO_PORT_NO || DIOConfigParameters[PinId] != OUTPUT)
   {
      //return error status
      return ERROR;
   }
   
   else
   {
      //select the calculated port 
      switch(u8port)
      {
         case M_PORTA:
            //clear the pin's equivalent bit in the PORTx Register
            CLR_BIT(PORTA_R,u8pin);
            //if we want to apply 5V to the pin
            if (u8Data)
            {
               //set the pin's equivalent bit in the PORTx Register
               SET_BIT(PORTA_R,u8pin);
            }
         break;

         case M_PORTB:
            //clear the pin's equivalent bit in the PORTx Register
            CLR_BIT(PORTB_R,u8pin);
            //if we want to apply 5V to the pin
            if (u8Data)
            {
               //set the pin's equivalent bit in the PORTx Register
               SET_BIT(PORTB_R,u8pin);
            }
         break;

         case M_PORTC:
            //clear the pin's equivalent bit in the PORTx Register
            CLR_BIT(PORTC_R,u8pin);
            //if we want to apply 5V to the pin
            if (u8Data)
            {
               //set the pin's equivalent bit in the PORTx Register
               SET_BIT(PORTC_R,u8pin);
            }
         break;

         case M_PORTD:
            //clear the pin's equivalent bit in the PORTx Register
            CLR_BIT(PORTD_R,u8pin);
            //if we want to apply 5V to the pin
            if (u8Data)
            {
               //set the pin's equivalent bit in the PORTx Register
               SET_BIT(PORTD_R,u8pin);
            }
         break;
      }
   }
   //return success status
   return SUCCESS;
}


/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t* pu8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to read a digital value from the selected DIO u8pin
************************************************************************************/
enuErrorStatus_t DIO_Read(enuDIOPinNo_t PinId, uint8_t* pu8Data)
{
   uint8_t u8port,u8pin;
   //calculate the port and pin number of the selected pin
   u8port=PinId / DIO_PINS_NO;
   u8pin =PinId % DIO_PINS_NO;
   //if port number is invalid or the pin is set as output or the result holder's address is NULL
   if(u8port >= DIO_PORT_NO || DIOConfigParameters[PinId] == OUTPUT  || pu8Data == NULLPTR)
   {
      //return error status
      return ERROR;
   }
   else
   {
      //select the calculated port 
      switch(u8port)
      {
         case M_PORTA:
            //get the state of the pin in the selected port and store it in the provided value holder
            *pu8Data=GET_BIT(PINA_R,u8pin);
         break;
           
         case M_PORTB:
            //get the state of the pin in the selected port and store it in the provided value holder
            *pu8Data=GET_BIT(PINB_R,u8pin);
         break;

         case M_PORTC:
            //get the state of the pin in the selected port and store it in the provided value holder
            *pu8Data=GET_BIT(PINC_R,u8pin);
         break;

         case M_PORTD:
            //get the state of the pin in the selected port and store it in the provided value holder
            *pu8Data=GET_BIT(PIND_R,u8pin);
         break;
      }
   }
   //return success state
   return SUCCESS;
}

/************************************************************************************
* Parameters (in): enuDIOPinNo_t PinId, uint8_t* pu8Data
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to toggle the digital value of the selected DIO pin
************************************************************************************/
enuErrorStatus_t DIO_Toggle(enuDIOPinNo_t PinId)
{
   uint8_t u8port,u8pin;
   //calculate the port and pin number of the selected object
   u8port=PinId / DIO_PINS_NO;
   u8pin =PinId % DIO_PINS_NO;
   
   //if port number is invalid or the pin is set as input
   if(u8port >= DIO_PORT_NO || DIOConfigParameters[PinId] != OUTPUT)
   {
      //return error status
      return ERROR;
   }
   else
   {
      //select the calculated port 
      switch(u8port)
      {
         case M_PORTA:
            //toggle the current value of the pin in the PORTx Register
            TOG_BIT(PORTA_R,u8pin);
         break;

         case M_PORTB:
            //toggle the current value of the pin in the PORTx Register
            TOG_BIT(PORTB_R,u8pin);
         break;

         case M_PORTC:
            //toggle the current value of the pin in the PORTx Register
            TOG_BIT(PORTC_R,u8pin);
         break;

         case M_PORTD:
            //toggle the current value of the pin in the PORTx Register
            TOG_BIT(PORTD_R,u8pin);
         break;
      }
   }
   //return success status
   return SUCCESS;
}

/**************************************************************************************************************/

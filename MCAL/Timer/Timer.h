/*****************************************************************************
* Task: TIMER_DRIVER
* File Name: Timer.h
* Description: File containing function prototypes for Timer.c
* Author: Amr Mohamed
* Date: 10/7/2021
******************************************************************************/

#ifndef __TIMER__
#define __TIMER__

#include "DataTypes.h"
#include "Utils.h"
#include "Register.h"

typedef enum{
	TIMER0_STOP,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}enuTimer0Scaler_t;

typedef enum
{
	TIMER0_NORMAL_MODE,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}enuTimer0Mode_t;


typedef enum
{
	OC0_DISCONNECTED,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}enuOC0Mode_t;

//Initialization functions

/************************************************************************************
* Parameters (in): enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize timer 0 according to the sent parameters
************************************************************************************/
enuErrorStatus_t T0_Init(enuTimer0Mode_t enuMode,enuTimer0Scaler_t scaler);

/************************************************************************************
* Parameters (in): enuOC0Mode_t enuMode
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize the OCR0 pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t T0_OC0Mode(enuOC0Mode_t enuMode);
 
//Interrupt functions
/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptEnable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptDisable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptEnable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptDisable(void);

//Timer Ctrl Functions
/************************************************************************************
* Parameters (in): uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to start the timer and set a callback funtion to be called when time runs up
************************************************************************************/
enuErrorStatus_t T0_Start(uint64_t u64TimerValue, void(*pfCallback)(void));

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to stop the timer if running
************************************************************************************/
enuErrorStatus_t T0_Stop(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=time's up or 0=timer is still running
* Description: A function to check if a previously set up timer is still running or not
************************************************************************************/
enuErrorStatus_t T0_GetStatus(void);



/******************************************************************************************/

/********************************** Timer 1 Functions *************************************/

typedef enum{
   TIMER1_STOP=0,
   TIMER1_SCALER_1,
   TIMER1_SCALER_8,
   TIMER1_SCALER_64,
   TIMER1_SCALER_256,
   TIMER1_SCALER_1024,
   EXTERNAL0_FALLING,
   EXTERNAL0_RISING
}enuTimer1Scaler_t;

typedef enum
{
   TIMER1_NORMAL_MODE=0,
   TIMER1_CTC_ICR_TOP_MODE,
   TIMER1_CTC_OCRA_TOP_MODE,
   TIMER1_FASTPWM_ICR_TOP_MODE,
   TIMER1_FASTPWM_OCRA_TOP_MODE,
   TIMER1_PWM_PHASE_FREQ_ICR_TOP_MODE

}enuTimer1Mode_t;

typedef enum
{
   OCRA_DISCONNECTED=0,
   OCRA_TOGGLE,
   OCRA_NON_INVERTING,
   OCRA_INVERTING

}enuOC1A_Mode_t;

typedef enum
{
   OCRB_DISCONNECTED=0,
   OCRB_TOGGLE,
   OCRB_NON_INVERTING,
   OCRB_INVERTING
   
}enuOC1B_Mode_t;


/************************************************************************************
* Parameters (in): enuTimer1Mode_t enuMode,enuTimer1Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize timer 1 according to the sent parameters
************************************************************************************/
enuErrorStatus_t Timer1_Init( enuTimer1Mode_t enuMode,enuTimer1Scaler_t enuScaler);

/************************************************************************************
* Parameters (in): enuOC1A_Mode_t enu_oc1a_mode
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize the OCR1A pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t Timer1_OCRA1Mode(enuOC1A_Mode_t enu_oc1a_mode);

/************************************************************************************
* Parameters (in): enuOC1B_Mode_t enu_oc1b_mode
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize the OCR1B pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t Timer1_OCRB1Mode(enuOC1B_Mode_t enu_oc1b_mode);


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable over flow interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OVF_InterruptEnable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable over flow interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OVF_InterruptDisable(void);


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable output compare A interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCA_InterruptEnable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable output compare A interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCA_InterruptDisable(void);


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable output compare B interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCB_InterruptEnable(void);

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable output compare B interrupt for timer 1
************************************************************************************/
enuErrorStatus_t Timer1_OCB_InterruptDisable(void);



#endif /* __TIMER__ */
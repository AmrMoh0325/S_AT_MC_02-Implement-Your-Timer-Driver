
/*****************************************************************************
* Task: TIMER_DRIVER
* File Name: Timer.c
* Description: File containing timer driver functions
* Author: Amr Mohamed
* Date: 10/7/2021
******************************************************************************/



#include "Timer.h"

#define T0_TICKS     256
#define USEC_TO_SEC  1000000

void (*G_fptr)(void)=NULLPTR;
uint64_t Gu32MaxOVCount=0;
uint64_t Gu32CurrentOVCount=0;
uint8_t  Gu32LastOVTicks=0;
uint16_t G_u16Prescaler=0;

/************************************************************************************
* Parameters (in): enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize timer 0 according to the sent parameters
************************************************************************************/
enuErrorStatus_t T0_Init(enuTimer0Mode_t enuMode,enuTimer0Scaler_t enuScaler)
{
   //set the timer mode by setting the correct configuration of the WGM bits for the mode the user has selected 
   switch (enuMode)
   {
      case TIMER0_NORMAL_MODE:
      CLR_BIT(TCCR0_R,WGM00_B);
      CLR_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_PHASECORRECT_MODE:
      SET_BIT(TCCR0_R,WGM00_B);
      CLR_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_CTC_MODE:
      CLR_BIT(TCCR0_R,WGM00_B);
      SET_BIT(TCCR0_R,WGM01_B);
      break;
      case TIMER0_FASTPWM_MODE:
      SET_BIT(TCCR0_R,WGM00_B);
      SET_BIT(TCCR0_R,WGM01_B);
      break;
      default:
      return ERROR;
      break;
   }
   
   //clear the CS bits in the Timer control register and set the prescaler value
   TCCR0_R &= 0xF8;
   TCCR0_R |= enuScaler;
   
   //set the prescaler value in a global variable for other functions to use
   switch(enuScaler)
   {
      case TIMER0_STOP:          G_u16Prescaler=0;       break;
      case TIMER0_SCALER_1:      G_u16Prescaler=1;       break;
      case TIMER0_SCALER_8:      G_u16Prescaler=8;       break;
      case TIMER0_SCALER_64:     G_u16Prescaler=64;      break;
      case TIMER0_SCALER_256:    G_u16Prescaler=256;     break;
      case TIMER0_SCALER_1024:   G_u16Prescaler=1024;    break;
      default:                                           break;
   }
   //return SUCCESS state
   return SUCCESS;
}


/************************************************************************************
* Parameters (in): enuOC0Mode_t enuMode
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to initialize the OCR0 pin for use in PWM generation
************************************************************************************/
enuErrorStatus_t T0_OC0Mode(enuOC0Mode_t enuMode)
{
   //set the OC0 pin mode by setting the correct configuration of the COM bits for the mode the user has selected 
   switch (enuMode)
   {
      case OC0_DISCONNECTED:
      CLR_BIT(TCCR0_R,COM00_B);
      CLR_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_TOGGLE:
      SET_BIT(TCCR0_R,COM00_B);
      CLR_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_NON_INVERTING:
      CLR_BIT(TCCR0_R,COM00_B);
      SET_BIT(TCCR0_R,COM01_B);
      break;
      case OC0_INVERTING:
      SET_BIT(TCCR0_R,COM00_B);
      SET_BIT(TCCR0_R,COM01_B);
      break;
      
      default:
      return ERROR;
      break;
   }
   //return SUCCESS state
   return SUCCESS;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptEnable(void)
{
   //set the TOIE bit to enable the overflow interrupt
   SET_BIT(TIMSK_R,TOIE0_B);
   return SUCCESS;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable overflow interrupt
************************************************************************************/
enuErrorStatus_t T0_OV_InterruptDisable(void)
{
   //clear the TOIE bit to enable the overflow interrupt
   CLR_BIT(TIMSK_R,TOIE0_B);
   return SUCCESS;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to enable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptEnable(void)
{
   //set the TOIE bit to enable output compare interrupt
   SET_BIT(TIMSK_R,OCIE0_B);
   return SUCCESS;
}

/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to disable output compare interrupt
************************************************************************************/
enuErrorStatus_t T0_OC_InterruptDisable(void)
{
   //clear the TOIE bit to enable output compare interrupt
   CLR_BIT(TIMSK_R,OCIE0_B);
   return SUCCESS;
}



//Timer Ctrl Functions
/************************************************************************************
* Parameters (in): uint64_t u64TimerValue, void(*pfCallback)(void)
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to start the timer and set a callback funtion to be called when time runs up
************************************************************************************/
enuErrorStatus_t T0_Start(uint64_t u64TimerValue, void(*pfCallback)(void))
{
   enuTimer0Scaler_t enuScaler=TIMER0_STOP;
   
   //check if the timer interrups are enabled
   if (GET_BIT(TIMSK_R,TOIE0_B) || GET_BIT(TIMSK_R,OCIE0_B))
   {
      //check if the user has not sent a pointer to function to execute 
      if (pfCallback == NULLPTR)
      {
         //return error
         return ERROR;
      }
      else
      {
         //else store this pointer to function in the global pointer to function for the ISR to be able to execute
         G_fptr=pfCallback;
      }
   }
   
    //if the user sent a 0 time delay
    if (u64TimerValue==0)
    {
       //return an error
       return ERROR;
    }
    //else select the appropriate timer prescaler depending on the time sent for the least number of overflows
    else if (u64TimerValue<=256)
    {
       enuScaler=TIMER0_SCALER_8;
    }                                   
    else if (u64TimerValue>256 && u64TimerValue<=2048)
    {
       enuScaler=TIMER0_SCALER_64;
    }        
    else if (u64TimerValue>2048 && u64TimerValue<=8192)       
    {
       enuScaler=TIMER0_SCALER_256;   
    }
    else                                                      
    {
       enuScaler=TIMER0_SCALER_1024;
    }
    
   //initialize the timer in normal mode with the new prescaler 
   T0_Init(TIMER0_NORMAL_MODE,enuScaler);
   
   //Enable Timer overflow interrupt
   T0_OV_InterruptEnable();
    
   //calculate tick time of the selected prescaler
   uint32_t u32TimerFreq=F_CPU/G_u16Prescaler;
   
   //calculate the number of overflows required to reach the selected time
   Gu32MaxOVCount=((u64TimerValue*u32TimerFreq)/(T0_TICKS*USEC_TO_SEC));
   
   //calculate the time required to setup  the last overflow iteration
   Gu32LastOVTicks=((u64TimerValue*u32TimerFreq)/USEC_TO_SEC)-(Gu32MaxOVCount*T0_TICKS);
   
   //clear the overflow flag by writing 1 on it
   SET_BIT(TIFR_R,TOV0_B);
   
   //if the time can be achieved without overflows
   if (Gu32MaxOVCount==0)
   {
      //set the timer value to overflow on the exact timing
      TCNT0_R= (T0_TICKS-Gu32LastOVTicks);
   }
   else
   {
      //else, set the overflow to 0
      TCNT0_R=0;
   }
   
   //return success state
   return SUCCESS;
}



/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=SUCCESS or 0=FAIL
* Description: A function to stop the timer if running
************************************************************************************/
enuErrorStatus_t T0_Stop(void)
{
   //turn off all timer interrupts
   T0_OV_InterruptDisable();
   T0_OC_InterruptDisable();
   //initialize the timer with no clock to stop it
   T0_Init(TIMER0_NORMAL_MODE,TIMER0_STOP);
   //clear the timer overflow flag
   SET_BIT(TIFR_R,TOV0_B);
   
   //reset all global variables
   Gu32MaxOVCount=0;
   Gu32LastOVTicks=0;
   Gu32CurrentOVCount=0;
   
   //return success state
   return SUCCESS;
}


/************************************************************************************
* Parameters (in): void
* Parameters (out): enuErrorStatus_t
* Return value: 1=time's up or 0=timer is still running
* Description: A function to check if a previously set up timer is still running or not
************************************************************************************/
enuErrorStatus_t T0_GetStatus(void)
{
      //if the current overflow value is less than the total overflows value
      if (Gu32CurrentOVCount < Gu32MaxOVCount)
      {
         //check the over flow flag
         if (GET_BIT(TIFR_R,TOV0_B))
         {
            //if set, clear it
            SET_BIT(TIFR_R,TOV0_B);
            //and increase the overflow counter
            Gu32CurrentOVCount++;
         }
      }
      //if the current overflow value equals the calculated total overflows value
      else if (Gu32CurrentOVCount == Gu32MaxOVCount)
      {
         //set the timer value to the remaining timing
         TCNT0_R=((T0_TICKS-1)-Gu32LastOVTicks);
         //clear the overflow flag
         SET_BIT(TIFR_R,TOV0_B);
         //increase the overflow counter
         Gu32CurrentOVCount++;
      }
      
      //if the time is up
      else
      {
         //check if the global pointer to function holds a valid function address
         if (G_fptr != NULLPTR)
         {
            //if so, call the function
            G_fptr();
         }
         //stop the timer
         T0_Stop();
         //return a SUCCESS state
         return SUCCESS;
         
      }
      // if all failed, return an error state
   return ERROR;
}





/******************** ISR FUNCTIONS ****************************************/

//ISR function to run in case  of a timer overflow interrupt
ISR(TIMER0_OVF_vect)
{
   //if the current overflow value is less than the total overflows value
   if (Gu32CurrentOVCount < Gu32MaxOVCount)
   {
      //increase the overflow counter
      Gu32CurrentOVCount++;
   }
   //if the current overflow value equals the calculated total overflows value
   else if (Gu32CurrentOVCount == Gu32MaxOVCount)
   {
      //set the timer value to the remaining timing
      TCNT0_R=((T0_TICKS-1)-Gu32LastOVTicks);
      //increase the overflow counter
      Gu32CurrentOVCount++;
   }
   //if the time is up
   else
   {
      //reset the overflow counter
      Gu32CurrentOVCount=0;
      //check if the global pointer to function holds a valid function address
      if (G_fptr != NULLPTR)
      {
         //call the function
         G_fptr();
      }
   }      
}
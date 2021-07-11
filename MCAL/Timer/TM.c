/*
 * TM.c
 *
 * Created: 7/10/2021 4:58:48 AM
 *  Author: Amrth
 */ 

#include "TM.h"

/* A function to initialize all the TM groups according to the configuration */

 void (*G_fptr)(void);

enuErrorStatus_t Timer_Init(void)
{
   for (int u8i=0;u8i<TM_GROUPS_NO;u8i++)
   {
      switch(astrTimerConfigParameters[u8i].enuTimerModule)
      {
         case TIMER0:
            
            switch(astrTimerConfigParameters[u8i].enuTimerMode)
            {
               case NORMAL:
                  CLR_BIT(TCCR0,WGM00);
                  CLR_BIT(TCCR0,WGM01);
                  break;
                 
               case CTC:
                  CLR_BIT(TCCR0,WGM00);
                  SET_BIT(TCCR0,WGM01);
                  break;
                  
               case FAST_PWM:
                  SET_BIT(TCCR0,WGM00);
                  SET_BIT(TCCR0,WGM01);
                  break;
                  
               case PC_PWM:
                  SET_BIT(TCCR0,WGM00);
                  CLR_BIT(TCCR0,WGM01);
                  break;
            }
            TCCR0&=0XF8;//0b11111000
            TCCR0|=astrTimerConfigParameters[u8i].enuTimerClock;
            
            if (astrTimerConfigParameters[u8i].enuTimerIntEn)
            {
               SET_BIT(TIMSK_R,TOIE0_B);
            }
            
            break;
            
            
         case TIMER1:
            
            break;
         case TIMER2:
            
            break;
      }
   }
}


/* A function to initiate a timer delay on the selected TM group */
enuErrorStatus_t Timer_Start(uint8_t u8GroupId, uint32_t u32TimerValueUS, void(*pfCallback)(void))
{
   uint8_t u8Prescaler=astrTimerConfigParameters[u8GroupId].enuTimerClock;
   switch(astrTimerConfigParameters[u8GroupId].enuTimerModule)
   {
      case TIMER0:
      TCCR0&=0XF8;//0b11111000
      TCCR0|=u8Prescaler;
      
      
      
      break;
      
      
      case TIMER1:
      
      break;
      case TIMER2:
      
      break;
   }
}


/* A function to stop a timer */
enuErrorStatus_t Timer_Stop(uint8_t u8GroupId);
/* A function to check periodically for the timer flag */
enuErrorStatus_t Timer_GetStatus(uint8_t u8GroupId);

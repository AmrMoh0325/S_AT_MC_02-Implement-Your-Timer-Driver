

#ifndef __DATA_TYPES__
#define __DATA_TYPES__

/********************** General Data Types **************************/
typedef unsigned char           uint8_t;
typedef signed char             sint8_t;
typedef unsigned int            uint16_t;
typedef signed int              sint16_t;
typedef unsigned long int       uint32_t;
typedef signed long int         sint32_t;
typedef unsigned long long int  uint64_t;
typedef signed long long int    sint64_t;


#define NULLPTR                 ((void *) 0) 



typedef enum{
   ERROR,
   SUCCESS
}enuErrorStatus_t;


#endif // __DATA_TYPES__

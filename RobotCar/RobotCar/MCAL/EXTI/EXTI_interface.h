/*
 * EXTI_interface.h
 *
 * Created: 9/26/2024 5:09:46 PM
 *  Author: AMIT
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_



/* interrupt pins */

#define  INT_0     0
#define  INT_1     1
#define  INT_2     2

/* sense control */

#define  LOW_LEVEL             0 
#define  ANY_LOGICAL_CHANGE    1 
#define  FALLING_EDGE          2 
#define  RISING_EDGE           3 



void EXTI_voidInit(u8 copy_u8interrupt , u8 copy_u8sense) ; 
void EXTI_voidSetCallBack(u8 copy_u8interrupt,void(*ptr)(void)) ; 
void EXTI0_voidEnable(void) ; 
void EXTI0_voidDisable(void) ;


void EXTI1_voidEnable(void) ;
void EXTI1_voidDisable(void) ;


void EXTI2_voidEnable(void) ;
void EXTI2_voidDisable(void) ;



#endif /* EXTI_INTERFACE_H_ */
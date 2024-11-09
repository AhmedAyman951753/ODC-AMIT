/*
 * EXTI_prg.c
 *
 * Created: 9/26/2024 5:10:21 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "EXTI_reg.h" 
#include "EXTI_interface.h"


void(*EXTI_PTR[3])(void) ={null} ; 

void EXTI_voidInit(u8 copy_u8interrupt , u8 copy_u8sense){
	
	   
	   switch(copy_u8interrupt){
		   
		   
		   case INT_1 : 
		                if (copy_u8sense==LOW_LEVEL)
		                {
							CLR_BIT(MCUCR_REG,3) ; 
							CLR_BIT(MCUCR_REG,2) ; 
		                }
						else if (copy_u8sense==ANY_LOGICAL_CHANGE)
						{
							CLR_BIT(MCUCR_REG,3) ;
							SET_BIT(MCUCR_REG,2) ;
						}
						else if (copy_u8sense==FALLING_EDGE)
						{
							SET_BIT(MCUCR_REG,3) ;
							CLR_BIT(MCUCR_REG,2) ;
						}
						else if (copy_u8sense==RISING_EDGE)
						{
							SET_BIT(MCUCR_REG,3) ;
							SET_BIT(MCUCR_REG,2) ;
						}
		                  break;
						  
		case INT_0 :
	                  	if (copy_u8sense==LOW_LEVEL)
	                  	{
	                  		CLR_BIT(MCUCR_REG,1) ;
	                  		CLR_BIT(MCUCR_REG,0) ;
	                  	}
	                  	else if (copy_u8sense==ANY_LOGICAL_CHANGE)
	                  	{
	                  		CLR_BIT(MCUCR_REG,1) ;
	                  		SET_BIT(MCUCR_REG,0) ;
	                  	}
	                  	else if (copy_u8sense==FALLING_EDGE)
	                  	{
	                  		SET_BIT(MCUCR_REG,1) ;
	                  		CLR_BIT(MCUCR_REG,0) ;
	                  	}
	                  	else if (copy_u8sense==RISING_EDGE)
	                  	{
	                  		SET_BIT(MCUCR_REG,1) ;
	                  		SET_BIT(MCUCR_REG,0) ;
	                  	}
	                  	break;
						  
		   case INT_2 : 
		               if (copy_u8sense==FALLING_EDGE)
		               {
						   CLR_BIT(MCUCSR_REG,6) ; 
		               }
					   else if (copy_u8sense==RISING_EDGE)
					   {
						   SET_BIT(MCUCSR_REG,6) ; 
					   }
		   
	   }
	
	
	
	
	
	
}

void EXTI0_voidEnable(void) {
	
	SET_BIT(GICR_REG,6) ; 
	
}
void EXTI0_voidDisable(void){
	
	CLR_BIT(GICR_REG,6) ; 
	
	
}



void EXTI1_voidEnable(void) {
	
	SET_BIT(GICR_REG,7) ; 
}
void EXTI1_voidDisable(void){
	CLR_BIT(GICR_REG,7) ; 
}


void EXTI2_voidEnable(void){
	SET_BIT(GICR_REG,5) ; 
	
}
void EXTI2_voidDisable(void){
	CLR_BIT(GICR_REG,5) ; 
}


void EXTI_voidSetCallBack(u8 copy_u8interrupt,void(*ptr)(void)){
	
	
	 switch(copy_u8interrupt){
		 
		 case INT_0:  EXTI_PTR[0]=ptr ; break;
		 case INT_1:  EXTI_PTR[1]=ptr ; break;
		 case INT_2:  EXTI_PTR[2]=ptr ; break;
		 
		 
		 
		 
	 }
	
	
	
}


/*int0*/
void __vector_1(void)__attribute__((signal)) ;
void __vector_1(void){
	
	 EXTI_PTR[0]() ; 
	
	
}

/*int1*/
void __vector_2(void)__attribute__((signal)) ;
void __vector_2(void){
	
	
EXTI_PTR[1]() ; 
	
	
}
/*int2 */
void __vector_3(void)__attribute__((signal)) ;
void __vector_3(void){
	
	
	EXTI_PTR[2]() ; 
	
	
}

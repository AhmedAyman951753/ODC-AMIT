/*
 * Kernel_interface.c
 *
 * Created: 10/2/2024 2:38:42 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/TIMER0/TIMER0_interface.h"
#include "Kerneinterface.h"


Task_type TASK_ARR[TASK_NUM]={{0}};
	
	



void Kernel_voidCreateTask(void(*ptr)(void), u16 periodicity, u8 priority) {
	
	      if (TASK_ARR[priority].ptr_fun ==0)
	      {
			   TASK_ARR[priority].ptr_fun=ptr ;
			   TASK_ARR[priority].periodicity=periodicity ;
			   TASK_ARR[priority].Task_state=RESUME ; 
			   
	      }
	   
	
}

void Kernel_voidSchdulerALO(void){
	
	   static u16 count=0 ; 
	   count++ ; 
	   u8 task_in= 0 ; 
	   
	   for (task_in=0 ; task_in<TASK_NUM;task_in++)
	   {
		      if (TASK_ARR[task_in].ptr_fun!=0 )
		      {
				   if ((count%TASK_ARR[task_in].periodicity ) ==0)
				   {
					   if (TASK_ARR[task_in].Task_state==RESUME)
					   {
						   // CAL
						   
						   TASK_ARR[task_in].ptr_fun() ;
					   }
					   
					   
				   }
				   
		      }
			 
		      
		   
		   
		   
	   }
	
	
	
	
}



void Kernel_voidStart(void){
	
	 TIMER0_voidInit(CTC_MODE) ; 
	 TIMER0_voidSetCallBack(Kernel_voidSchdulerALO,CTC_MODE) ; 
	
	
}


void Kernel_voidDeletTask(u8 priority){
	
	TASK_ARR[priority].ptr_fun=0 ; 
	
}



void Kernel_voidSuspendTask(u8 priority){
	
	TASK_ARR[priority].Task_state=SUSPEND ; 
	
}
void Kernel_voidResumeTask(u8 priority) {
	TASK_ARR[priority].Task_state=RESUME ; 
}
/*
 * Kerneinterface.h
 *
 * Created: 10/2/2024 2:39:09 PM
 *  Author: AMIT
 */ 


#ifndef KERNEINTERFACE_H_
#define KERNEINTERFACE_H_



#define   SUSPEND   0 
#define   RESUME     1 


#define  TASK_NUM    3 


typedef struct {
	
	   void(*ptr_fun)(void) ; 
	   
	   u16 periodicity ; 
	  
	     u8 Task_state ; 
	
	}Task_type;







void Kernel_voidCreateTask(void(*ptr)(void), u16 periodicity, u8 priority) ; 

void Kernel_voidStart(void) ; 


void Kernel_voidDeletTask(u8 priority) ; 


void Kernel_voidSuspendTask(u8 priority) ; 
void Kernel_voidResumeTask(u8 priority) ;



#endif /* KERNEINTERFACE_H_ */
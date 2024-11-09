/*
 * DCMOTOR_prog.c
 *
 * Created: 10/2/2024 9:50:58 AM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h" 
#include "../../MCAL/DIO/DIO_interface.h"
#include "DCMOTOR_config.h"


void DCMOTOR_voidF(void){
	
	/*make pins as output */
	DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ; 
	DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;
	
	/*Drive motor cw */
	
	DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,HIGH) ; 
	DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,HIGH) ;
	DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,HIGH) ; 
	DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,LOW) ; 
	DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,HIGH) ; 
	DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,LOW) ; 
	
	
	
	
	
	
	
	
	
}
void DCMOTOR_voidV(void){
	
	/*make pins as output */
	DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;
	
	/*Drive motor acw */
	
	DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,HIGH) ;
	DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,HIGH) ;
	DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,LOW) ;
	DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,HIGH) ;
	DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,LOW) ;
	DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,HIGH) ;
	
	
}

void DCMOTOR_voidS(void){
	
	
	/*make pins as output */
	DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;
	
	/*Drive motor stop */
	
	DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,LOW) ;
	DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,LOW) ;
	  DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,LOW) ;
	  DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,LOW) ;
	  DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,LOW) ;
	  DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,LOW) ;
}


void DCMOTOR_voidR(void)
{
	/*make pins as output */
	DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;
	
	/*Drive motor right */
	
	DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,HIGH) ;
	DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,LOW) ;
	DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,HIGH) ;
	DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,LOW) ;
	DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,LOW) ;
	DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,LOW) ;
}


void DCMOTOR_voidL(void)
{
	/*make pins as output */
	DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
	DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;
	
	/*Drive motor left */
	
	DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,LOW) ;
	DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,HIGH) ;
	DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,LOW) ;
	DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,LOW) ;
	DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,LOW) ;
	DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,HIGH) ;
}


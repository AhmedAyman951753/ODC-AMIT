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


void DCMOTOR_voidCW(u8 Motor)
{
	if (Motor == MOTOR1)
	{
		/*make pins as output */
		DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
		
		/*Drive motor cw */
		DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,LOW) ;
	}
	
	else if (Motor == MOTOR2)
	{
		/*make pins as output */
		DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;

		/*Drive motor cw */
		DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,LOW) ;
	}
	
}

void DCMOTOR_voidACW(u8 Motor)
{
	if (Motor == MOTOR1)
	{
		/*make pins as output */
		DIO_voidSetPinDir(H_ENA_PORT,H_ENA_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A1_PORT,H_A1_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A2_PORT,H_A2_PIN,OUTPUT) ;
		
		/*Drive motor cw */
		DIO_voidSetPinVal(H_ENA_PORT,H_ENA_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A1_PORT,H_A1_PIN,LOW) ;
		DIO_voidSetPinVal(H_A2_PORT,H_A2_PIN,HIGH) ;
	}
	
	else if (Motor == MOTOR2)
	{
		/*make pins as output */
		DIO_voidSetPinDir(H_ENB_PORT,H_ENB_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A3_PORT,H_A3_PIN,OUTPUT) ;
		DIO_voidSetPinDir(H_A4_PORT,H_A4_PIN,OUTPUT) ;

		/*Drive motor cw */
		DIO_voidSetPinVal(H_ENB_PORT,H_ENB_PIN,HIGH) ;
		DIO_voidSetPinVal(H_A3_PORT,H_A3_PIN,LOW) ;
		DIO_voidSetPinVal(H_A4_PORT,H_A4_PIN,HIGH) ;
	}
}

void DCMOTOR_voidStop(u8 Motor){
	
	
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


void DCMOTOR_voidF(void){
	
	DCMOTOR_voidACW(MOTOR1);
	DCMOTOR_voidCW(MOTOR2);
}


void DCMOTOR_voidV(void){
	
	DCMOTOR_voidCW(MOTOR1);
	DCMOTOR_voidACW(MOTOR2);
}


void DCMOTOR_voidR(void)
{
	DCMOTOR_voidStop(MOTOR2);
	DCMOTOR_voidCW(MOTOR1);
}


void DCMOTOR_voidL(void)
{
	DCMOTOR_voidStop(MOTOR1);
	DCMOTOR_voidACW(MOTOR2);
}


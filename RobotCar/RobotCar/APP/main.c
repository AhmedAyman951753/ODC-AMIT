/*
 * Test2.c
 *
 * Created: 10/2/2024 9:44:37 AM
 * Author : USER
 */ 

/***** Includes Section Start *****/
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/DIO/DIO_Reg.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/TIMER0/TIMER0_reg.h"
#include "../MCAL/GI/GI_interface.h"
#include "../MCAL/GI/GI_reg.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/EXTI/EXTI_reg.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/ADC/ADC_reg.h"
#include "../HAL/DCMOTOR/DCMOTOR_config.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/UART/UART_reg.h"
#include "../MCAL/RTOS/Kerneinterface.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/***** Includes Section End *****/


int main(void)
{
	u8 str[100] = "Enter (1) for bluetooth mode or (2) for line follower mode : ";
	u8 character = 0;
	u8 flag = 0;
	u8 Right_IR = 0 , Left_IR = 0;
	UART_voidInit();
	for (u8 counter = 0 ; str[counter] != '\0' ; counter++)
	{
		UART_voidTX(str[counter]);
	}
	flag = UART_u8RX();
    while (1) 
    {	
		if ('1' == flag)
		{
			character = UART_u8RX();
			switch(character)
			{
				case 'F' :      DCMOTOR_voidF();				break;
				case 'V' :      DCMOTOR_voidV();				break;
				case 'S' :
						 {
							DCMOTOR_voidStop(MOTOR1);
							DCMOTOR_voidStop(MOTOR2);
							break;
						 }
				case 'R' :      DCMOTOR_voidR();				break;
				case 'L' :      DCMOTOR_voidL();				break;
			}	
		}
		
		else if ('2' == flag)
		{
			Right_IR = DIO_u8ReadpinVal(DIO_PORTA , DIO_PIN1);
			Left_IR =  DIO_u8ReadpinVal(DIO_PORTA , DIO_PIN0);
			if ((Left_IR == 1) && (Right_IR == 1))
			{
				DCMOTOR_voidF();
			}
			else if ((Left_IR == 1) && (Right_IR == 0))
			{
				DCMOTOR_voidR();
			}
			else if ((Left_IR == 0) && (Right_IR == 1))
			{
				DCMOTOR_voidL();
			}
			else if ((Left_IR == 0) && (Right_IR == 0))
			{
				DCMOTOR_voidV();
			}
		}	
    }	
}
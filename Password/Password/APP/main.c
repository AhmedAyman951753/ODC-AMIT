/*
 * Password.c
 *
 * Created: 9/28/2024 11:49:34 PM
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
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/ADC/ADC_reg.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/***** Includes Section End *****/

int main(void)
{
	
	u8 op1 , op2 , op3 , op4;											// operators of password
	u8 counter1 = 0 , counter2 = 0;										// counter1 for loops and counter2 for the wrong password
	u8 flag = 0 , key = 0 , No_Of_Digits = 0;												// flag to check the password and active ADC for temperature
	u16 val = 0;														// To read value of pin of ADC
	f32 temp = 0;														// Temperature of LM35
	u32 password = 0;													// password from the user
	u8 dc = 0;															// Duty Cycle
	
	DIO_voidSetPortDir(DIO_PORTA , 0xf0);								// set direction of PORTA as output
	DIO_voidSetPortDir(DIO_PORTB , 0xff);								// set direction of PORTC as output
	LCD_voidInit();														// activate LCD
	KEYPAD_voidInit();													// activate KEYPAD
	ADC_voidInit();														// activate ADC
	while(1)
	{
		while (counter2 < 3)											// Three chances for the user to enter the correct password
		{
			LCD_voidSendString("Enter password : ");					// Asking the user to enter the password
			
			key = ReturnKey_void();										// Reading keypad if any button is pressed
			
			/* This loop below is implemented for security as if who enters the password isn't the user so he don't know the
			real numbers of password so every number he will press in keypad , it will be printed on lcd as number of numbers of password */
			
			while (key != '=')											// Loop to get the password in its operators
			{
				
				LCD_voidGotoxy(counter1,1);								// location of each number in keypad in serial
				LCD_voidSendNumber(key);								// printing the number which is pressed in the keypad
				_delay_ms(200);											// delay to print * instead of the number for security
				LCD_voidGotoxy(counter1,1);								// same location of the number
				LCD_voidSendData('*');									// printing * in lcd
				switch (counter1)										// check counter1 to put the password in its operators
				{
					case 0 :      op1 = key;			break;			// 1st number of password
					case 1 :      op2 = key;			break;			// 2nd number of password
					case 2 :      op3 = key;			break;			// 3rd number of password
					case 3 :      op4 = key;			break;			// 4th number of password
				}
				counter1++;												// increasing the counter to continue the loop
				key = ReturnKey_void();									// reading another value from keypad
				
			}
			
			password = op1 * 1000 + op2 * 100 + op3 * 10 + op4;			// create digits of password
			No_Of_Digits = counter1;									// keep the last value of counter in key for the condition of the password
			
			
			if (key = '=')												// condition if the user ends from entering the password
			{
				
				LCD_voidSendCommand(1);									// clear lcd
				LCD_voidSendString("Please wait");						// waiting to check the password (It's your choice to make it or not)
				
				/* loop to print (.) in serial for waiting */
				for (counter1 = 0 ; counter1 < 10 ; counter1++)			
				{
					LCD_voidGotoxy(counter1,1);
					LCD_voidSendData('.');
					_delay_ms(100);
				}
			}
			counter1 = 0;												// reset the counter to place the password in lcd in location 0					

			LCD_voidSendCommand(1);										// clear lcd
			if ((password == 1234) && (No_Of_Digits < 5))				// condition of checking the password
			{					
				LCD_voidSendString("Correct Password.");				// print correct password on lcd
				DIO_voidSetPinVal(DIO_PORTB , DIO_PIN7 , HIGH);			// emitting the green led
				_delay_ms(1000);										// delay
				LCD_voidSendCommand(1);									// clear lcd
				LCD_voidSendString("Welcome User");						// print welcome user on lcd
				_delay_ms(2000);										// delay
				LCD_voidSendCommand(1);									// clear lcd
				break;
			}
			else
			{
				flag = 1;												// set the flag as the user enters wrong password
				counter2++;												// increase counter of chances for entering password
				LCD_voidSendString("Wrong Password!!");					// print wrong password on lcd
				DIO_voidSetPinVal(DIO_PORTB , DIO_PIN6 , HIGH);			// turn on the red led
				_delay_ms(2000);										// delay
				LCD_voidSendCommand(1);									// clear lcd
				if (counter2 < 3)										// loop to check chances of entering the password
				{
					flag = 0;											// reset the flag to enter the password again if counter2 < 3
					DIO_voidSetPinVal(DIO_PORTB , DIO_PIN6 , LOW);		// turn off the red led
					LCD_voidSendString("Please Try again !!");			// message to enter password again
					_delay_ms(1000);									// delay
					LCD_voidSendCommand(1);								// clear lcd
				}
				
			}
		}
		
		if (counter2 == 3)												// if the user enters password wrong 3 times
		{
			flag = 1;													// set the flag
			LCD_voidSendString("Alarm is On !!");						// set the alarm
			DIO_voidSetPinVal(DIO_PORTB , DIO_PIN6 , HIGH);				// turn on the red led
			DIO_voidSetPinVal(DIO_PORTB , DIO_PIN4 , HIGH);
			break;														// break to get out of the loop to continue the alarm
		}
		
		
		if (flag == 0)													// if user enters correct password
		{
			while(1)
			{
				val = ADC_u16ReadChannel(ADC_0);						// reading LM35 temperature				
				temp = (f32)val * 500 / 1024;							// calculate temperature		
				LCD_voidGotoxy(0,0);									// go to location 0 , 0 in lcd
				LCD_voidSendString("Temperature = ");					// print the temperature
				LCD_voidSendNumber(temp);
				
				/* conditions of turning on the fan and controlling the speed */
				if (temp < 30)											// if temp < 30											
				{
					dc = 0;												// set the speed = 0
					TIMER0_voidFastPWM(dc);								// turn on the fan with the entered speed
					LCD_voidGotoxy(0,1);								// go to location 0 , 1 in lcd
					LCD_voidSendString("Fan Speed = 0%");				// print the speed of the fan on lcd
				}
				else if ((temp >= 30) && (temp < 40))					// if temp is between 30 and 40
				{
					dc = 30;											// set the speed by 30%
					TIMER0_voidFastPWM(dc);								// turn on the fan with the entered speed
					LCD_voidGotoxy(0,1);								// go to location 0 , 1 in lcd
					LCD_voidSendString("Fan Speed = 30%");				// print the speed of the fan on lcd
				}
				else if ((temp >= 40) && (temp < 50))					// if temp is between 40 and 50
				{
					dc = 50;											// set the speed by 50%
					TIMER0_voidFastPWM(dc);								// turn on the fan with the entered speed
					LCD_voidGotoxy(0,1);								// go to location 0 , 1 in lcd
					LCD_voidSendString("Fan Speed = 50%");				// print the speed of the fan on lcd
				}
				else if (temp >= 50)									// if temp is greater than 50
				{
					dc = 99;											// set the speed by 100%
					TIMER0_voidFastPWM(dc);								// turn on the fan with the entered speed
					LCD_voidGotoxy(0,1);								// go to location 0 , 1 in lcd
					LCD_voidSendString("Fan Speed = 100%");				// print the speed of the fan on lcd
				}
				
			}
			
		}
		
		
	}
	
}










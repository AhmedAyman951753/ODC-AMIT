/*
 * Test3.c
 *
 * Created: 10/3/2024 11:04:12 AM
 * Author : USER
 */ 

/***** Includes Section Start *****/
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/LCD/LCD_config.h"
#include "../HAL/KEYPAD/KEYPAD_config.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_config.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
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
#include "../MCAL/UART/UART_interface.h"
#include "../MCAL/UART/UART_reg.h"
#include "../MCAL/RTOS/Kerneinterface.h"
#include "../MCAL/FreeRtos/FreeRTOS.h"
#include "../MCAL/FreeRtos/FreeRTOSConfig.h"
#include "../MCAL/FreeRtos/task.h"
#include "../MCAL/FreeRtos/semphr.h"
#include "../MCAL/FreeRtos/queue.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/***** Includes Section End *****/



SemaphoreHandle_t semaphore;
QueueHandle_t queue1;
QueueHandle_t queue2;


void task1()
{
	u8 key;
	xSemaphoreTake(semaphore , 100);
	key = UART_u8RX();
	xQueueSend(queue1 , &key , 100);
	xSemaphoreGive(semaphore);
	vTaskDelay(1000);
}



void task2()
{
	u8 key;
	xSemaphoreTake(semaphore , 200);
	xQueueReceive(queue1 , &key , 100);
	switch (key)
	{
		case 'a' :
		LCD_voidSendString("Correct Password.");
		DIO_voidSetPinVal(DIO_PORTB , DIO_PIN7 , HIGH);
		_delay_ms(1000);
		xSemaphoreGive(semaphore);
		break;
		
		default  :
		LCD_voidGotoxy(0,0);
		LCD_voidSendString("Wrong Password!!");
		LCD_voidGotoxy(0,1);
		LCD_voidSendString("System is Closed !!");
		DIO_voidSetPinVal(DIO_PORTB , DIO_PIN6 , HIGH);
		_delay_ms(30000);
	}	
	vTaskDelay(2000);
}



void task3()
{
	u16 val = 0;
	f32 temp = 0;
	if (xSemaphoreTake(semaphore , 300) == 1)
	{
		while(1)
		{
			val = ADC_u16ReadChannel(ADC_0);						
			temp = (f32)val * 500 / 1024;				
			xQueueSend(queue2 , &temp , 200);
		}	
	}
	xSemaphoreGive(semaphore);
	vTaskDelay(3000);
}


void task4()
{
	f32 temp;
	u8 dc = 0;
	if (xSemaphoreTake(semaphore , 400) == 1)
	{
		while(1)
		{
			xQueueReceive(queue2 , &temp , 200);
			LCD_voidGotoxy(0,0);
			LCD_voidSendString("Temperature = ");
			LCD_voidSendNumber(temp);
			if (temp < 30)
			{
				dc = 0;
				TIMER0_voidFastPWM(dc);
				LCD_voidGotoxy(0,1);
				LCD_voidSendString("Fan Speed = 0%");
			}
			else if ((temp >= 30) && (temp < 40))
			{
				dc = 30;
				TIMER0_voidFastPWM(dc);
				LCD_voidGotoxy(0,1);
				LCD_voidSendString("Fan Speed = 30%");
			}
			else if ((temp >= 40) && (temp < 50))
			{
				dc = 50;
				TIMER0_voidFastPWM(dc);
				LCD_voidGotoxy(0,1);
				LCD_voidSendString("Fan Speed = 50%");
			}
			else if (temp >= 50)
			{
				dc = 99;
				TIMER0_voidFastPWM(dc);
				LCD_voidGotoxy(0,1);
				LCD_voidSendString("Fan Speed = 100%");
			}
		}
	}
	vTaskDelay(4000);
}

int main(void)
{
	DIO_voidSetPortDir(DIO_PORTA , 0xf0);
	DIO_voidSetPinDir(DIO_PORTD , DIO_PIN0 , INPUT);
	DIO_voidSetPinDir(DIO_PORTD , DIO_PIN1 , INPUT);
	DIO_voidSetPortDir(DIO_PORTB , 0xcf);
	LCD_voidInit();
	ADC_voidInit();
	UART_voidInit();
	xTaskCreate(task1 , "task1" , 80 , NULL , 4 , NULL);
	xTaskCreate(task2 , "task2" , 80 , NULL , 3 , NULL);
	xTaskCreate(task3 , "task3" , 80 , NULL , 2 , NULL);
	xTaskCreate(task4 , "task4" , 80 , NULL , 1 , NULL);
	semaphore = xSemaphoreCreateBinary();
	queue1 = xQueueCreate(1 , sizeof(u8));
	queue2 = xQueueCreate(1 , sizeof(f32));
	vTaskStartScheduler();
}


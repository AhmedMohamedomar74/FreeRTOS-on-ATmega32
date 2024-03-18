/*
 * RTOS_LAB1_ATMEGA32.c
 *
 * Created: 1/27/2014 12:22:11 AM
 *  Author: IMT
 */

#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../HAL/LED/LED.h"
#include "../HAL/LCD/LCD.h"

/* Define Tasks Priorities */
#define TASK2_PRIORITY (1)
#define TASK1_PRIORITY (2)

#define TASK1_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK2_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)

/*tasks codes prototypes */
void task1_code(void *pvParamter);
void task2_code(void *pvParamter);


int main(void)
{

	init_lcd();
	/*Creat tasks*/
	xTaskCreate(task1_code, NULL, TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(task2_code, NULL, TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}

/*Task1 Code */
void task1_code(void *pvParamter)
{
	for (;;)
	{
		LCD_clear();
		LCD_vidWriteString("I am Task 1");
		vTaskDelay(2000); // Running to waiting for time 2000 Tick
	}
}
/*Task2 Code */
void task2_code(void *pvParamter)
{
	for (;;)
	{
		LCD_clear();
		LCD_vidWriteString("I am Task 2");
		vTaskDelay(1000);
	}
}

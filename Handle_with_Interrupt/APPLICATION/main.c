#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../HAL/LCD/LCD.h"
#include "../RTOS/semphr.h"
#include "../MCAL/Interrupt/Interrupt_EXT.h"

/* Define Tasks Priorities */
#define TASK2_PRIORITY (2)
#define TASK1_PRIORITY (2)

#define TASK1_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK2_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)
#define TASK_ISR_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)

/*tasks codes prototypes */
void task1_code(void *pvParamter);
void task2_code(void *pvParamter);
void task_ISR(void *pvParamter);
void Task_Realse();
xSemaphoreHandle LCD_SEM;
xSemaphoreHandle task_sync_sem;
int main(void)
{

	vSemaphoreCreateBinary(LCD_SEM);
	task_sync_sem = xSemaphoreCreateCounting(1,0);
	init_lcd();
	Interrupt_EXT_t INT_OBJ = {
		.Call_back_fun = Task_Realse,
		.INT_CONTROL = falling_edge,
		.INT_NUM = EXT_INT_Number_INT0,
	};
	Test_Enable_init(&INT_OBJ);
	/*Creat tasks*/
	// xTaskCreate(task2_code, NULL, TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
	// xTaskCreate(task1_code, NULL, TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
	xTaskCreate(task_ISR, NULL, TASK_ISR_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);

	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}

/*Task1 Code */
void task1_code(void *pvParamter)
{
	for (;;)
	{
		if (xSemaphoreTake(LCD_SEM,portMAX_DELAY) == 1)
		{
			LCD_clear();
			LCD_vidWriteString("I am Task 1");
			vTaskDelay(2000); // Running to waiting for time 2000 Tick
			
		}
		xSemaphoreGive(LCD_SEM);
	}
}
/*Task2 Code */
void task2_code(void *pvParamter)
{
	for (;;)
	{
		if (xSemaphoreTake(LCD_SEM,portMAX_DELAY) == 1)
		{
			LCD_clear();
			LCD_vidWriteString("I am Task 2");
			vTaskDelay(1000);	
			
		}
		xSemaphoreGive(LCD_SEM);
		
	}
}

void task_ISR(void *pvParamter)
{
	while (1)
	{
		if (xSemaphoreTake(task_sync_sem, portMAX_DELAY) == pdTRUE)
		{
			LCD_vidWriteString("Button Pressed:D");
			_delay_ms(500);
			LCD_clear();
		}
	}
	
}

void Task_Realse()
{
	xSemaphoreGiveFromISR(task_sync_sem,NULL);
}

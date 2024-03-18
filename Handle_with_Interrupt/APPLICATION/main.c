#include "../RTOS/FreeRTOS.h"
#include "../RTOS/task.h"
#include "../HAL/LCD/LCD.h"
#include "../RTOS/semphr.h"
#include "../MCAL/Interrupt/Interrupt_EXT.h"

#define TASK_ISR_PRIORITY (2)
#define TASK_ISR_STACK_SIZE (configMINIMAL_STACK_SIZE * 2)

void task_ISR(void *pvParamter);
void Task_Realse();

xSemaphoreHandle task_sync_sem;

int main(void)
{
    task_sync_sem = xSemaphoreCreateCounting(1, 0);
    init_lcd();

    Interrupt_EXT_t INT_OBJ = {
        .Call_back_fun = Task_Realse,
        .INT_CONTROL = falling_edge,
        .INT_NUM = EXT_INT_Number_INT0,
    };
    Test_Enable_init(&INT_OBJ);

    xTaskCreate(task_ISR, NULL, TASK_ISR_STACK_SIZE, NULL, TASK_ISR_PRIORITY, NULL);

    vTaskStartScheduler();

    return 0;
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
    xSemaphoreGiveFromISR(task_sync_sem, NULL);
}

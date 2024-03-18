# FreeRTOS with Interrupt and Semaphore Example

This project demonstrates the usage of FreeRTOS on ATmega32 microcontroller with interrupts and semaphores to manage tasks.

## Description

This project utilizes interrupts along with FreeRTOS tasks to control concurrent execution. One task, `task_ISR`, is triggered by an external interrupt (e.g., a button press) to perform an action while synchronized with other tasks.

## Task Priorities

- `Task_ISR`: Priority 1

## Task Codes

- `task_ISR`: Handles the button press interrupt and displays a message on the LCD.

## Task Handling

The `task_ISR` function is triggered by an external interrupt and executes asynchronously. It waits for the semaphore (`task_sync_sem`) to be released before performing its action. Upon execution, it releases the semaphore to allow other tasks to proceed.

## Initialization

1. `task_sync_sem`: Counting semaphore for synchronizing the ISR task with other tasks.
2. Interrupt setup: Configure external interrupt (`INT0`) and its callback function (`Task_Realse`) to release the semaphore.

## Demo

You can watch a demo of this project to see how the interrupt-driven task is triggered in the attached GIF file.

![FreeRTOS Demo GIF](VID_20240319_000534-ezgif.com-video-to-gif-converter.gif)

## Conclusion

This project showcases how FreeRTOS, along with interrupts and semaphores, can be effectively used to manage concurrent tasks on microcontrollers like ATmega32. By leveraging synchronization mechanisms, developers can build robust and efficient embedded systems with ease.

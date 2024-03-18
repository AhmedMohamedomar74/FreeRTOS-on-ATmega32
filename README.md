# FreeRTOS on ATmega32

🔧 This project demonstrates the usage of FreeRTOS on ATmega32 microcontroller to manage two tasks concurrently.

## Description

📝 The project initializes two tasks, `Task1` and `Task2`, which execute concurrently with different priorities. FreeRTOS scheduler handles these tasks efficiently.

## Task Priorities

- `Task1`: Priority 2
- `Task2`: Priority 1

## Task Codes

- `task1_code`: Displays "I am Task 1" on the LCD screen every 2 seconds.
- `task2_code`: Displays "I am Task 2" on the LCD screen every 1 second.

## Task Handling

🔄 FreeRTOS handles the execution of tasks through its task scheduler. Tasks are created using the `xTaskCreate()` function, specifying their respective entry functions (`task1_code` and `task2_code`), stack size, priority, and other parameters.

Once tasks are created, the scheduler decides which task to run based on their priorities. Higher priority tasks preempt lower priority tasks, ensuring that critical tasks are executed promptly.

Tasks can be suspended or delayed using FreeRTOS API functions like `vTaskDelay()`, allowing for precise timing control. When a task is delayed, the scheduler switches to another task until the delay expires.

Overall, FreeRTOS provides a flexible and efficient mechanism for multitasking on microcontrollers like ATmega32, enabling developers to build complex embedded systems with ease.

## Demo GIF

![FreeRTOS Demo GIF](VID_20240318_141622-ezgif.com-video-to-gif-converter.gif)

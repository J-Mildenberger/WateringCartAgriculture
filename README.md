<h1 align="center">Agricultural Watering Cart</h1>

<p align="center">
  <img src="https://img.shields.io/badge/STM32-03234B?style=for-the-badge&logo=stmicroelectronics&logoColor=white" alt="STM32" />
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Hardware-UART-8A2BE2?style=for-the-badge" alt="UART" />
</p>

> This repository contains the embedded software for an agricultural watering cart. Based on Microcontoller STM32F4 (as i had the eval laying around). Firmware is developed bare-metal C utilizing STM32 HAL framework to speed things up. 

Architecture basically is a queue-based event-driven management of asynchronous Inputs which are debounced remote button presses + flow meter pulse signals.

## SW-Modules

The business logic and HALs are separated into distinct C modules located in the `playground/Core/` directory.

### `Application` (`Application.h` / `Application.c`)
The central controller of the system. It implements a high-level state machine for the watering process (Idle, Auto, Manual, FlowMeterTarget, Timeout). It processes asynchronous events from the application queues and handles critical boundaries like the watering WDG.

### `DrPushButton` (`DrPushButton.h` / `DrPushButton.c`)
A HAL for physical buttons. It defines GPIO pin mappings, handles signal debouncing, and translates raw hardware interrupts into categorized logical events (e.g., Watering, MotorCtrl, WaterTank) to be dispatched to the main application via queues.

### `DrFlowMeter` (`DrFlowMeter.h` / `DrFlowMeter.c`)
A driver for calculating water volume by counting sensor pulses. It tracks current consumption and supports defining specific target volumes (e.g., 10 Liters, 20 Liters). It transitions its internal state to notify the application when the target volume has been successfully reached.

### `DrTimer` (`DrTimer.h` / `DrTimer.c`)
Implements timing utilities. (= one-shot timer, cyclic timers, stopwatch). Also WDG Timer is configured here.

### `DrSystem` (`DrSystem.h` / `DrSystem.c`)
System administration utilities for interrupt management. It provides mechanisms for entering/exiting critical sections and granular manipulation of NVIC IRQ priorities, ensuring critical interrupts remain responsive.

### `DrStepperMotor`
#TBD

### `MyQueue` (`MyQueue.h` / `MyQueue.c`)
A generic FIFO ring buffer implementation. This module is the backbone of the project's event-driven architecture, enabling safe and decoupled data transfer between fast Interrupt Service Routines (ISRs) and the slower main processing loop.

### `DrDebug` (`DrDebug.h` / `DrDebug.c`)
Provides developer utilities, including timestamped `printf` wrappers routed via UART, animated keep-alive terminal visuals, and helper functions to stringify enum values (such as button states and watering phases) for simplified state monitoring.

/*
 * DrSystem.c
 *
 *  Created on: May 22, 2025
 *      Author: julia
 */


/* Includes ------------------------------------------------------------------*/
#include "DrSystem.h"

/* Static variables ----------------------------------------------------------*/
uint8_t previouslyEnabledLowPrioIRQs[NVIC_ENTRIES_PRIO_LOW];  // 1 = was enabled before disabling

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

void Disable_And_Record_Enabled_Low_Priority_IRQs(void) {
    for (int i = 0; i < NVIC_ENTRIES_PRIO_LOW; ++i) {
        IRQn_Type irq = (IRQn_Type)i;

        if (irq >= 0) {
            uint32_t prio = NVIC_GetPriority(irq);
            if (prio > 0) {
                if (NVIC->ISER[irq >> 5] & (1U << (irq & 0x1F))) {
                    previouslyEnabledLowPrioIRQs[i] = 1;
                } else {
                    previouslyEnabledLowPrioIRQs[i] = 0;
                }

                NVIC_DisableIRQ(irq);  // Disable it in any case
            } else {
                previouslyEnabledLowPrioIRQs[i] = 0;  // High-priority, untouched
            }
        }
    }
}

void Disable_Low_Priority_IRQs(void) {
    for (int i = 0; i < NVIC_ENTRIES_PRIO_LOW; ++i) {
        IRQn_Type irq = (IRQn_Type)i;
        if (irq >= 0) {  // Skip system exceptions
            uint32_t prio = NVIC_GetPriority(irq);
            if (prio > APPL_NVIC_PRIO_HIGH) {
                NVIC_DisableIRQ(irq);
            }
        }
    }
}

void Reenable_Previously_Enabled_Low_Priority_IRQs(void) {
    for (int i = 0; i < NVIC_ENTRIES_PRIO_LOW; ++i) {
        IRQn_Type irq = (IRQn_Type)i;
        if (irq >= 0) {
            uint32_t prio = NVIC_GetPriority(irq);
            if (prio > 0 && previouslyEnabledLowPrioIRQs[i]) {
                NVIC_ClearPendingIRQ(irq);  // Clear pending just to be safe
                NVIC_EnableIRQ(irq);
                previouslyEnabledLowPrioIRQs[i] = 0;  // Reset state
            }
        }
    }
}



void Clear_Low_Priority_Pending_IRQs(void) {
    for (int i = 0; i < NVIC_ENTRIES_PRIO_LOW; ++i) {
        IRQn_Type irq = (IRQn_Type)i;
        if (irq >= 0) {
            uint32_t prio = NVIC_GetPriority(irq);
            if (prio > APPL_NVIC_PRIO_HIGH) {
                NVIC_ClearPendingIRQ(irq);
            }
        }
    }
}

void Reenable_Low_Priority_IRQs(void) {
    for (int i = 0; i < NVIC_ENTRIES_PRIO_LOW; ++i) {
        IRQn_Type irq = (IRQn_Type)i;
        if (irq >= 0) {
            uint32_t prio = NVIC_GetPriority(irq);
            if (prio > APPL_NVIC_PRIO_HIGH) {
                NVIC_EnableIRQ(irq);
            }
        }
    }
}

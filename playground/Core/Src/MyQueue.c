/*
 * MyQueue.c
 *
 *  Created on: May 24, 2025
 *      Author: julian
 */


/* Includes ------------------------------------------------------------------*/
#include "MyQueue.h"
#include <string.h>
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Static variables ----------------------------------------------------------*/
/* Static Function prototypes -----------------------------------------------*/
/* Static Function definitions -----------------------------------------------*/
/* Function prototypes ------------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

void MyQueue_Init(tQueue *q, void *buffer, uint32_t elementSize, uint32_t capacity) {
    q->buffer = (uint8_t *)buffer;
    q->elementSize = elementSize;
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool MyQueue_IsEmpty(const tQueue *q) {
    return q->count == 0;
}

bool MyQueue_IsFull(const tQueue *q) {
    return q->count == q->capacity;
}

void MyQueue_Reset(tQueue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool MyQueue_Enqueue(tQueue *q, const void *element) {
    if (MyQueue_IsFull(q)) {
        return false;
    }

    uint8_t *dest = q->buffer + (q->head * q->elementSize);
    memcpy(dest, element, q->elementSize);
    q->head = (q->head + 1) % q->capacity;
    q->count++;
    return true;
}

bool MyQueue_Dequeue(tQueue *q, void *element) {
    if (MyQueue_IsEmpty(q)) {
        return false;
    }

    uint8_t *src = q->buffer + (q->tail * q->elementSize);
    memcpy(element, src, q->elementSize);
    q->tail = (q->tail + 1) % q->capacity;
    q->count--;
    return true;
}

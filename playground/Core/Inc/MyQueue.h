/*
 * MyQueue.h
 *
 *  Created on: May 24, 2025
 *      Author: julian
 */

#ifndef INC_MYQUEUE_H_
#define INC_MYQUEUE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* Private defines -----------------------------------------------------------*/
#define QUEUE_SIZE 32

#define QUEUE_DEBUG 1


/* Typedefs and structs ------------------------------------------------------*/
typedef struct {
    uint8_t *buffer;         // pointer to buffer array (cast to uint8_t for generic access)
    uint32_t elementSize;    // size of one element
    uint32_t capacity;       // total number of elements
    uint32_t head;           // enqueue index
    uint32_t tail;           // dequeue index
    uint32_t count;          // number of items currently in queue
    char name[32];
} tQueue;
/* Static variables ----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/


/* Function declarations -----------------------------------------------------*/
/**
 * @brief Initialize the queue
 * @param q Pointer to MyQueue structure
 * @param buffer Pointer to preallocated buffer (must be elementSize * capacity)
 * @param elementSize Size of each element
 * @param capacity Number of elements (max queue length)
 */
void MyQueue_Init(tQueue *q, void *buffer, uint32_t elementSize, uint32_t capacity, const char *pName);
bool MyQueue_Enqueue(tQueue *q, const void *element);
bool MyQueue_Dequeue(tQueue *q, void *element);
bool MyQueue_IsEmpty(const tQueue *q);
bool MyQueue_IsFull(const tQueue *q);
void MyQueue_Reset(tQueue *q);
bool MyQueue_Peek(tQueue *q, void *element);
#endif /* INC_MYQUEUE_H_ */

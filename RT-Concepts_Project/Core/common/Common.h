/*
 * Common.h
 *
 *  Created on: Nov 3, 2025
 *      Author: doomnuke
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include "stm32f7xx_hal.h"
extern UART_HandleTypeDef huart3;

/*
 * Total Resources Available For The Departments
 */
#define POLICE_CARS 5
#define AMBULANCE_CARS 5
#define FIRE_CARS 5

/*
 * For Buffer
 */
#define MSG_LEN 100

/*
 * All of the semaphore counting handlers and queue handler
 */


extern QueueHandle_t Dispatcher_Queue;
extern TaskHandle_t Dispatcher_Handle;

extern TaskHandle_t Police_Dep_Handler;
extern TaskHandle_t Ambulance_Dep_Handler;
extern TaskHandle_t Fire_Dep_Handler;

extern SemaphoreHandle_t Police_Cars_Sem;
extern SemaphoreHandle_t Ambulance_Cars_Sem;
extern SemaphoreHandle_t Fire_Cars_Sem;

typedef enum Departments
{
	Police = 1,
	Ambulance = 2,
	Fire_Dep = 3,
	NUM_DEPARTMENTS
} DepartmentsID;

typedef enum priority
{
	LOW_PRIORITY = 0,
	MEDIUM_PRIORITY,
	HIGH_PRIORITY
}Priority;

typedef struct TaskCreation
{
	DepartmentsID Department;
	Priority Task_Priority;
	SemaphoreHandle_t AssignedSem;
	int EventID;
	char Status;
	char msg[MSG_LEN];
	uint8_t Assigned;
	uint32_t Duration;
} NewTask;

#endif /* COMMON_COMMON_H_ */

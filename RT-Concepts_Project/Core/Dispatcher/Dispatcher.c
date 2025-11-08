/*
 * Dispatcher.c
 *
 *  Created on: Oct 20, 2025
 *      Author: doomnuke
 */

#include <stdio.h>
#include <stdlib.h>
#include "Dispatcher.h"
#include "FreeRTOS.h"

TaskHandle_t Dispatcher_Handle;

SemaphoreHandle_t Police_Cars_Sem;
SemaphoreHandle_t Ambulance_Cars_Sem;
SemaphoreHandle_t Fire_Cars_Sem;

QueueHandle_t Dispatcher_Queue;

void Status()
{
	UBaseType_t Police_Avail = uxSemaphoreGetCount(Police_Cars_Sem);
	UBaseType_t Ambulance_Avail = uxSemaphoreGetCount(Ambulance_Cars_Sem);
	UBaseType_t Fire_Avail = uxSemaphoreGetCount(Fire_Cars_Sem);
	UBaseType_t Total_Avail = Police_Avail + Ambulance_Avail + Fire_Avail;

	  char msg[MSG_LEN];
	  int msg_len = snprintf(msg, sizeof(msg), "Total Available: %lu | Police: %lu | Ambulance: %lu | Fire: %lu\r\n",
			  (unsigned long)Total_Avail, (unsigned long)Police_Avail, (unsigned long)Ambulance_Avail, (unsigned long)Fire_Avail);
	  /*
	   * To Ensure We Don't Send More Than The Buffer Size
	   */
	  if (msg_len < 0) msg_len = 0;
	  if (msg_len >= sizeof(msg)) msg_len = sizeof(msg) - 1;

	  HAL_UART_Transmit(&huart3, (uint8_t *)msg, msg_len, 1000);
}

/*
 * Helper Function
 */
const char* DepartmentIDtoString(int Department)
{
	switch(Department)
	{
		case Police: return "Police";
		case Ambulance: return "Ambulance";
		case Fire_Dep: return "Fire_Dep";
		default: return "Unknown";
	}
}

BaseType_t Take_Car(NewTask *Tasks, SemaphoreHandle_t Own, SemaphoreHandle_t Sem1, SemaphoreHandle_t Sem2)
{
	BaseType_t Taken = pdFALSE;
	char msg[MSG_LEN];
	int Choise;
	int Lend;
	SemaphoreHandle_t SelectedSem = NULL;

	/*
	 * First we the department will try and take its own resource
	 * if false it will randomize between two other departments
	 */
	if (xSemaphoreTake(Own, 100) == pdTRUE)
	{
		Tasks->Assigned = Tasks->Department;
		Tasks->AssignedSem = Own;
		Taken = pdTRUE;

		int len_msg = snprintf(msg,sizeof(msg),"Department %s using its own car\r\n",DepartmentIDtoString(Tasks->Department));
		HAL_UART_Transmit(&huart3, (uint8_t *)msg, len_msg, 500);
	}
	else
	{
		/*
		 * Now we will randomize between the remaining resources
		 * and we will determine by the department ID which department took
		 * the resource to use
		 */
		Choise = rand() % 2;

		Lend = (Tasks->Department + Choise + 1) % 3;

		int len_msg = snprintf(msg,sizeof(msg),"Department %s lent car from department %s\r\n",DepartmentIDtoString(Tasks->Department), DepartmentIDtoString(Lend));
		HAL_UART_Transmit(&huart3, (uint8_t *)msg, len_msg, 500);
	}

	if (Choise == 0)
	{
		SelectedSem = Sem1;
	}
	else
	{
		SelectedSem = Sem2;
	}

	if(xSemaphoreTake(SelectedSem, 100) == pdTRUE)
	{
		Tasks->Assigned = Tasks->Department;
		Tasks->AssignedSem = SelectedSem;
		Taken = pdTRUE;
	}

	return Taken;
}


void Dispatcher(void *pvParams)
{
	char msg[MSG_LEN];
	int msg_len;

	NewTask *Tasks;

	while(1)
	{
		if(Dispatcher_Queue == NULL)
		{
			msg_len = snprintf(msg, sizeof(msg), "Error Couldn't Create The Queue, Exitting...\r\n");
			HAL_UART_Transmit(&huart3, (uint8_t *)msg, msg_len, 3000);
			break;
		}

	if (xQueueReceive(Dispatcher_Queue, &Tasks, portMAX_DELAY) == pdTRUE)
	{
		BaseType_t CarTaken = pdFALSE;


			switch(Tasks->Department)
			{
				case Police:
				{
					CarTaken = Take_Car(Tasks, Police_Cars_Sem, Ambulance_Cars_Sem, Fire_Cars_Sem);
					break;
				}
				case Ambulance:
				{
					CarTaken = Take_Car(Tasks, Ambulance_Cars_Sem, Police_Cars_Sem, Fire_Cars_Sem);
					break;
				}
				case Fire_Dep:
				{
					CarTaken = Take_Car(Tasks, Fire_Cars_Sem, Police_Cars_Sem, Ambulance_Cars_Sem);
					break;
				}
				default:
					break;
			}

			/*
			 * It checks why the resource has been held up and what is the status
			 */
			if(!CarTaken)
			{
				Status(NULL);
				vTaskDelay(500);
				continue;
			}

			switch(Tasks->Department)
			{
				case Police:
				{
					xTaskNotify(Police_Dep_Handler,(uint32_t)Tasks, eSetValueWithOverwrite);
					break;
				}
				case Ambulance:
				{
					xTaskNotify(Ambulance_Dep_Handler,(uint32_t)Tasks, eSetValueWithOverwrite);
					break;
				}
				case Fire_Dep:
				{
					xTaskNotify(Fire_Dep_Handler,(uint32_t)Tasks, eSetValueWithOverwrite);
					break;
				}
				default:
					break;

			}
		}
	}
}

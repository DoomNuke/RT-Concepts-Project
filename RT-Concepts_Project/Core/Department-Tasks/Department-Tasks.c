/*
 * Dispatcher_Tasks.c
 *
 *  Created on: Oct 20, 2025
 *      Author: doomnuke
 */


#include "../Department-Tasks/Department-Tasks.h"
#include "../Dispatcher/Dispatcher.h"

#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



TickType_t Start_Tick,End_Tick;

TaskHandle_t Police_Dep_Handler;
TaskHandle_t Ambulance_Dep_Handler;
TaskHandle_t Fire_Dep_Handler;


/*
 * Pool of the total amount of resources of each department
 * and how much resources are in total
 */

void ExecuteMission(NewTask Event, const char *msg_text)
{

	char msg[MSG_LEN];
	int msg_len = snprintf(msg, sizeof(msg), "%s\r\n", msg_text);
	HAL_UART_Transmit(&huart3,(uint8_t *)msg, msg_len, 500);

	Start_Tick = xTaskGetTickCount();
	vTaskDelay(pdMS_TO_TICKS(Event.Duration));
	End_Tick = xTaskGetTickCount();

	const char *Dep = (Event.Department == Police) ? "Police" :
					  (Event.Department == Ambulance) ? "Ambulance" :
					  (Event.Department == Fire_Dep) ? "Fire_Dep" : "Unknown";

	msg_len = snprintf(msg, sizeof(msg), "[%s]Completed The Task in %lu ticks\r\n", Dep ,(unsigned long)(End_Tick - Start_Tick));
	HAL_UART_Transmit(&huart3,(uint8_t *)msg, msg_len, 500);
}


void PoliceTasks(void *pvParams)
{
	NewTask *Event;
	uint32_t copy_value;



	for(;;)
	{

		 /*
		  * waiting forever for a notification from the dispatcher
		  */
		if(xTaskNotifyWait(0, 0, &copy_value, portMAX_DELAY) != pdTRUE)
		{
			continue;
		}

		Event = (NewTask *)copy_value;




		Event->Duration = MIN_INTERVAL_TASK + (rand() % MAX_INTERVAL_TASK);

		switch(Event->EventID)
		{
			case PATROL:
			{
				ExecuteMission(*Event, "[POLICE]Patrolling Over The Area...");
				break;
			}
			case CHASE:
			{
				ExecuteMission(*Event, "[POLICE]Chasing A Robber...");
				break;
			}
			case INVESTIGATION:
			{
				ExecuteMission(*Event, "[POLICE]Investigating Suspect...");
				break;
			}
		}
		/*
		 * Notify THe Dispatcher the mission is complete
		 */
		xSemaphoreGive(Event->AssignedSem);
		xTaskNotifyGive(Dispatcher_Handle);
		vPortFree(Event);
	}

}

void AmbulanceTasks(void *pvParams)
{
	NewTask *Event;
	uint32_t copy_value;


	for(;;)
	{
		/*
		 * wait forever for the notification from the dispatcher to come in
		 */
		if(xTaskNotifyWait(0, 0, &copy_value, portMAX_DELAY) != pdTRUE)
		{
			continue;
		}

		Event = (NewTask *)copy_value;




		/*
		 * Duration of the mission a randomizer between a 1 - 10 ticks
		 */
		Event->Duration = MIN_INTERVAL_TASK + (rand() % MAX_INTERVAL_TASK);

		switch(Event->EventID)
		{
			case INJURY:
			{
				ExecuteMission(*Event, "[AMBULANCE]Injury Reported...");
				break;
			}
			case UNCONSCIOUS:
			{
				ExecuteMission(*Event, "[AMBULANCE]Unconscious Report...");
				break;
			}
			case SEIZURE:
			{
				ExecuteMission(*Event, "[AMBULANCE]Seizure Reported...");
				break;
			}
		}

		/*
		 * Notify THe Dispatcher the mission is complete
		 */
		xSemaphoreGive(Event->AssignedSem);
		xTaskNotifyGive(Dispatcher_Handle);
		vPortFree(Event);
	}
}


void FireDepTasks(void *pvParams)
{
	NewTask *Event;
	uint32_t copy_value;


	for(;;)
	{
		/*
		 * wait forever for the notification from the dispatcher to come in
		 */
		if(xTaskNotifyWait(0, 0, &copy_value, portMAX_DELAY) != pdTRUE)
		{
			continue;
		}

		Event = (NewTask *)copy_value;



		/*
		 * Duration of the mission a randomizer between a 1 - 10 ticks
		 */
		Event->Duration = MIN_INTERVAL_TASK + (rand() % MAX_INTERVAL_TASK);

		switch(Event->EventID)
		{
			case FIRE:
			{
				ExecuteMission(*Event, "[FIRE]Fire Reported...");
				break;
			}
			case SEARCH:
			{
				ExecuteMission(*Event, "[FIRE]Search And Rescue Mission...");
				break;
			}
			case CAT:
			{
				ExecuteMission(*Event, "[FIRE]Cat stuck on roof...");
				break;
			}
		}


		/*
		 * Notify THe Dispatcher the mission is complete
		 */
		xSemaphoreGive(Event->AssignedSem);
		xTaskNotifyGive(Dispatcher_Handle);

		vPortFree(Event);
	}
}

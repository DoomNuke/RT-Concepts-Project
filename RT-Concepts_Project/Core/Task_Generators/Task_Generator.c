/*
 * Task_Generator.c
 *
 *  Created on: Oct 26, 2025
 *      Author: doomnuke
 */
#include <stdlib.h>
#include "../Task_Generators/Task_Generator.h"
#include "../common/Common.h"
/*Generator For Each Department And A Randomizer
 *
 * the generator choosing between each department each time, with a randomizing interval
 * between a second and 5 seconds, choosing between 3 missions each department has and
 * according to the priority it's been sent to the queue first
 */

/*
 * Giving each task an priority for each mission
*/
const Priority PoliceTaskPriority[NUM_POLICE_TASKS] = {MEDIUM_PRIORITY, HIGH_PRIORITY, LOW_PRIORITY};
const Priority AmbulanceTaskPriority[NUM_AMBULANCE_TASKS] = {MEDIUM_PRIORITY, HIGH_PRIORITY,HIGH_PRIORITY};
const Priority FireDepTaskPriority[NUM_FIRE_TASKS] = {HIGH_PRIORITY, MEDIUM_PRIORITY, LOW_PRIORITY};

void Generator(void *pvParams)
{
	uint32_t Rand_Time;

	for(;;)
	{
		NewTask *Tasks = pvPortMalloc(sizeof(NewTask));
		Rand_Time = MIN_INTERVAL + (rand() % (MAX_INTERVAL - MIN_INTERVAL + 1));

		/*So it can always start from 1 - 3 */
		Tasks->Department = 1 +(rand() % NUM_DEPARTMENTS - 1);

		switch(Tasks->Department)
		{
			case Police:
			{
				 Tasks->EventID = rand() % NUM_POLICE_TASKS;
				 Tasks->Task_Priority = PoliceTaskPriority[Tasks->EventID];
				 break;
			}
			case Ambulance:
			{
				 Tasks->EventID = rand() % NUM_AMBULANCE_TASKS;
				 Tasks->Task_Priority = AmbulanceTaskPriority[Tasks->EventID];
				 break;
			}
			case Fire_Dep:
			{
				 Tasks->EventID = rand() % NUM_FIRE_TASKS;
				 Tasks->Task_Priority = FireDepTaskPriority[Tasks->EventID];
				 break;
			}
			default:

				break;
		}

		if (Dispatcher_Queue != NULL)
		{
			xQueueSend(Dispatcher_Queue, &Tasks, portMAX_DELAY);
		}

		vTaskDelay(pdMS_TO_TICKS(Rand_Time));
	}
}

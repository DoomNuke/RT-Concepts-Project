/*
 * Dispatcher-Tasks.h
 *
 *  Created on: Oct 20, 2025
 *      Author: doomnuke
 */

#ifndef DEPARTMENT_TASKS_DEPARTMENT_TASKS_H_
#define DEPARTMENT_TASKS_DEPARTMENT_TASKS_H_

#include "../Dispatcher/Dispatcher.h"
#include "../common/Common.h"

/*
 *  timeout variables of 1 to 5 ticks of each new task generated and sent to the dispatcher
 *  semaphore handlers = the amount of each departments resources
 *  i decided to use counting semaphore to keep count on each resource
 */

#define MSG_LEN 100
#define MIN_INTERVAL_TASK 1000
#define MAX_INTERVAL_TASK 10000

/*
 * Counting Semaphore For The Amount Of The Resources,
 * Queues Of Each Department,
 * TickType_t For Tracking The Amount of Ticks For Each Task
 */

extern TickType_t Start_Tick,End_Tick;



/*
 * Helper Function for printing out the tasks, and also tracking the ticks
 */

void ExecuteMission(NewTask Event, const char *msg_text);

void PoliceTasks(void *pvParams);

void AmbulanceTasks(void *pvParams);

void FireDepTasks(void *pvParams);





#endif /* DEPARTMENT_TASKS_DEPARTMENT_TASKS_H_ */

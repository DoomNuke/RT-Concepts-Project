/*
 * Dispatcher.h
 *
 *  Created on: Oct 20, 2025
 *      Author: doomnuke
 */

#ifndef DISPATCHER_DISPATCHER_H_
#define DISPATCHER_DISPATCHER_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "../Task_Generators/Task_Generator.h"
#include "../Department-Tasks/Department-Tasks.h"
#include "../common/Common.h"


/*
 *  Status = helper function of the dispatching status if not dispatched
 * DepartmentIDtostring = just an helper function
 *	Take_Car = Attempt to grab the semaphore from each department
 * Dispatcher = The main handler of the dispatcher
 */

void Status();

const char* DepartmentIDtoString(int Department);

BaseType_t Take_Car(NewTask *Tasks, SemaphoreHandle_t Own, SemaphoreHandle_t Sem1, SemaphoreHandle_t Sem2);

void Dispatcher(void *pvParams);



#endif /* DISPATCHER_DISPATCHER_H_ */

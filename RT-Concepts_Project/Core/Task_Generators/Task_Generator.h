/*
 * Task_Generator.h
 *
 *  Created on: Oct 26, 2025
 *      Author: doomnuke
 */

#ifndef TASK_GENERATORS_TASK_GENERATOR_H_
#define TASK_GENERATORS_TASK_GENERATOR_H_

#include "../Dispatcher/Dispatcher.h"
#include "../common/Common.h"

#define MIN_INTERVAL 1000
#define MAX_INTERVAL 5000

void Generator(void *pvParams);

/*
 * Task Creation with each department
 * each enum struct has its own missions and the total of each department kind of mission
 */
typedef enum Police_Tasks
{
	PATROL = 0,
	CHASE,
	INVESTIGATION,
	NUM_POLICE_TASKS
} Police_Tasks_ID;


typedef enum Ambulance_Tasks
{
	INJURY = 0,
	UNCONSCIOUS,
	SEIZURE,
	NUM_AMBULANCE_TASKS
} Ambulance_Tasks_ID;

typedef enum Fire_Tasks
{
	FIRE = 0,
	SEARCH,
	CAT,
	NUM_FIRE_TASKS
} Fire_Tasks_ID;

#endif /* END TASK_GENERATORS_TASK_GENERATOR_H_  */

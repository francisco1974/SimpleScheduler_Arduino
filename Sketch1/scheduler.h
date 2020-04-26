
#include "types.h"
#include "TimerOne.h"
#include <stdio.h>
#include <string.h>

#ifndef _SCHEDULER_h
#define _SCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



void clear_event_list(event_handler_t* event_handler);
bool post_event(unsigned int new_event, event_handler_t* event_handler);
bool free_event(event_t* old_event, event_handler_t* event_handler);

bool scheduler_start(void);
void change_task_status(unsigned int new_status, TCBstruct* task_pointer);
void replace_task(TCBstruct** task_destiny, TCBstruct* task_source);
bool add_task(TCBstruct** task_list, TCBstruct* new_task_pointer);
bool delete_task(TCBstruct** task_list, TCBstruct* new_task_pointer);







#endif


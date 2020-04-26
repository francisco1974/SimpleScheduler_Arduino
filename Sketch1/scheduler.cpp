
#include "types.h"
#include "TimerOne.h"
#include "scheduler.h"
#include <stdio.h>
#include <string.h>


extern TCBstruct* task_list[TASK_NUMBER];

event_t event;
pointer_t pppL;
pointer_t pppR;

event_handler_t event_handler = { true,0,0,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };

bool scheduler_start(void)
{
    int i;
    event_t* event;
    for (;;) {
        if (!free_event(event, &event_handler))// is the list of events empty
        {
            (*task_list[0]->ftpr)(*event, &pppL, &pppR);// idle_fcn
        }
        else
        {
            for (i = 1;i < TASK_NUMBER;i++)
            {
                if (!(task_list[i]->state == HALT)&&(task_list[i]!=NULL))
                {
                    (*task_list[i]->ftpr)(*event, &pppL, &pppR);
                }
            }
        }
    }
}

bool post_event(unsigned int new_event, event_handler_t* event_handler)
{
    if (event_handler->event_list[event_handler->first_free_position] != NULL) return false;

    event_handler->event_list[event_handler->first_free_position] = new_event;

    event_handler->first_free_position++;

    if (event_handler->first_free_position >= EVENT_LIST_SIZE)
    {
        event_handler->first_free_position = 0;
    }
    event_handler->event_list_empty = false;

    return true;
}

bool free_event(event_t* old_event, event_handler_t* event_handler)
{

    *old_event = NULL;

    if (event_handler->event_list[event_handler->oldest_event_position] == NULL) return false;

    *old_event = event_handler->event_list[event_handler->oldest_event_position];

    event_handler->event_list[event_handler->oldest_event_position] = NULL;

    event_handler->oldest_event_position++;

    if (event_handler->oldest_event_position >= EVENT_LIST_SIZE)
    {
        event_handler->oldest_event_position = 0;
    }
    if (event_handler->oldest_event_position == event_handler->first_free_position)
    {
        event_handler->event_list_empty = true;
    }
    return true;
}

void clear_event_list(event_handler_t* event_handler)
{
    unsigned int i;
    for (i = 0;i < EVENT_LIST_SIZE;i++)
    {
        event_handler->event_list[i]        = NULL;
    }

    event_handler->first_free_position      = 0;
    event_handler->oldest_event_position    = 0;
    event_handler->event_list_empty         = true;
}

void change_task_status(unsigned int new_status, TCBstruct* task_pointer)
{
    task_pointer->state = new_status;
}

void replace_task(TCBstruct** task_destiny, TCBstruct* task_source)
{
    *task_destiny = task_source;
}

bool add_task(TCBstruct** task_list,TCBstruct* new_task_pointer)
{
    unsigned int i;
    TCBstruct** task_list_aux = task_list;
    
    for (i = 0;i < TASK_NUMBER;i++)
    {
        if (*task_list_aux == new_task_pointer) {
            return false;                           // No repeat task
        }
        task_list_aux++;
    }

    for (i = 0;i < TASK_NUMBER;i++)
    {
        if(*task_list == NULL){
            *task_list = new_task_pointer;
            return true;                            // New task success
        }
        task_list++;
    }
    return false;                                   // No free space for new task
}
bool delete_task(TCBstruct** task_list, TCBstruct* task_to_delete_pointer)
{
    unsigned int i;
    for (i = 0;i < TASK_NUMBER;i++)
    {
        if (*task_list == task_to_delete_pointer) 
        {
            *task_list = NULL;
            return true;
        }
        task_list++;
    }
    return false;
}




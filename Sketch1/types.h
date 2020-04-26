#pragma once


#include <stdio.h>
#include <string.h>


#define TASK_NUMBER         10
#define EVENT_LIST_SIZE     10
#define MAX_CHAR            20 

typedef enum task_priority_enum_t   { LOW_PRIORITY, MEDIUM_PRIORITY, HIGH_PRIORITY, CRITICAL_PRIORITY };
typedef enum task_status_enum_t     { NOT_READY, READY, SLEEP, HALT };
typedef enum task_events_enum_t     { INIT_EVT, RUN_EVT, IDLE_EVT, SLEEP_EVT, TIMER_10MS_EVT, TIMER_100MS_EVT, TIMER_1S_EVT, TIMER_10S_EVT, HALT_EVT };

typedef void*           pointer_t;
typedef unsigned int    event_t;


typedef struct event_handler_t {
    bool                    event_list_empty;
    unsigned int            oldest_event_position;
    unsigned int            first_free_position;
    task_events_enum_t      event_list[EVENT_LIST_SIZE];
};


typedef struct TCBstruct {
    void (*ftpr)(event_t event, pointer_t* pppL, pointer_t* pppR);  // the function pointer
    task_status_enum_t          state;                              // the task state
    task_priority_enum_t        priority; 
    unsigned int                delay;                              // sleep delay in ms
    unsigned long int           timestamp;                          // Time stamo for debug purposes
    unsigned char               string[MAX_CHAR];                   // Alias to identify Task
};

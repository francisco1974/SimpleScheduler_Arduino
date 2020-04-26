/*
 Name:    scheduler.ino
 Created: 12/04/2020 15:18:16
 Author:  franc
*/

#include "types.h"
#include "TimerOne.h"
#include "scheduler.h"
#include "Rotary_encoder_task.h"

#include <stdio.h>
#include <string.h>

extern event_t          event;
extern pointer_t        pppL;
extern pointer_t        pppR;
extern event_handler_t  event_handler;

void timer_one_callback();
void idle_fcn(event_t event, pointer_t* pppL, pointer_t* pppR);
void tarea_2(event_t event, pointer_t* pppL, pointer_t* pppR);
void tarea_3(event_t event, pointer_t* pppL, pointer_t* pppR);
void tarea_4(event_t event, pointer_t* pppL, pointer_t* pppR);
void tarea_5(event_t event, pointer_t* pppL, pointer_t* pppR);
void tarea_6(event_t event, pointer_t* pppL, pointer_t* pppR);

unsigned int        counter         = 0;
unsigned int        counter_10ms    = 0;
unsigned int        counter_100ms   = 0;
unsigned int        counter_1s      = 0;
unsigned int        counter_10s     = 0;
unsigned long int   timestamp       = 0;
int                 rotary_encoder_counter = 0;

const byte A_rotary_encoder = 2;
const byte B_rotary_encoder = 3;

rotary_encoder_handler_t rotary_encoder_handler = { A_rotary_encoder, \
                                                    B_rotary_encoder ,\
                                                    & rotary_encoder_counter,\
                                                    ROTARY_IDLE };
TCBstruct idle_task = {
    & idle_fcn, NOT_READY, LOW_PRIORITY,    0,       0,     "idle_fcn" };
TCBstruct rotary_encoder_tsk = {
    & rotary_encoder_fcn, NOT_READY, LOW_PRIORITY, 0, 0,    "rotary_encoder_fcn" };
TCBstruct task_2 = {
    &tarea_2,   NOT_READY,  LOW_PRIORITY,   0,      0,      "task 2" };
TCBstruct task_3 = {
    &tarea_3,   NOT_READY,  LOW_PRIORITY,   0,      0,      "task 3" };
TCBstruct task_4 = {
    &tarea_4,   NOT_READY,  LOW_PRIORITY,   0,      0,      "task 4" };
TCBstruct task_5 = {
    &tarea_5,   NOT_READY,  LOW_PRIORITY,   0,      0,      "task 5" };
TCBstruct task_6 = {
    &tarea_6,   NOT_READY,  LOW_PRIORITY,   0,      0,      "task 6" };


TCBstruct* task_list[TASK_NUMBER] =
{   & idle_task ,
    & rotary_encoder_tsk,
    & task_2,   
    & task_3,   
    & task_4,   
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
};



void tarea_2(event_t event, pointer_t* pppL, pointer_t* pppR)
{

    switch (event)
    {
    case INIT_EVT:
        break;
    case TIMER_10MS_EVT:
        break;
    case TIMER_100MS_EVT:
          *pppL = (pointer_t)&timestamp;
        break;
    case TIMER_1S_EVT:
        Serial.println("2 tarea TIMER 1s \n");
        break;
    case TIMER_10S_EVT:
        break;
    default:
        break;
    }

}
void tarea_3(event_t event, pointer_t* pppL, pointer_t* pppR)
{

    switch (event)
    {
    case INIT_EVT:
        break;
    case TIMER_10MS_EVT:
        break;
    case TIMER_100MS_EVT:
        break;
    case TIMER_1S_EVT:
        Serial.println("3 tarea TIMER 1s \n");
        break;
    case TIMER_10S_EVT:
        break;

    default:
        break;
    }
}
void tarea_4(event_t event, pointer_t* pppL, pointer_t* pppR)
{

    switch (event)
    {
    case INIT_EVT:
        break;
    case TIMER_10MS_EVT:
        break;
    case TIMER_100MS_EVT:
        break;
    case TIMER_1S_EVT:
        Serial.println("4 tarea TIMER 1s \n");
        break;
    case TIMER_10S_EVT:
        break;
    default:
        break;
    }
}

void tarea_5(event_t event, pointer_t* pppL, pointer_t* pppR)
{

    switch (event)
    {
    case INIT_EVT:
        break;
    case TIMER_10MS_EVT:
        break;
    case TIMER_100MS_EVT:
        break;
    case TIMER_1S_EVT:
        Serial.println("5 tarea TIMER 1s \n");
        break;
    case TIMER_10S_EVT:

        break;
    default:
        break;
    }
}

void tarea_6(event_t event, pointer_t* pppL, pointer_t* pppR)
{

    switch (event)
    {
    case INIT_EVT:
        break;
    case TIMER_10MS_EVT:
        break;
    case TIMER_100MS_EVT:
        break;
    case TIMER_1S_EVT:
        Serial.println("6 tarea TIMER 1s \n");
        break;
    case TIMER_10S_EVT:

        break;
    default:
        break;
    }
}




void timer_one_callback()
{
    timestamp++;
    post_event(TIMER_10MS_EVT, &event_handler);
    counter_10ms++;

    if (counter_10ms > 10 - 1)
    {
        counter_10ms = 0;
        post_event(TIMER_100MS_EVT, &event_handler);
        counter_100ms++;
    }

    if (counter_100ms > 10 - 1)
    {
        counter_100ms = 0;
        post_event(TIMER_1S_EVT, &event_handler);
        counter_1s++;
    }

    if (counter_1s > 10 - 1)
    {
        counter_1s = 0;
        post_event(TIMER_10S_EVT, &event_handler);
        counter_10s++;
    }

    if (counter_10s > 10 - 1)
    {
        counter_10s = 0;
    }
}



void setup() 
{
    Serial.begin(115200);
    Timer1.initialize(10000);                       // initialize timer1, and set a 1/2 second period
    Timer1.attachInterrupt(timer_one_callback);     // attaches callback() as a timer overflow interrupt
    rotary_encoder_start(&rotary_encoder_handler);
}


void loop()
{
    scheduler_start();
    while (1U)
    {
    }
}


void idle_fcn(event_t event, pointer_t* pppL, pointer_t* pppR)
{
   
     String str;
     byte command;
    
     if (Serial.available() > 0)
     {
         command = Serial.parseInt();

         Serial.println(command, DEC);
         Serial.println(" ---- \n");

         switch (command)
         {
         case 1:
             delete_task(task_list, &rotary_encoder_tsk);
             break;
         case 2:
             delete_task(task_list, &task_2);
             break;
         case 3:
             delete_task(task_list, &task_3);
             break;
         case 4:
             delete_task(task_list, &task_4);
             break;
         case 5:
             delete_task(task_list, &task_5);
             break;
         case 6:
             delete_task(task_list, &task_6);
             break;
         case 7:
             add_task(task_list, &rotary_encoder_tsk);
             break;
         case 8:
             add_task(task_list, &task_2);
             break;
         case 9:
             add_task(task_list, &task_3);
             break;
         case 10:
             add_task(task_list, &task_4);
             break;
         case 11:
             add_task(task_list, &task_5);
             break;
         case 12:
             add_task(task_list, &task_6);
             break;

         default:
             break;
         }
     }
}
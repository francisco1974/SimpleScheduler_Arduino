#include <Arduino.h>
#include "types.h"
#include "TimerOne.h"
#include "scheduler.h"
#include "Rotary_encoder_task.h"


unsigned int               rotary_encoder_previous = 0;
unsigned int               rotary_encoder_display = 0;

rotary_encoder_handler_t* rotary_encoder_handler_pointer;

void rotary_encoder_start(rotary_encoder_handler_t* rotary_encoder_handler)
{

    rotary_encoder_handler_pointer = rotary_encoder_handler;

    Serial.println(*(rotary_encoder_handler->rotary_counter_pointer), DEC);

    pinMode(rotary_encoder_handler_pointer->port_A, INPUT);
    pinMode(rotary_encoder_handler_pointer->port_B, INPUT);

	attachInterrupt(digitalPinToInterrupt(rotary_encoder_handler_pointer->port_A), rotary_encoder_callback, FALLING);

}


void rotary_encoder_callback(void)
{
    if (digitalRead(rotary_encoder_handler_pointer->port_B))
    {
       *rotary_encoder_handler_pointer->rotary_counter_pointer+=1;
        rotary_encoder_handler_pointer->status = ROTARY_UP;
    }
    else
    {
        *rotary_encoder_handler_pointer->rotary_counter_pointer-=1;
        rotary_encoder_handler_pointer->status = ROTARY_DOWN;
    }  
}


void rotary_encoder_fcn(event_t event, pointer_t* pppL, pointer_t* pppR)
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

        Serial.println("rotary_encoder_fcn\n");
        unsigned long int* time = (unsigned long int*)(*pppL);
        Serial.println(*time, DEC);

        Serial.println(*rotary_encoder_handler_pointer->rotary_counter_pointer, DEC);

        break;
    case TIMER_10S_EVT:
        break;

    default:
        break;
    }
}
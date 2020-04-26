#pragma once

typedef enum  rotary_encoder_status_enum_t {ROTARY_IDLE, ROTARY_UP, ROTARY_DOWN, ROTARY_SWITCH } ;



typedef struct rotary_encoder_handler_t
{
	const char port_A;
	const char port_B;
	int* rotary_counter_pointer;
	rotary_encoder_status_enum_t  status;
};

void rotary_encoder_start(rotary_encoder_handler_t* rotary_encoder_handler);
void rotary_encoder_callback(void);
void rotary_encoder_fcn(event_t event, pointer_t* pppL, pointer_t* pppR);


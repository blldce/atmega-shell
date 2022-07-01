#ifndef _CMD_FUNC_H_
#define _CMD_FUNC_H_


#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "cmd_util.h"
#include "uart_text_io.h"

//Total functions number
#define FUNC_NUM        3

//Function and command tables
extern void (*sys_func[])(uint8_t* p_arg[],uint8_t num_args);
extern uint8_t* sys_func_names[];

#endif

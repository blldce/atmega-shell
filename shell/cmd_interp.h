#ifndef _CMD_INTERP_H_
#define _CMD_INTERP_H_


#include <stdint.h>
#include "cmd_func.h"
#include "cmd_util.h"
#include "cmd_shell.h"

#define MAX_CMD_LEN         SHELL_INPUT_LEN
#define MAX_ARGS_NUM        SHELL_ARGS_MAX

//Command interpreting function.
//Takes command line and executes appropriate handler.
uint8_t cmd_exec(uint8_t* cmdline);

#endif

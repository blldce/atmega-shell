#ifndef _CMD_SHELL_H_
#define _CMD_SHELL_H_


//Maximum user input length in characters.
#define SHELL_INPUT_LEN		20
//Maximum number of arguments that can be passed with a command.
#define SHELL_ARGS_MAX		5

//Main user interface routine.
//Place it in your main() instead of while (1).
void cmd_process_loop(void);

#endif

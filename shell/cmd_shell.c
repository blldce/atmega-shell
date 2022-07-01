#include "cmd_shell.h"
#include "uart_text_io.h"
#include "cmd_interp.h"



//System messages
uint8_t msg_cmd_err[] PROGMEM = {"Input error - unknown command.\r\n"};
uint8_t msg_con[] PROGMEM = {"cmd: "};
uint8_t msg_start[] PROGMEM = {"AVR command shell v1.0 \r\n\r\n"};
uint8_t msg_newline[] PROGMEM = {"\r\n"};

uint8_t cmdline[SHELL_INPUT_LEN];

void cmd_process_loop(void)
{
  TIO_Init();
  TIO_PrintPgmMsg(msg_start);

  while (1)
  {
  TIO_PrintPgmMsg(msg_con);
	TIO_TextInput(cmdline);

	TIO_PrintPgmMsg(msg_newline);

	if (!(cmd_exec(cmdline)))
	  TIO_PrintPgmMsg(msg_cmd_err);

	TIO_PrintPgmMsg(msg_newline);
  }
}

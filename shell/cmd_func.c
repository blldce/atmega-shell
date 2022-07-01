#include "cmd_func.h"


//Command line functions and their data

uint8_t help_text[] PROGMEM = {

  "AVR command shell v1.0							\r\n\
  Currently supports three commands:				\r\n\
  help - display this help;							\r\n\
  listarg - lists its arguments;					\r\n\
  led <color> <state> - control LEDs.				\r\n\
  \t color: green/blue;								\r\n\
  \t state: on/off/blink/noblink					\r\n"
};

void print_help(uint8_t* p_arg[],uint8_t num_args)
{
	TIO_PrintPgmMsg(help_text);
}

uint8_t msg_args[] PROGMEM = {"Arguments passed:\r\n"};
uint8_t msg_noargs[] PROGMEM = {"No arguments passed.\r\n"};

void print_args(uint8_t* p_arg[],uint8_t num_args)
{
    int8_t i;

	if (num_args)
	{
      TIO_PrintPgmMsg(msg_args);

	  for (i=0; i<num_args; i++)
	  {
	    TIO_TextOutput(p_arg[i]);
		TIO_CharOutput('\r');
		TIO_CharOutput('\n');
	  }
    }
	else
	  TIO_PrintPgmMsg(msg_noargs);

}

uint8_t ledcmd_on[] PROGMEM = {"on"};
uint8_t ledcmd_off[] PROGMEM = {"off"};
uint8_t ledcmd_blink[] PROGMEM = {"blink"};
uint8_t ledcmd_noblink[] PROGMEM = {"noblink"};

uint8_t ledsel_green[] PROGMEM = {"green"};
uint8_t ledsel_blue[] PROGMEM = {"blue"};

uint8_t ledmsg_ok[] PROGMEM = {"LED OK\r\n"};
uint8_t ledmsg_err_noparam[] PROGMEM = {"Error - too few parameters.\r\n"};
uint8_t ledmsg_err_unknown[] PROGMEM = {"Error - unknown parameter.\r\n"};
uint8_t ledmsg_err_unsupp_led[] PROGMEM = {"Unsupported LED, using green as default.\r\n"};

volatile uint8_t ledtype;

ISR (TIMER1_COMPA_vect)
{
  TCNT1=0;

  if (PORTB & (1<<ledtype))
    PORTB&=~(1<<ledtype);
  else
    PORTB|=(1<<ledtype);
}

void handle_led(uint8_t* p_arg[],uint8_t num_args)
{
  if (num_args>1)
  {
    if (str_equal_pgm(p_arg[0],ledsel_green))
	  ledtype=PB1;
    else
      if (str_equal_pgm(p_arg[0],ledsel_blue))
	    ledtype=PB2;
	  else
	  {
	    ledtype=PB1;
	    TIO_PrintPgmMsg(ledmsg_err_unsupp_led);
      }

    if (str_equal_pgm(p_arg[1],ledcmd_on))
	{
	  DDRB|=(1<<ledtype);
	  PORTB|=(1<<ledtype);

	  TIO_PrintPgmMsg(ledmsg_ok);

	  return;
	}

	if (str_equal_pgm(p_arg[1],ledcmd_off))
	{
	  PORTB&=~(1<<ledtype);

	  TIO_PrintPgmMsg(ledmsg_ok);

	  return;
	}

	if (str_equal_pgm(p_arg[1],ledcmd_blink))
	{
	  DDRB|=(1<<ledtype);
	  PORTB|=(1<<ledtype);

	  OCR1A=0xF424;
	  TIMSK1=(1<<OCIE1A);
	  TCCR1B=(1<<CS11) | (1<<CS10);

	  sei();

	  TIO_PrintPgmMsg(ledmsg_ok);

	  return;
	}

	if (str_equal_pgm(p_arg[1],ledcmd_noblink))
	{
	  TCCR1B=0;

	  TIO_PrintPgmMsg(ledmsg_ok);

	  return;
	}

	TIO_PrintPgmMsg(ledmsg_err_unknown);
  }
  else
    TIO_PrintPgmMsg(ledmsg_err_noparam);
}

//Function table
void (*sys_func[])(uint8_t* p_arg[],uint8_t num_args) PROGMEM = {

    print_help,
    print_args,
	handle_led

};

//Command line alias table
uint8_t funcname1[] PROGMEM = {"help"};
uint8_t funcname2[] PROGMEM = {"listarg"};
uint8_t funcname3[] PROGMEM = {"led"};

uint8_t *sys_func_names[] PROGMEM = {

    funcname1,
    funcname2,
	funcname3

};

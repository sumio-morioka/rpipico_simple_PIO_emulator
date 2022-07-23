/////////////////////////////////////////////////////////////////////////////////////////
// RPi Pico PIO emulator for C
// sample 2
/////////////////////////////////////////////////////////////////////////////////////////

#define	PIO_OUT_GPIO_BIT_BY_BIT
//#undef	PIO_OUT_GPIO_BIT_BY_BIT

//#define	PIO_IN_GPIO_BIT_BY_BIT
#undef	PIO_IN_GPIO_BIT_BY_BIT

//#define DISP_ASM_STDOUT
#undef DISP_ASM_STDOUT

#define DISP_TRACE_STDOUT
//#undef DISP_TRACE_STDOUT

#include "picopio_emu.h"


int main(int argc, char *argv[])
{
	///////////////////////////////////////////////////////////////
	// asm code
	///////////////////////////////////////////////////////////////
	pio_code_start_simple(
		"pio0_sm1",		// char *funcname
		1,				// int	sm_id

		16,				// int in_pins
		2,				// int in_num
		12,				// int out_pins
		1,				// int out_num
		8,				// int sideset_pins
		3,				// int sideset_num
		true			// bool sidest_opt
	);

	//----> actual code

	pio_wrap_target();

	pio_wait(/* polarity */ false,	/* src */ PIO_PIN,	/* index */ 0,	/* rel */ false,	0x01, 0);
	pio_wait(/* polarity */ true,	/* src */ PIO_PIN,	/* index */ 0,	/* rel */ false,	0x02, 0);		// wait pin0
	pio_set(/* dest */ PIO_Y,		/* data */ 4,											0x00, 0);		// loop count

	pio_label("loop_top");
	pio_pull(/* ifempty */ false,	/* block */ true,										0x03, 0);		// osr = fifo
	pio_mov(/* dest */ PIO_X,		/* op */ PIO_INVERT,/* src */ PIO_OSR,					0x04, 1);		// x = !osr
	pio_out(/* dest */ PIO_PINS,	/* bitcnt */ 1,											0x00, 0);
	pio_in(/* src */ PIO_X,			/* bitcnt */ 32,										PIO_UNUSE, 0);	// isr = x
	pio_push(/* iffull */false,		/* block */ true, 										0x05, 0);		// push isr
	pio_jmp(/* cond */ PIO_Y_NEQ_0_DEC,	/* lable */ "loop_top",								0x00, 0);		// jmp reg_recovery

	pio_label("loop_end");
	pio_in(/* src */ PIO_Y,			/* bitcnt */ 32,										0x00, 0);		// isr = y
	pio_push(/* iffull */ false,	/* block */ true, 										0x00, 0);		// push isr
	pio_irq(/* clr */ false,		/* wait */ true,	/* index */ 1,	/* rel */ false,	0x00, 0);		// irq

	pio_wait(/* polarity */ false,	/* src */ PIO_PIN,	/* index */ 1,	/* rel */ false,	0x06, 0);
	pio_wait(/* polarity */ true,	/* src */ PIO_PIN,	/* index */ 1,	/* rel */ false,	0x07, 0);		// wait pin1

	pio_wrap();

	//<---- actual code
	pio_code_end(true, "pio0_sm1.pio");

	///////////////////////////////////////////////////////////////
	// emulation
	///////////////////////////////////////////////////////////////
	pio_run_emulation(
		200,			// int  cycles
		"in2.csv",		// char *file_name_in
		"out2.csv"		// char *file_name_out
	);

}
// end of file

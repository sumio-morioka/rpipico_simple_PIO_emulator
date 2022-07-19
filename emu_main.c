/////////////////////////////////////////////////////////////////////////////////////////
// RPi Pico PIO emulator for C
// Copyright(c) Sumio Morioka (Facebook: sumio.morioka)
// 
// sample
//
// (1) Original coding by Sumio Morioka									2022.07.18
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
		"pio0_sm0",		// char *funcname
		0,				// int	sm_id

		PIO_UNUSE,		// int in_pins
		PIO_UNUSE,		// int in_num
		PIO_UNUSE,		// int out_pins
		PIO_UNUSE,		// int out_num
		0,				// int sideset_pins
		3,				// int sideset_num
		false			// bool sidest_opt
	);

	//----> actual code

	pio_wrap_target();
		// sideset	delay
	pio_nop(0x01,	0);
	pio_nop(0x02,	1);
	pio_nop(0x04,	2);

	pio_wrap();

	//<---- actual code
	pio_code_end(true, "pio0_sm0.pio");

	///////////////////////////////////////////////////////////////
	// emulation
	///////////////////////////////////////////////////////////////
	pio_run_emulation(
		30,				// int  cycles
		"in.csv",		// char *file_name_in
		"out.csv"		// char *file_name_out
	);

}
// end of file

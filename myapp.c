#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "pio0_sm0.pio.h"		// pio0_sm0.pio: PIO ASM src name

int	main()
{
	uint	data;

//	setup_default_uart();
	stdio_init_all();
	sleep_ms(3000);		// wait serial connection

	// setup state machines
	pio0_sm0_config(
		pio0,
		0,			// state machine

//		1.0			// 125MHz
//		1.25		// 100MHz
//		12.50		// 10M
		125.0		// 1M
//		1250.0		// 100KHz
//		12500.0		// 10KHz
					// (min 1.9kHz)
	);

	// start state machines
	pio_sm_set_enabled(pio0, 0, true);	// PIO pio, uint sm, bool enabled

	// main
	while (1) {
		;
	}
}
// end of file

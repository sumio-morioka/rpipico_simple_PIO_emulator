#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "pio0_sm0.pio.h"		// pio0_sm0.pio: PIO ASM src name
#include "pio0_sm1.pio.h"		// pio0_sm1.pio: PIO ASM src name

////////////////////////////////////////////////
// interrupt handler
////////////////////////////////////////////////

//#define	USE_IRQ0
#undef		USE_IRQ0

volatile bool	irq_set;

static void irq_handler()
{
#ifdef	USE_IRQ0
	pio_interrupt_clear(pio0, 0);
	irq_clear(PIO0_IRQ_0);
#else
	pio_interrupt_clear(pio0, 1);
	irq_clear(PIO0_IRQ_1);
#endif

	irq_set	= true;
}


////////////////////////////////////////////////
// main
////////////////////////////////////////////////
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
		125.0		// 1M
					// (min 1.9kHz)
	);

	pio0_sm1_config(
		pio0,
		1,			// state machine
		12500.0		// 10KHz
					// (min 1.9kHz)
	);

	// configure interrupt
#ifdef	USE_IRQ0
	irq_set_exclusive_handler(PIO0_IRQ_0, irq_handler);
	irq_set_enabled(PIO0_IRQ_0, true);
	pio_set_irq0_source_enabled(pio0, pis_interrupt0, true);
#else
	irq_set_exclusive_handler(PIO0_IRQ_1, irq_handler);
	irq_set_enabled(PIO0_IRQ_1, true);
	pio_set_irq1_source_enabled(pio0, pis_interrupt1, true);
#endif
	irq_set	= false;

	// start state machines
	pio_sm_set_enabled(pio0, 0, true);	// PIO pio, uint sm, bool enabled
	pio_sm_set_enabled(pio0, 1, true);	// PIO pio, uint sm, bool enabled

	// main
	printf("init done\n");
	while (1) {
		printf("main loop\n");

		// put data to tx fifo
		pio_sm_put_blocking(pio0, 1, 0x00008001);
		printf("\tTX_0\n");
		pio_sm_put_blocking(pio0, 1, 0x00008002);
		printf("\tTX_1\n");
		pio_sm_put_blocking(pio0, 1, 0x00008003);
		printf("\tTX_2\n");
		pio_sm_put_blocking(pio0, 1, 0x00008004);
		printf("\tTX_3\n");

		// (wait GPIO16 goes to high)
		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_0 (0xFFFF7FFE): %08x\n", data);

		pio_sm_put_blocking(pio0, 1, 0x00008005);
		printf("\tTX_4\n");

		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_1 (0xFFFF7FFD): %08x\n", data);
		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_2 (0xFFFF7FFC): %08x\n", data);
		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_3 (0xFFFF7FFB): %08x\n", data);
		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_4 (0xFFFF7FFA): %08x\n", data);
		data	= pio_sm_get_blocking(pio0, 1);
		printf("\tRX_Y (0xFFFFFFFF): %08x\n", data);

		// wait interrupt from PIO
		while (irq_set == false)
			;

		printf("received irq\n");
		irq_set	= false;

		// (wait GPIO17 goes to high)
	}
}
// end of file

/////////////////////////////////////////////////////////////////////////////////////////
// RPi Pico PIO emulator for C
// Copyright(c) Sumio Morioka (Facebook: sumio.morioka)
// 
// (1) Original coding by Sumio Morioka									2022.07.18
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef PICOPIO_EMU
#define PICOPIO_EMU

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

////////////////////////////
// emulator API
////////////////////////////
extern void pio_code_start(
	char	*funcname, 
	int		sm_id,					// state machine ID (for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt, 

	bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
	bool	isr_autopush,
	int		isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
	bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
	bool	osr_autopull,
	int		osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
	int		jmp_pin,				// EXECCTRL_JMP_PIN
	bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
	int		mov_status_val			// EXECCTRL_STATUS_SEL
);

extern void pio_code_start_simple(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt
);

extern void pio_code_end(bool write_code, char *file_name_code);

extern void pio_run_emulation(int cycles, char *file_name_in, char *file_name_out);

////////////////////////////
// instructions
////////////////////////////
extern void pio_jmp(int cond, char *lbl, int sideset, int delay);
extern void pio_wait(bool polarity, int src, int index, bool rel, int sideset, int delay);
extern void pio_in(int src, int bitcount, int sideset, int delay);
extern void pio_out(int dest, int bitcount, int sideset, int delay);
extern void pio_push(bool iffull, bool block, int sideset, int delay);
extern void pio_pull(bool ifempty, bool block, int sideset, int delay);
extern void pio_mov(int dest, int op, int src, int sideset, int delay);
extern void pio_irq(bool clr, bool wait, int index, bool rel, int sideset, int delay);
extern void pio_set(int dest, int data, int sideset, int delay);

// (pseudo instructions)
extern void pio_comment(char *string);		// max len = MAX_COMMENT_LEN
extern void pio_label(char *lbl);
extern void pio_nop(int sideset, int delay);
extern void pio_wrap_target(void);
extern void pio_wrap(void);
extern void pio_origin(int addr);

////////////////////////////
// constants
////////////////////////////

#define	PIO_UNUSE				-1

// instructions
#define	PIO_INST_IN				0
#define	PIO_INST_IRQ			1
#define	PIO_INST_JMP			2
#define	PIO_INST_MOV			3
#define	PIO_INST_OUT			4
#define	PIO_INST_PULL			5
#define	PIO_INST_PUSH			6
#define	PIO_INST_SET			7
#define	PIO_INST_WAIT			8

#define	PIO_INST_COMMENT		9
#define	PIO_INST_LABEL			10
#define	PIO_INST_NOP			11
#define	PIO_INST_WRAP_TARGET	12
#define	PIO_INST_WRAP			13
#define	PIO_INST_ORIGIN			14

// operands (in, out, mov)
#define	PIO_PINS				100
#define	PIO_X					101
#define	PIO_Y					102
#define	PIO_NULL				103
#define	PIO_ISR					104
#define	PIO_OSR					105
#define	PIO_PC					106
#define	PIO_EXEC				107
#define	PIO_PINDIRS				108
#define	PIO_STATUS				109

#define	PIO_NONE				200
#define	PIO_INVERT				201
#define	PIO_BIT_REVERSE			202

// operands (jmp)
#define	PIO_ALWAYS				300
#define	PIO_X_EQ_0				301
#define	PIO_X_NEQ_0_DEC			302
#define	PIO_Y_EQ_0				303
#define	PIO_Y_NEQ_0_DEC			304
#define	PIO_X_NEQ_Y				305
#define	PIO_PIN					306
#define	PIO_OSRE_NOTEMPTY		307

// operands (wait)
#define	PIO_GPIO				400
//#define	PIO_PIN				401		// defined above
#define	PIO_IRQ					402

// oprands (push, pull)
#define	PIO_BLOCK				500
#define	PIO_NOBLOCK				501


////////////////////////////
// other parameters
////////////////////////////
#define	PIO_MAX_FUNCNAME_LEN	256

#define	PIO_MAX_ASMLINE_LEN		1024
#define	PIO_MAX_ASMLINE_NUM		1024
#define	PIO_MAX_CSVLINE_LEN		1024

#define	PIO_MAX_INST_NUM		32		// don't change


/////////////////////////////////////////////////////////////////////////////////////////
// type definitions & global variables
/////////////////////////////////////////////////////////////////////////////////////////

typedef struct _pio_inst_list {
	bool		used;
	int			code_line;
	uint8_t		addr;			// 0-31

	int			inst_type;
	int			operand1;
	int			operand2;
	int			operand3;
	int			operand4;
	int			operand5;
	int			sideset;
	int			delay;

	char		strbuf[PIO_MAX_ASMLINE_LEN + 1];	// label or comment
	char		asmbuf[PIO_MAX_ASMLINE_LEN + 1];	// assembler output
} _PIO_INST;


typedef struct _pio_csvin_info {
	int			cycles;
	uint32_t	gpio_i;
	uint8_t		irq_i;
	bool		txfifo_push;
	uint32_t	txfifo_val;
	bool		rxfifo_pop;
} _PIO_CSVIN;


typedef struct _pio_global_info {
	// func name
	char		func_name[PIO_MAX_FUNCNAME_LEN];
	int			sm_id;

	// instruction
	_PIO_INST	asmline[PIO_MAX_ASMLINE_NUM];
	int			asmline_ptr;

	int			origin;
	int			inst_ptr;

	// CPU registers
	int			delay_timer;
	uint32_t	x;
	uint32_t	y;

	uint32_t	isr;
	int			isr_bitctr;
	uint32_t	osr;
	int			osr_bitctr;

	uint32_t	txfifo[4];
	int			txfifo_num;

	uint32_t	rxfifo[4];
	int			rxfifo_num;

	uint32_t	gpio_i;
	uint32_t	gpio_o;
	uint32_t	sideset_val;

	uint8_t		irq_i;
	uint8_t		irq_o;
	bool		irq_stalling;

	// emulator info (configuration values)
	// CPU I/O
	int			cycles;

	int			in_pins;
	int			in_num;
	int			out_pins;
	int			out_num;
	int			sideset_pins;
	int			sideset_num;
	bool		sideset_opt;
	int			sideset_maxval;
	int			delay_maxval;

	uint32_t	in_pin_setmask;
	uint32_t	out_pin_setmask;
	uint32_t	sideset_pin_setmask;
	uint32_t	jmp_pin_setmask;

	uint32_t	in_pin_clrmask;
	uint32_t	out_pin_clrmask;
	uint32_t	sideset_pin_clrmask;

	bool		isr_shift_right;
	bool		isr_autopush;
	int			isr_autopush_threshold;
	bool		osr_shift_right;
	bool		osr_autopull;
	int			osr_autopull_threshold;
	int			jmp_pin;
	bool		mov_status_sel;
	int			mov_status_val;

	int			wrap_target_line;
	int			wrap_line;

	FILE		*fin;
	FILE		*fout;
	FILE		*fcode;

	char		csvin_cache[PIO_MAX_CSVLINE_LEN];
	bool		csvin_cache_valid;
	_PIO_CSVIN	csvin_info;
} _PIO_INFO;


// global
static _PIO_INFO		_pio_info_g;

#define	PIO_SIMSTATE_CODE_START		0
#define	PIO_SIMSTATE_CODE_END		1
#define	PIO_SIMSTATE_RUN_START		2
#define	PIO_SIMSTATE_RUN_END		3

static int			_pio_emu_state_g	= PIO_SIMSTATE_CODE_START;

/////////////////////////////////////////////////////////////////////////////////////////
// function body
/////////////////////////////////////////////////////////////////////////////////////////

static uint32_t pio_maxval(unsigned int bitnum)
{
	// return (2^bitnum)-1
	uint32_t		mask;
	unsigned int	i;
	for (i = 0, mask = 0; i <= 32; i++) {
		if (i == bitnum)
			return mask;
		mask	= (mask << 1) | 1;
	}
	return	mask;
}


static unsigned int pio_bitnum(uint32_t val)
{
	uint32_t		mask;
	unsigned int	i;
	for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
		if (val < mask)
			return i;
	}
	return 32;
}


static uint32_t _pio_bitreverse(uint32_t val)
{
	uint32_t		ret;
	unsigned int	i;
	for (i = 0, ret = 0; i < 32; i++) {
		ret	<<= 1;
		if ((val & 1) != 0) {
			ret	|= 1;
		}
		val	>>= 1;
	}
	return ret;
}


void pio_code_start(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt, 

	bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
	bool	isr_autopush,
	int		isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
	bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
	bool	osr_autopull,
	int		osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
	int		jmp_pin,				// EXECCTRL_JMP_PIN
	bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
	int		mov_status_val			// EXECCTRL_STATUS_SEL
)
{
	int	i;
	int delay_bitnum;

	if (_pio_emu_state_g != PIO_SIMSTATE_CODE_START) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal code-start position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_CODE_END;

	// initialize global info
	strcpy(_pio_info_g.func_name, funcname);			// NOTE: init value

	// state machine ID (for IRQ rel)
	if (sm_id < 0 || sm_id > 3) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal state machine id (0-3).\n");
		exit(1);
	}
	_pio_info_g.sm_id	= sm_id;

	// init internal info
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*p;
		p						= &(_pio_info_g.asmline[i]);
		p->used					= false;
		p->code_line			= 0;
		p->addr					= 0;
		p->inst_type			= PIO_UNUSE;
		p->operand1				= PIO_UNUSE;
		p->operand2				= PIO_UNUSE;
		p->operand3				= PIO_UNUSE;
		p->operand4				= PIO_UNUSE;
		p->operand5				= PIO_UNUSE;
		p->sideset				= PIO_UNUSE;
		p->delay				= PIO_UNUSE;
		(p->strbuf)[0]			= '\0';
		(p->asmbuf)[0]			= '\0';
	}
	_pio_info_g.asmline_ptr		= 0;

	_pio_info_g.origin			= PIO_UNUSE;
	_pio_info_g.inst_ptr		= 0;

	_pio_info_g.delay_timer		= PIO_UNUSE;
	_pio_info_g.x				= 0;
	_pio_info_g.y				= 0;

	_pio_info_g.isr				= 0;
	_pio_info_g.osr				= 0;

	for (i = 0; i < 4; i++) {
		(_pio_info_g.txfifo)[i]	= 0;
	}
	_pio_info_g.txfifo_num		= 0;
	for (i = 0; i < 4; i++) {
		(_pio_info_g.rxfifo)[i]	= 0;
	}
	_pio_info_g.rxfifo_num		= 0;

	_pio_info_g.in_pins			= in_pins;			// NOTE: init value
	_pio_info_g.in_num			= in_num;			// NOTE: init value
	_pio_info_g.out_pins		= out_pins;			// NOTE: init value
	_pio_info_g.out_num			= out_num;			// NOTE: init value
	_pio_info_g.sideset_pins	= sideset_pins;		// NOTE: init value
	_pio_info_g.sideset_num		= sideset_num;		// NOTE: init value
	_pio_info_g.sideset_opt		= sideset_opt;		// NOTE: init value

	{
		if (in_pins == PIO_UNUSE || in_num == PIO_UNUSE) {
			in_pins			= 0;
			in_num			= 0;
		}
		if (out_pins == PIO_UNUSE || out_num == PIO_UNUSE) {
			out_pins		= 0;
			out_num			= 0;
		}
		if (sideset_pins == PIO_UNUSE || sideset_num == PIO_UNUSE) {
			sideset_pins	= 0;
			sideset_num		= 0;
		}

		// check pin assign
		if (in_pins < 0 || in_num < 0 || (in_pins + in_num) > 29) {		// 29 ... GPIO 0-28
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of input pins.\n");
			exit(1);
		}
		if (out_pins < 0 || out_num < 0 || (out_pins + out_num) > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of output pins.\n");
			exit(1);
		}
		if (sideset_pins < 0 || sideset_num < 0 || (sideset_pins + sideset_num) > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of sideset pins.\n");
			exit(1);
		}

		_pio_info_g.in_pin_setmask		= (pio_maxval(in_num)      << in_pins)      & 0x1FFFFFFF;	// 0x1FFFFFFF ... GPIO28-0
		_pio_info_g.out_pin_setmask		= (pio_maxval(out_num)     << out_pins)     & 0x1FFFFFFF;
		_pio_info_g.sideset_pin_setmask	= (pio_maxval(sideset_num) << sideset_pins) & 0x1FFFFFFF;

		_pio_info_g.in_pin_clrmask		= 0xFFFFFFFF ^ _pio_info_g.in_pin_setmask;					// (inversion)
		_pio_info_g.out_pin_clrmask		= 0xFFFFFFFF ^ _pio_info_g.out_pin_setmask;
		_pio_info_g.sideset_pin_clrmask	= 0xFFFFFFFF ^ _pio_info_g.sideset_pin_setmask;

//fprintf(stderr, "in mask   %08x\n", _pio_info_g.in_pin_setmask);
//fprintf(stderr, "out mask  %08x\n", _pio_info_g.out_pin_setmask);
//fprintf(stderr, "side mask %08x\n", _pio_info_g.sideset_pin_setmask);

		if ((_pio_info_g.in_pin_setmask & _pio_info_g.out_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between input and output.\n");
			exit(1);
		}
		if ((_pio_info_g.in_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between input and sideset.\n");
			exit(1);
		}
		if ((_pio_info_g.out_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between output and sideet.\n");
			exit(1);
		}
	}

	_pio_info_g.gpio_i			= 0;
	_pio_info_g.gpio_o			= 0;
	_pio_info_g.sideset_val		= 0;

	_pio_info_g.irq_i			= 0;
	_pio_info_g.irq_o			= 0;
	_pio_info_g.irq_stalling	= false;

	_pio_info_g.cycles			= 1;
	_pio_info_g.isr_shift_right	= isr_shift_right;	// NOTE: default value
	_pio_info_g.osr_shift_right	= osr_shift_right;	// NOTE: default value

	if (isr_autopush_threshold < 0 || isr_autopush_threshold > 32) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal isr_autopush_threshold value.\n");
		exit(1);
	}
	if (osr_autopull_threshold < 0 || osr_autopull_threshold > 32) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal osr_autopull_threshold value.\n");
		exit(1);
	}
	_pio_info_g.isr_autopush			= isr_autopush;
	_pio_info_g.isr_autopush_threshold	= isr_autopush_threshold;	// NOTE: default value
	_pio_info_g.osr_autopull			= osr_autopull;
	_pio_info_g.osr_autopull_threshold	= osr_autopull_threshold;	// NOTE: default value

	_pio_info_g.isr_bitctr		= 0;		// empty
	_pio_info_g.osr_bitctr		= _pio_info_g.osr_autopull_threshold;	// (empty)


	{	// check # of sideset num
		if (sideset_num > 5 || (sideset_opt == true && sideset_num > 4)) {
			fprintf(stderr, "pio_code_start(): ERROR. Too many number of sideset signals.\n");
			exit(1);
		}

		if (sideset_opt == false) {
			delay_bitnum	= 5 - sideset_num;
		}
		else {
			delay_bitnum	= 4 - sideset_num;
		}

		_pio_info_g.sideset_maxval	= pio_maxval(sideset_num);

		if (delay_bitnum >= 1)
			_pio_info_g.delay_maxval	= pio_maxval(delay_bitnum);
		else
			_pio_info_g.delay_maxval	= 0;
	}

	_pio_info_g.jmp_pin		= jmp_pin;
	if (jmp_pin != PIO_UNUSE) {	// check jmp pin
		if (jmp_pin < 0 || jmp_pin > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal jmp_pin assignment.\n");
			exit(1);
		}

		_pio_info_g.jmp_pin_setmask	= ((uint32_t)1 << jmp_pin) & 0x1FFFFFFF;	// GPIO28-0

		if ((_pio_info_g.jmp_pin_setmask & _pio_info_g.out_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Jmp_pin is assigned to an output port.\n");
			exit(1);
		}
		if ((_pio_info_g.jmp_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Jmp_pin is assigned to a sideset port.\n");
			exit(1);
		}
	}

	_pio_info_g.mov_status_sel		= mov_status_sel;	// true:TX, false:RX
	if (mov_status_val < 1 || mov_status_val > 4) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal mov_status_val (1-4).\n");
		exit(1);
	}
	_pio_info_g.mov_status_val		= mov_status_val;

	_pio_info_g.wrap_target_line	= PIO_UNUSE;
	_pio_info_g.wrap_line			= PIO_UNUSE;

	_pio_info_g.fin					= (FILE *)NULL;
	_pio_info_g.fout				= (FILE *)NULL;
	_pio_info_g.fcode				= (FILE *)NULL;

	_pio_info_g.csvin_cache[0]		= '\0';
	_pio_info_g.csvin_cache_valid	= false;
	{
		_PIO_CSVIN	*p;
		p				= &(_pio_info_g.csvin_info);
		p->cycles		= PIO_UNUSE;
		p->gpio_i		= 0;
		p->txfifo_push	= false;
		p->txfifo_val	= 0;
		p->rxfifo_pop	= false;
	}
}


void pio_code_start_simple(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)
	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt
)
{
	pio_code_start(
		funcname, 
		sm_id,

		in_pins, 
		in_num, 
		out_pins, 
		out_num, 
		sideset_pins, 
		sideset_num, 
		sideset_opt, 

		false,			// bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
		false,			// bool	isr_autopush,
		32,				// int	isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
		true,			// bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
		false,			// bool	osr_autopull,
		32,				// int	osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
		PIO_UNUSE,		// int	jmp_pin,				// EXECCTRL_JMP_PIN
		true,			// bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
		4				// int	mov_status_val			// EXECCTRL_STATUS_SEL
	);
}


static bool pio_get_asmline_pc(int *asmline, int pc)
{
	int	i;
	*asmline	= PIO_UNUSE;
	pc			&= 31;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return false;
		if (inst->addr == pc) {
			*asmline	= inst->code_line;	// IMPORTANT: return assember line
			return true;
		}
	}
	return false;
}


static bool pio_get_label_address(int *asmline, char *lbl)
{
	int	i;
	*asmline	= PIO_UNUSE;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return false;
		if (inst->inst_type != PIO_INST_LABEL)
			continue;
		if (!strcmp(lbl, inst->strbuf)) {
//			*asmline	= inst->addr;		// BUG
			*asmline	= inst->code_line;	// IMPORTANT: return assember line
			return true;
		}
	}
	return false;
}


static void pio_resolve_label_address(void)
{
	int		i, asmline;
//	char	tmpbuf[PIO_MAX_ASMLINE_LEN + 1];

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return;
		if (inst->inst_type != PIO_INST_JMP)
			continue;
		if (pio_get_label_address(&asmline, inst->strbuf) == false) {
			fprintf(stderr, "pio_resolve_label_address(): ERROR. Undefined label \"%s\" in step %d (\"%s\").\n", inst->strbuf, inst->code_line, inst->asmbuf);
			exit(1);
		}
		else {
			inst->operand2	= asmline;		// IMPORTANT: assembler line
//fprintf(stderr, "resolve_label step %d jmp to step %d\n", inst->code_line, asmline);
// for debug
//			sprintf(tmpbuf, "\t; to addr 0x%02x", addr);
//			strcat(inst->asmbuf, tmpbuf);
		}
	}
}


static void pio_write_assembler_code(char *file_name_code)
{
	int		i;
	FILE	*fp;

	if ((_pio_info_g.fcode = fopen(file_name_code, "wt")) == (FILE *)NULL) {
		fprintf(stderr, "pio_write_assembler_code(): ERROR. Cannot create output ASM file \"%s\".\n", file_name_code);
		exit(1);
	}
	fp	= _pio_info_g.fcode;

	fprintf(fp, "; automatically generated by picopio_emu\n");
	fprintf(fp, "\n");

	// write header
	fprintf(fp, ".program %s\n", _pio_info_g.func_name);

	if (_pio_info_g.sideset_num > 0) {
		fprintf(fp, ".side_set %d", _pio_info_g.sideset_num);
		if (_pio_info_g.sideset_opt == true) {
			fprintf(fp, " opt");
		}
		fprintf(fp, "\n\n");
	}

	// write each instruction
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			break;

		// write code
#ifdef DISP_ASM_STDOUT
		fprintf(stdout, "%03d (pc=0x%02x):\t", inst->code_line, inst->addr);
#endif
		if (inst->inst_type != PIO_INST_COMMENT
					&& inst->inst_type != PIO_INST_LABEL
					&& inst->inst_type != PIO_INST_WRAP_TARGET
					&& inst->inst_type != PIO_INST_WRAP
					&& inst->inst_type != PIO_INST_ORIGIN) {
			fprintf(fp,     "\t");
#ifdef DISP_ASM_STDOUT
			fprintf(stdout, "\t");
#endif
		}
		fprintf(fp,     "%s\t; line %03d\n", inst->asmbuf, inst->code_line);
#ifdef DISP_ASM_STDOUT
		fprintf(stdout, "%s\n", inst->asmbuf);
#endif
	}

	// write C interface
	fprintf(fp, "\n");
	fprintf(fp, "%% c-sdk {\n");
	fprintf(fp, "// see also (api):   https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__pio.html\n");
	fprintf(fp, "// see also (pio.h): https://raspberrypi.github.io/pico-sdk-doxygen/rp2__common_2hardware__pio_2include_2hardware_2pio_8h_source.html\n");
	fprintf(fp, "// see also (sm):    https://raspberrypi.github.io/pico-sdk-doxygen/group__sm__config.html\n");
	fprintf(fp, "\n");

	fprintf(fp, "void %s_config(\n", _pio_info_g.func_name);
	fprintf(fp, "	PIO		pio,\n");
	fprintf(fp, "	uint	sm,\n");
	fprintf(fp, "	float	clkdiv\n");
	fprintf(fp, ")\n");
	fprintf(fp, "{\n");
	fprintf(fp, "	int		i;\n");
	fprintf(fp, "	uint	prog_addr;\n");
	fprintf(fp, "\n");

	fprintf(fp, "	if (clkdiv < 1.0) {\n");
	fprintf(fp, "		printf(\"asm_exec(): too small clkdiv\\n\");\n");
	fprintf(fp, "		return;\n");
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// load program to PIO\n");
	fprintf(fp, "	prog_addr			= pio_add_program(pio, &%s_program);\n", _pio_info_g.func_name);
	fprintf(fp, "	pio_sm_config	c	= %s_program_get_default_config(prog_addr);	// addr\n", _pio_info_g.func_name);
	fprintf(fp, "	sm_config_set_clkdiv(&c, clkdiv);	// pio_sm_config *c, float div\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// input\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.in_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.in_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.in_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, false);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.in_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, false);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.in_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		sm_config_set_in_pins(&c, %d);	// pio_sm_config *c, uint in_base\n", _pio_info_g.in_pins);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// sideset\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.sideset_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.sideset_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.sideset_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.sideset_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sideset_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		sm_config_set_sideset_pins(&c, %d);	// pio_sm_config *c, uint sideset_base\n", _pio_info_g.sideset_pins);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// output\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.out_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.out_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.out_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.out_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.out_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		if (%d <= 5)", _pio_info_g.out_num);
	fprintf(fp, "			sm_config_set_set_pins(&c, %d, %d);	// pio_sm_config *c, uint set_base, uint set_count\n", _pio_info_g.out_pins, _pio_info_g.out_num);
	fprintf(fp, "		else\n");
	fprintf(fp, "			sm_config_set_set_pins(&c, %d, 5);	// pio_sm_config *c, uint set_base, uint set_count\n", _pio_info_g.out_pins);
	fprintf(fp, "		sm_config_set_out_pins(&c, %d, %d);	// pio_sm_config *c, uint out_base, uint out_count\n", _pio_info_g.out_pins, _pio_info_g.out_num);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// fifo, isr and osr\n");
//	fprintf(fp, "	sm_config_set_in_shift(&c, false, false, 32);		// shift right, auto-push, threshold\n");
	fprintf(fp, "	sm_config_set_in_shift(&c, ");
	if (_pio_info_g.isr_shift_right == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	if (_pio_info_g.isr_autopush == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	fprintf(fp, "%d);		// pio_sm_config *c, bool shift_right, bool autopush, uint push_threshold\n", _pio_info_g.isr_autopush_threshold);

	fprintf(fp, "	sm_config_set_out_shift(&c, ");
	if (_pio_info_g.osr_shift_right == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	if (_pio_info_g.osr_autopull == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	fprintf(fp, "%d);		// pio_sm_config *c, bool shift_right, bool autopull, uint pull_threshold\n", _pio_info_g.osr_autopull_threshold);
	fprintf(fp, "\n");

	if (_pio_info_g.jmp_pin != PIO_UNUSE) {
		fprintf(fp, "	// \"jmp pin\" instruction\n");
		fprintf(fp, "	sm_config_set_jmp_pin(&c, %d);	// pio_sm_config *c, uint pin\n", _pio_info_g.jmp_pin);
		fprintf(fp, "\n");
	}

	fprintf(fp, "	// \"move status\" instruction\n");
 	fprintf(fp, "	sm_config_set_mov_status(&c, ");
	if (_pio_info_g.mov_status_sel == true)
		fprintf(fp, "STATUS_TX_LESSTHAN, ");
	else
		fprintf(fp, "STATUS_RX_LESSTHAN, ");
	fprintf(fp, "%d);	// pio_sm_config *c, enum pio_mov_status_type status_sel, uint status_n\n", _pio_info_g.mov_status_val);
	fprintf(fp, "\n");

//	fprintf(fp, "	pio_sm_clear_fifos(pio, %d);	// PIO pio, uint sm\n", _pio_info_g.sm_id);
	fprintf(fp, "	pio_sm_clear_fifos(pio, sm);	// PIO pio, uint sm\n");
//	fprintf(fp, "	pio_sm_init(pio, %d, prog_addr, &c);	// PIO pio, uint sm, uint initial_pc, const pio_sm_config *config\n", _pio_info_g.sm_id);
	fprintf(fp, "	pio_sm_init(pio, sm, prog_addr, &c);	// PIO pio, uint sm, uint initial_pc, const pio_sm_config *config\n");
//	fprintf(fp, "	pio_sm_set_enabled(pio, sm, true);	// PIO pio, uint sm, bool enabled\n");
	fprintf(fp, "}\n");

	fprintf(fp, "%%}\n");

	fclose(_pio_info_g.fcode);
}


void pio_code_end(bool write_code, char *file_name_code)
{
	if (_pio_emu_state_g != PIO_SIMSTATE_CODE_END) {
		fprintf(stderr, "pio_code_end(): ERROR. Illegal code-end position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_RUN_START;

	pio_resolve_label_address();
	if (write_code == true) {
		pio_write_assembler_code(file_name_code);		// create output asm
	}
}


static int pio_search_wrap_target(void)
{
	int	i;
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*ap;
		ap	= &(_pio_info_g.asmline[i]);
		if (ap->used == false)
			break;
		if (ap->inst_type == PIO_INST_WRAP_TARGET)
			return i;
	}
	return 0;	// not found: return to top of the list
}


static void pio_read_csv_input_header(void)
{
	FILE		*fp;
	if ((fp = _pio_info_g.fin) == (FILE *)NULL)
		return;
	if (feof(fp))
		return;

	// cut 1st line of the csv
	fgets(_pio_info_g.csvin_cache, PIO_MAX_CSVLINE_LEN - 1, fp);
	_pio_info_g.csvin_cache_valid = false;
}


static void pio_shift_txfifo(void)
{
	int	i;
	for (i = 0; i < 3; i++) {
		_pio_info_g.txfifo[i]	= _pio_info_g.txfifo[i + 1];
	}
	_pio_info_g.txfifo[3]	= 0;
}


static void pio_shift_rxfifo(void)
{
	int	i;
	for (i = 0; i < 3; i++) {
		_pio_info_g.rxfifo[i]	= _pio_info_g.rxfifo[i + 1];
	}
	_pio_info_g.rxfifo[3]	= 0;
}


static bool pio_push_txfifo(uint32_t val)
{
	switch (_pio_info_g.txfifo_num) {
	case 0:
		_pio_info_g.txfifo[0]	= val;
		_pio_info_g.txfifo_num	= 1;
		return true;
	case 1:
		_pio_info_g.txfifo[1]	= val;
		_pio_info_g.txfifo_num	= 2;
		return true;
	case 2:
		_pio_info_g.txfifo[2]	= val;
		_pio_info_g.txfifo_num	= 3;
		return true;
	case 3:
		_pio_info_g.txfifo[3]	= val;
		_pio_info_g.txfifo_num	= 4;
		return true;
	default:
		break;
	}
	return false;
}


static bool pio_pop_txfifo(uint32_t *val)
{
	switch (_pio_info_g.txfifo_num) {
	case 4:
	case 3:
	case 2:
	case 1:
		*val	= _pio_info_g.txfifo[0];
		(_pio_info_g.txfifo_num)--;
		pio_shift_txfifo();
		return true;
	default:
		break;
	}
	*val	= 0;
	return false;
}


static bool pio_push_rxfifo(uint32_t val)
{
	switch (_pio_info_g.rxfifo_num) {
	case 0:
		_pio_info_g.rxfifo[0]	= val;
		_pio_info_g.rxfifo_num	= 1;
		return true;
	case 1:
		_pio_info_g.rxfifo[1]	= val;
		_pio_info_g.rxfifo_num	= 2;
		return true;
	case 2:
		_pio_info_g.rxfifo[2]	= val;
		_pio_info_g.rxfifo_num	= 3;
		return true;
	case 3:
		_pio_info_g.rxfifo[3]	= val;
		_pio_info_g.rxfifo_num	= 4;
		return true;
	default:
		break;
	}
	return false;
}


static bool pio_pop_rxfifo(uint32_t *val)
{
	switch (_pio_info_g.rxfifo_num) {
	case 4:
	case 3:
	case 2:
	case 1:
		*val	= _pio_info_g.rxfifo[0];
		(_pio_info_g.rxfifo_num)--;
		pio_shift_rxfifo();
		return true;
	default:
		break;
	}
	*val	= 0;
	return false;
}


static void pio_copy_csvin_to_input(void)
{
	uint32_t	tmp;

	// GPIO
	_pio_info_g.gpio_i	= (_pio_info_g.csvin_info.gpio_i) & _pio_info_g.in_pin_setmask;		// IMPORTANT: apply mask
	_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.in_pin_clrmask)
							| _pio_info_g.gpio_i;											// IMPORTANT: copy input value to output

	// IRQ ACK
	_pio_info_g.irq_i	= _pio_info_g.csvin_info.irq_i;

	// TX fifo
	if (_pio_info_g.csvin_info.txfifo_push == true) {
		if (pio_push_txfifo(_pio_info_g.csvin_info.txfifo_val) == false) {
			fprintf(stderr, "pio_copy_csvinfo_to_input(): WARNING. Cannot push data to tx-fifo (in cycle %d).\n", _pio_info_g.cycles);
		}
	}

	// RX fifo
	if (_pio_info_g.csvin_info.rxfifo_pop == true) {
		if (pio_pop_rxfifo(&tmp) == false) {
			fprintf(stderr, "pio_copy_csvinfo_to_input(): WARNING. Cannot pop data from rx-fifo (in cycle %d).\n", _pio_info_g.cycles);
		}
	}
}


static void pio_read_csv_input(void)
{
	FILE		*fp;
	if ((fp = _pio_info_g.fin) == (FILE *)NULL)
		return;
	if (feof(fp))
		return;

	// - read csv until exec cycle >= csv cycle
	// - update input value if exec cycle == csv cycle
	// - csv format: "cycle, gpio_i, irq_i, tx_push(0/1), tx_val, rx_pop(0/1)\n"
	while (1) {
		if (_pio_info_g.csvin_cache_valid == false) {
			int	b0, b1, i0;
#ifdef	PIO_IN_GPIO_BIT_BY_BIT
			int	gp[29];	// 29 ... GPIO 0-28
#endif

			// read line
			if (fgets(_pio_info_g.csvin_cache, PIO_MAX_CSVLINE_LEN - 1, fp) == NULL)
				return;

			// scan line
#ifdef	PIO_IN_GPIO_BIT_BY_BIT
			sscanf(_pio_info_g.csvin_cache, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%x, %d\n",
						&(_pio_info_g.csvin_info.cycles),
						&(gp[0]), &(gp[1]), &(gp[2]), &(gp[3]), &(gp[4]), &(gp[5]), &(gp[6]), &(gp[7]), &(gp[8]), &(gp[9]),
						&(gp[10]), &(gp[11]), &(gp[12]), &(gp[13]), &(gp[14]), &(gp[15]), &(gp[16]), &(gp[17]), &(gp[18]), &(gp[19]),
						&(gp[20]), &(gp[21]), &(gp[22]), &(gp[23]), &(gp[24]), &(gp[25]), &(gp[26]), &(gp[27]), &(gp[28]),
						&i0,
						&b0,
						&(_pio_info_g.csvin_info.txfifo_val),
						&b1
					);
			{
				int			i;
				uint32_t	v;
				v	= 0;
				for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
					v	<<= 1;
					if (gp[28 - i] != 0) {
						v	|= 1;
					}
				}
				_pio_info_g.csvin_info.txfifo_val	= v;
			}
#else
			sscanf(_pio_info_g.csvin_cache, "%d, 0x%x, 0x%x, %d, 0x%x, %d\n",
						&(_pio_info_g.csvin_info.cycles),
						&(_pio_info_g.csvin_info.gpio_i),
						&i0,
						&b0,
						&(_pio_info_g.csvin_info.txfifo_val),
						&b1
					);
#endif
			_pio_info_g.csvin_info.irq_i	= (uint8_t)i0;

			if (b0 == 0)
				_pio_info_g.csvin_info.txfifo_push	= false;
			else
				_pio_info_g.csvin_info.txfifo_push	= true;
			if (b1 == 0)
				_pio_info_g.csvin_info.rxfifo_pop	= false;
			else
				_pio_info_g.csvin_info.rxfifo_pop	= true;
//fprintf(stderr, "%s", _pio_info_g.csvin_cache);
//fprintf(stderr, "cycle %d\n", _pio_info_g.csvin_info.cycles);
//fprintf(stderr, "gpio %08x\n", _pio_info_g.csvin_info.gpio_i);
//fprintf(stderr, "push %d\n", b0);
//fprintf(stderr, "pop %d\n", b1);
		}

		// update info
		if (_pio_info_g.cycles > _pio_info_g.csvin_info.cycles) {	// (past)
			pio_copy_csvin_to_input();
			_pio_info_g.csvin_cache_valid = false;
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tREAD CSV (cycle %d)\n", _pio_info_g.csvin_info.cycles);
#endif
		}
		else if (_pio_info_g.cycles == _pio_info_g.csvin_info.cycles) {	// (current)
			pio_copy_csvin_to_input();
			_pio_info_g.csvin_cache_valid = false;
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tREAD CSV (cycle %d)\n", _pio_info_g.csvin_info.cycles);
#endif
			return;
		}
		else {	// (future)
			// (nothing to do)
			_pio_info_g.csvin_cache_valid = true;
			return;
		}
	}	// while
}


static bool pio_is_assigned_pin(int num)
{
	uint32_t	pin;
	pin	= (uint32_t)1 << num;

	if ((_pio_info_g.in_pin_setmask & pin) != 0)
		return true;
	if ((_pio_info_g.out_pin_setmask & pin) != 0)
		return true;
	if ((_pio_info_g.sideset_pin_setmask & pin) != 0)
		return true;

	return false;
}


static void pio_write_csv_output_header(void)
{
	FILE		*fp;
	int			i;

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	fprintf(fp, "cycle, ");
	fprintf(fp, "line, ");
	fprintf(fp, "pc, ");
	fprintf(fp, "inst, ");

#ifdef	PIO_OUT_GPIO_BIT_BY_BIT
	for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
		if (pio_is_assigned_pin(i) == true) {
			fprintf(fp, "gpio_%d, ", i);
		}
	}
#else
	fprintf(fp, "gpio, ");
#endif

	fprintf(fp, "irq, ");
	fprintf(fp, "x, ");
	fprintf(fp, "y, ");
	fprintf(fp, "isr_bitctr, ");
	fprintf(fp, "isr, ");
	fprintf(fp, "osr_bitctr, ");
	fprintf(fp, "osr, ");
	fprintf(fp, "txfifo_num, ");
	fprintf(fp, "txfifo[0], ");
	fprintf(fp, "txfifo[1], ");
	fprintf(fp, "txfifo[2], ");
	fprintf(fp, "txfifo[3], ");
	fprintf(fp, "rxfifo_num, ");
	fprintf(fp, "rxfifo[0], ");
	fprintf(fp, "rxfifo[1], ");
	fprintf(fp, "rxfifo[2], ");
	fprintf(fp, "rxfifo[3]");
	fprintf(fp, "\n");
}

static void pio_write_csv_output_inst(void)
{
	_PIO_INST	*ap;
	FILE		*fp;
	char		tmpbuf[PIO_MAX_ASMLINE_NUM];

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);

	// - write csv output every cycle
	fprintf(fp, "%d, ", _pio_info_g.cycles);
	fprintf(fp, "%d, ", ap->code_line);
	fprintf(fp, "0x%02x, ", ap->addr);
	if (_pio_info_g.delay_timer > 0)
		fprintf(fp, "\"delay\", ");
	else {
		char	*p;
		strcpy(tmpbuf, ap->asmbuf);
		for (p = tmpbuf; *p != '\0'; p++) {
			if (*p == '\t')
				*p	= ' ';
			else if (*p == ',')
				*p	= ' ';
		}
		fprintf(fp, "\"%s\", ",tmpbuf);
	}
}


static void pio_write_csv_output_regs(void)
{
	_PIO_INST	*ap;
	FILE		*fp;
	uint32_t	val;
	int			i;

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);

	// - write csv output every cycle
#ifdef	PIO_OUT_GPIO_BIT_BY_BIT
	val	= _pio_info_g.gpio_o;
	for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
		if (pio_is_assigned_pin(i) == true) {
			if ((val & 1) != 0)
				fprintf(fp, "1, ");
			else
				fprintf(fp, "0, ");
		}
		val	>>=	1;
	}
#else
	fprintf(fp, "0x%08x, ", _pio_info_g.gpio_o);
#endif

	fprintf(fp, "0x%02x, ", _pio_info_g.irq_o);
	fprintf(fp, "0x%08x, ", _pio_info_g.x);
	fprintf(fp, "0x%08x, ", _pio_info_g.y);
	fprintf(fp, "%d, ",		_pio_info_g.isr_bitctr);
	fprintf(fp, "0x%08x, ", _pio_info_g.isr);
	fprintf(fp, "%d, ",		_pio_info_g.osr_bitctr);
	fprintf(fp, "0x%08x, ", _pio_info_g.osr);

	fprintf(fp, "%d, ", _pio_info_g.txfifo_num);
	for (i = 0; i < 4; i++) {
		fprintf(fp, "0x%08x, ", _pio_info_g.txfifo[i]);
	}
	fprintf(fp, "%d, ", _pio_info_g.rxfifo_num);
//	for (i = 0; i < 4; i++) {
	for (i = 0; i < 3; i++) {
		fprintf(fp, "0x%08x, ", _pio_info_g.rxfifo[i]);
	}
	fprintf(fp, "0x%08x", _pio_info_g.rxfifo[3]);
	fprintf(fp, "\n");
}


static bool pio_check_existence_of_code(void)
{
	int		inst, i;
	bool	ret	= false;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*ap;
		ap		= &(_pio_info_g.asmline[i]);
		inst	= ap->inst_type;
		if (ap->used == false)
			break;
		if (inst == PIO_INST_WRAP_TARGET) {
			ret	= false;	// IMPORTANT: reset flag
			continue;
		}
		if (inst == PIO_INST_COMMENT || inst == PIO_INST_LABEL || inst == PIO_INST_WRAP_TARGET || inst == PIO_INST_WRAP || inst == PIO_INST_ORIGIN)
			continue;

//		return true;	// IMPORTANT: do not return
		ret	= true;
	}
	return ret;
}


static uint32_t pio_input_inpin_value(void)
{
	uint32_t	ret;
	ret	= (_pio_info_g.gpio_i & _pio_info_g.in_pin_setmask) >> (_pio_info_g.in_pins);
	return ret;
}


static void pio_output_outpin_value(uint32_t val)
{
	uint32_t	real_val;
	real_val	= (val << (_pio_info_g.out_pins)) & _pio_info_g.out_pin_setmask;
	_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.out_pin_clrmask)
									| real_val;
}


static void pio_output_sideset_value(int sideset)
{
	if (_pio_info_g.sideset_opt == true || sideset != PIO_UNUSE) {
		if (sideset != PIO_UNUSE) {
			_pio_info_g.sideset_val	= (sideset << (_pio_info_g.sideset_pins)) & _pio_info_g.sideset_pin_setmask;
		}
		_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.sideset_pin_clrmask)
									| _pio_info_g.sideset_val;
	}
}


static void pio_exec_instruction(void)
{
	_PIO_INST	*ap;
	int 		inst, op1, op2, op3, op4, op5;
	int 		sideset, delay;
	char 		*str;
	int			linenum;
	uint8_t		addr;

	bool		autopull_failure;

	/////////////////////////////////////////////////////////
	// return immediately if executing delay cycles
	/////////////////////////////////////////////////////////
	if (_pio_info_g.delay_timer > 0) {
		pio_write_csv_output_inst();
		pio_write_csv_output_regs();
#ifdef DISP_TRACE_STDOUT
		fprintf(stdout, "cycle %d\t\t\tDELAY\n", _pio_info_g.cycles);
#endif

		(_pio_info_g.delay_timer)--;		// decrement delay timer
		(_pio_info_g.cycles)++;				// increment cycle counter
		return;
	}

	/////////////////////////////////////////////////////////
	// cut pseudo instructions
	/////////////////////////////////////////////////////////
	while (1) {
		ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);
		inst	= ap->inst_type;

		if (ap->used == false) {			// reached to the end of code list
			_pio_info_g.asmline_ptr	= 0;
			continue;
		}
		else if (inst == PIO_INST_COMMENT || inst == PIO_INST_LABEL || inst == PIO_INST_WRAP_TARGET || inst == PIO_INST_ORIGIN) {
			// skip this code
			(_pio_info_g.asmline_ptr)++;
			if (_pio_info_g.asmline_ptr >= PIO_MAX_ASMLINE_NUM) {
				_pio_info_g.asmline_ptr	= 0;
			}
			continue;
		}
		else if (inst == PIO_INST_WRAP) {
			// jump to wrap target
			_pio_info_g.asmline_ptr	= pio_search_wrap_target();
		}
		else
			break;
	};

	/////////////////////////////////////////////////////////
	// update input
	/////////////////////////////////////////////////////////
	pio_read_csv_input();

	/////////////////////////////////////////////////////////
	// autopull operation (if specified)
	/////////////////////////////////////////////////////////
	autopull_failure	= false;
	if (_pio_info_g.osr_autopull == true && _pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {	// reached to autopull threshold
		uint32_t	pop_val;
		if (pio_pop_txfifo(&pop_val) == true) {
			_pio_info_g.osr			= pop_val;
			_pio_info_g.osr_bitctr	= 0;			// (full)
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tAUTOPULL\n");
#endif
		}
		else {
			autopull_failure	= true;
		}
	}

	/////////////////////////////////////////////////////////
	// exec instruction
	/////////////////////////////////////////////////////////
	op1		= ap->operand1;
	op2		= ap->operand2;
	op3		= ap->operand3;
	op4		= ap->operand4;
	op5		= ap->operand5;
	sideset	= ap->sideset;
	delay	= ap->delay;
	str		= ap->strbuf;
	linenum	= ap->code_line;
	addr	= ap->addr;

	pio_write_csv_output_inst();		// write instruction BEFORE executing instruction
#ifdef DISP_TRACE_STDOUT
	fprintf(stdout, "cycle %d, line %d, pc=%d\t%s\n", _pio_info_g.cycles, ap->code_line, ap->addr, ap->asmbuf);
#endif

	switch (inst) {
	/////////////////////////////////
	// JMP
	/////////////////////////////////
	case PIO_INST_JMP: {
		bool		jmpcond;
		uint32_t	pinval;

		// condition
		switch (op1) {
		case PIO_ALWAYS:
			jmpcond	= true;
			break;

		case PIO_X_EQ_0:
			jmpcond	= (_pio_info_g.x == 0)	? true : false;
			break;

		case PIO_X_NEQ_0_DEC:
			jmpcond	= (_pio_info_g.x != 0)	? true : false;
			(_pio_info_g.x)--;		// post decrement
			break;

		case PIO_Y_EQ_0:
			jmpcond	= (_pio_info_g.y == 0)	? true : false;
			break;

		case PIO_Y_NEQ_0_DEC:
			jmpcond	= (_pio_info_g.y != 0)	? true : false;
			(_pio_info_g.y)--;		// post decrement
			break;

		case PIO_X_NEQ_Y:
			jmpcond	= (_pio_info_g.x != _pio_info_g.y)	? true : false;
			break;

		case PIO_PIN:
			if (_pio_info_g.jmp_pin == PIO_UNUSE) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. No pin assignment is given to JMP_PIN (JMP in step %d).\n", linenum);
				exit(1);
			}
			else {
				pinval	= _pio_info_g.jmp_pin_setmask & _pio_info_g.gpio_i;
				jmpcond	= (pinval != 0)	? true : false;		// jmp if gpio(EXECCTRL_JMP_PIN) == 1
			} 
			break;

		case PIO_OSRE_NOTEMPTY:
			jmpcond	= (_pio_info_g.osr_bitctr < _pio_info_g.osr_autopull_threshold)	? true : false;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal condition (JMP in step %d).\n", linenum);
			exit(1);
		} // op1

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (jmpcond == false)
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
		else {
			_pio_info_g.asmline_ptr	= op2;	// jump to the specified line (INST_LABEL)
		}

		if (delay > 0) {					// set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// WAIT
	/////////////////////////////////
	case PIO_INST_WAIT: {
		bool		stall;

		int			pin_in;
		uint32_t	pin_mask;
		int			pin_value;

		bool		rel;
		int			irq_num;
		uint8_t		irq_setmask, irq_clrmask;

		// source
		switch (op2) {
		case PIO_GPIO:
			if (op3 < 0 || op3 > 29) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal GPIO assignment (WAIT in step %d).\n", linenum);
				exit(1);
			}
			pin_mask	= ((uint32_t)1 << op3) & 0x1FFFFFFF;	// GPIO28-0
			if ((pin_mask & _pio_info_g.out_pin_setmask) != 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Reffering to an output port (WAIT in step %d).\n", linenum);
				exit(1);
			}
			if ((pin_mask & _pio_info_g.sideset_pin_setmask) != 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Reffering to an sideset port (WAIT in step %d).\n", linenum);
				exit(1);
			}

			pin_value	= ((_pio_info_g.gpio_i & pin_mask) != 0)	? 1 : 0;
			stall		= (op1 == pin_value)						? false : true;		// polarity
			break;

		case PIO_PIN:
			if (_pio_info_g.in_num <= 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. No input pin is assigned (WAIT in step %d).\n", linenum);
				exit(1);
			}
			if (op3 < 0 || op3 > _pio_info_g.in_num - 1) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal index value (WAIT in step %d).\n", linenum);
				exit(1);
			}
			pin_in		= (_pio_info_g.in_pins + op3) % 32;
			pin_mask	= ((uint32_t)1 << pin_in) & 0x1FFFFFFF;		// GPIO28-0
			pin_value	= ((_pio_info_g.gpio_i & pin_mask) != 0)	? 1 : 0;
			stall		= (op1 == pin_value)						? false : true;		// polarity
			break;

		case PIO_IRQ:
			rel		= (op4 == 1)	? true : false;

			// calc actual IRQ number
			irq_num	= op3 & 0x07;						// bit2-0
// NEEDS SPEC CHECK HERE
			if (rel == true || (op3 & 0x10) != 0) {		// rel == 1 or MSB of index == 1
				irq_num	= ((irq_num + _pio_info_g.sm_id) & 0x03)		// module 4 addition to bit 1-0
							| (op3 & 0x0C);								// no effect to bit 3-2
			}
			if (0 > irq_num || irq_num > 7) {
				fprintf(stderr, "pio_exec_instruction(): Internal ERROR. Illegal irq_num (WAIT in step %d).\n", linenum);
				exit(1);
			}

			irq_setmask	= (uint8_t)1 << irq_num;
			irq_clrmask	= irq_setmask ^ 0xFF;

			// status check
			if (op1 == 1 && (_pio_info_g.irq_i & irq_setmask) != 0) {		// wait for 1
				stall	= false;
// NEEDS SPEC CHECK HERE
				_pio_info_g.irq_o	&= irq_clrmask;		// clear INT
				_pio_info_g.irq_i	&= irq_clrmask;		// IMPORTANT: reflect to irq_in_buf
			}
			else if (op1 == 0 && (_pio_info_g.irq_i & irq_setmask) == 0) {	// wait for 0
				stall	= false;
			}
			else {
				stall	= true;
			}
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (WAIT in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

//		if (stall == false) {
		if (stall == false && _pio_info_g.irq_stalling == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { 				// set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}
		// else stall 	IMPORTANT NOTE: delay is NOT executed while stalling

		} break;

	/////////////////////////////////
	// IN
	/////////////////////////////////
	case PIO_INST_IN: {
		uint32_t	src_val, newisr_val;
		int			shift_amount;
		bool		stall;

		if (op2 <= 0 || op2 > 32) {
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal bit count (IN in step %d).\n", linenum);
			exit(1);
		}
		shift_amount	= op2;

		// source
		switch (op1) {
		case PIO_PINS:
			src_val	= pio_input_inpin_value();
			break;

		case PIO_X:
			src_val	= _pio_info_g.x;
			break;

		case PIO_Y:
			src_val	= _pio_info_g.y;
			break;

		case PIO_NULL:
			src_val	= 0;
			break;

		case PIO_ISR:
			src_val	= _pio_info_g.isr;
			break;

		case PIO_OSR:
			src_val	= _pio_info_g.osr;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (IN in step %d).\n", linenum);
			exit(1);
		}

		// dest
		src_val	&= pio_maxval(shift_amount);	// AND bitmask (use LSB side)
		if (_pio_info_g.isr_shift_right == true) {
			// right shift
			src_val	<<=	32 - shift_amount;
//			_pio_info_g.isr	= (_pio_info_g.isr >> shift_amount) | src_val;		// BUG
			newisr_val	= (_pio_info_g.isr >> shift_amount) | src_val;			// IMPORTANT: not substitute here, for autopush stall
		}
		else {
			// left shift
//			_pio_info_g.isr	= (_pio_info_g.isr << shift_amount) | src_val;		// BUG
			newisr_val	= (_pio_info_g.isr << shift_amount) | src_val;			// IMPORTANT: not substitute here, for autopush stall
		}

		// autopush and substitute
		stall	= false;

		if (_pio_info_g.isr_autopush == true && _pio_info_g.isr_bitctr + shift_amount >= _pio_info_g.isr_autopush_threshold) {
//			if (pio_push_rxfifo(_pio_info_g.isr) == true) {		// push operation	BUG
			if (pio_push_rxfifo(newisr_val) == true) {	// push operation
				_pio_info_g.isr			= 0;			// clear ISR
				_pio_info_g.isr_bitctr	= 0;			// (empty)
			}
			else {	// push failure
				stall	= true;							// wait until rxfifo has a empty space
			}
		}
		else {	// no autopush (normal operation)
			_pio_info_g.isr			= newisr_val;		// update ISR
			_pio_info_g.isr_bitctr	+= shift_amount;	// update ctr
			if (_pio_info_g.isr_bitctr > _pio_info_g.isr_autopush_threshold) {
				_pio_info_g.isr_bitctr	= _pio_info_g.isr_autopush_threshold;
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {	// go to next instruction if not stall
			(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// OUT
	/////////////////////////////////
	case PIO_INST_OUT: {
		uint32_t	dest_val;
		int			shift_amount;

		if (op2 <= 0 || op2 > 32) {
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal bit count (OUT in step %d).\n", linenum);
			exit(1);
		}
		shift_amount	= op2;

		// read osr
		if (_pio_info_g.osr_shift_right == true) {
			// get lsb
			dest_val		= _pio_info_g.osr & pio_maxval(shift_amount);
//			_pio_info_g.osr	>>= shift_amount;		// BUG: do not update here, for autopull stall
		}
		else {
			// get msb
			dest_val		= (_pio_info_g.osr >> (32 - shift_amount)) & pio_maxval(shift_amount);
//			_pio_info_g.osr	<<= shift_amount;		// BUG: do not update here, for autopull stall
		}

		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(dest_val);
			break;

		case PIO_X:
			_pio_info_g.x	= dest_val;
			break;

		case PIO_Y:
			_pio_info_g.y	= dest_val;
			break;

		case PIO_NULL:
			// do nothing, discard data
			break;

		case PIO_PINDIRS:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
// (Unsupported independent pin assignment between SET and OUT)
fprintf(stderr, "pio_exec_instruction(): WARNING. Unsupported destination PINDIRS, ignored (OUT in step %d).\n", linenum);
			break;

		case PIO_PC:
			break;

		case PIO_ISR:
			_pio_info_g.isr	= dest_val;
			break;

		case PIO_EXEC:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
fprintf(stderr, "pio_exec_instruction(): ERROR. Unsupported destination EXEC (OUT in step %d).\n", linenum);
exit(1);
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
			exit(1);
		}

		if (autopull_failure == false) {	// (tested at the top of exec cycle)
			// update osr
			if (_pio_info_g.osr_shift_right == true) {
				_pio_info_g.osr	>>= shift_amount;
			}
			else {
				_pio_info_g.osr	<<= shift_amount;
			}

			// update bitctr
			_pio_info_g.osr_bitctr	+= shift_amount;
			if (_pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {
				_pio_info_g.osr_bitctr	= _pio_info_g.osr_autopull_threshold;	// (empty)
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (autopull_failure == false) {	// (tested at the top of exec cycle)
			if (op1 != PIO_PC) {
				(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
			}
			else {	// OUT PC (unconditional jmp)
				int	asmline;
				if (pio_get_asmline_pc(&asmline, dest_val) == false) {
					fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
					exit(1);
				}
				_pio_info_g.asmline_ptr	= asmline;
			}

			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}
		// (else stall until autopull success)

		} break;

	/////////////////////////////////
	// PUSH
	/////////////////////////////////
	case PIO_INST_PUSH: {
		bool	push_done, iffull, block;
		bool	stall;
		iffull	= (op1 == 1)	? true : false;
		block	= (op2 == 1)	? true : false;

		stall	= false;

		if (iffull == false || _pio_info_g.isr_bitctr >= _pio_info_g.isr_autopush_threshold) {
			push_done		= pio_push_rxfifo(_pio_info_g.isr);		// push operation

			if (push_done == true) {
				_pio_info_g.isr			= 0;		// IMPORTANT: clear ISR
// SPECIFICATION UNCONFIRMED: clearing bitnum
				_pio_info_g.isr_bitctr	= 0;		// (empty)
			}
			else {	// push faliure
				if (block == true) {	// blocking
					stall	= true;
				}
				else {					// nonblocking
					_pio_info_g.isr			= 0;	// IMPORTANT: clear ISR
// SPECIFICATION UNCONFIRMED: clearing bitnum
					_pio_info_g.isr_bitctr	= 0;	// (empty)
				}
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// PULL
	/////////////////////////////////
	case PIO_INST_PULL: {
		bool	pop_done, ifempty, block;
		bool	stall;
		uint32_t	pop_val;
		ifempty		= (op1 == 1)	? true : false;
		block		= (op2 == 1)	? true : false;

		stall	= false;

		if (ifempty == false || _pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {
			pop_done	= pio_pop_txfifo(&pop_val);		// pop operation

			if (pop_done == true) {
				_pio_info_g.osr			= pop_val;
// SPECIFICATION UNCONFIRMED: clearing bitnum
				_pio_info_g.osr_bitctr	= 0;			// (full)
			}
			else {	// pop failure
				if (block == true) {	// blocking
					stall	= true;
				}
				else {					// nonblocking
					_pio_info_g.osr			= _pio_info_g.x;	// IMPORTANT: mov x, osr
// SPECIFICATION UNCONFIRMED: clearing bitnum
					_pio_info_g.osr_bitctr	= 0;				// IMPORTANT (full)
				}
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// MOV
	/////////////////////////////////
	case PIO_INST_MOV: {
		uint32_t	src_val;

		// source
		switch (op3) {
		case PIO_PINS:
			src_val	= pio_input_inpin_value();
			break;

		case PIO_X:
			src_val	= _pio_info_g.x;
			break;

		case PIO_Y:
			src_val	= _pio_info_g.y;
			break;

		case PIO_NULL:
			src_val	= 0;
			break;

		case PIO_STATUS:
			// see https://forums.raspberrypi.com/viewtopic.php?t=314334
			if (_pio_info_g.mov_status_sel == true) {	// TX FIFO
				if (_pio_info_g.txfifo_num < _pio_info_g.mov_status_val)
					src_val	= 0xFFFFFFFF;
				else
					src_val	= 0;
			}
			else {	// RX FIFO
				if (_pio_info_g.rxfifo_num < _pio_info_g.mov_status_val)
					src_val	= 0xFFFFFFFF;
				else
					src_val	= 0;
			}
			break;

		case PIO_ISR:
			src_val	= _pio_info_g.isr;
			break;

		case PIO_OSR:
//			if (_pio_info_g.osr_autopull == true && autopull_failure == false) {
//				fprintf(stderr, "pio_exec_instruction(): WARNING. Auto-pulled OSR value will be used (MOV in step %d).\n", linenum);
//			}
			src_val	= _pio_info_g.osr;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (MOV in step %d).\n", linenum);
			exit(1);
		}

		// operation
		switch (op2) {
		case PIO_NONE:
			// nothing to do
			break;
		case PIO_INVERT:
			src_val	^= 0xFFFFFFFF;
			break;
		case PIO_BIT_REVERSE:
			src_val	= _pio_bitreverse(src_val);
			break;
		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal operation (MOV in step %d).\n", linenum);
			exit(1);
		}

		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(src_val & 0x1F);
			break;

		case PIO_X:
			_pio_info_g.x	= src_val;
			break;

		case PIO_Y:
			_pio_info_g.y	= src_val;
			break;

		case PIO_EXEC:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
fprintf(stderr, "pio_exec_instruction(): ERROR. Unsupported destination EXEC (MOVE in step %d).\n", linenum);
exit(1);
			break;

		case PIO_PC:
			break;

		case PIO_ISR:
			_pio_info_g.isr			= src_val;
			_pio_info_g.isr_bitctr	= 0;			// IMPORTANT
			break;

		case PIO_OSR:
			if (_pio_info_g.osr_autopull == true) {
				fprintf(stderr, "pio_exec_instruction(): WARNING. Auto-pulled OSR value will be discarded and overwritten (MOV in step %d).\n", linenum);
			}

			_pio_info_g.osr			= src_val;
			_pio_info_g.osr_bitctr	= 0;			// IMPORTANT (full)
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (op1 != PIO_PC) {
			(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		}
		else {	// MOV PC (unconditional jmp)
			int		asmline;
			if (pio_get_asmline_pc(&asmline, src_val) == false) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
				exit(1);
			}
			_pio_info_g.asmline_ptr	= asmline;
		}

		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// IRQ
	/////////////////////////////////
	case PIO_INST_IRQ: {
		bool		clr, wait, rel;
		int			irq_num;
		uint8_t		irq_setmask, irq_clrmask;

		clr		= (op1 == 1)	? true : false;
		wait	= (op2 == 1)	? true : false;
		rel		= (op4 == 1)	? true : false;

		// calc actual IRQ number
		irq_num	= op3 & 0x07;						// bit2-0
// NEEDS SPEC CHECK HERE
//		if (rel == true) {
		if (rel == true || (op3 & 0x10) != 0) {		// rel == 1 or MSB of index == 1
			irq_num	= ((irq_num + _pio_info_g.sm_id) & 0x03)		// module 4 addition to bit 1-0
						| (op3 & 0x0C);								// no effect to bit 3-2
		}
		if (0 > irq_num || irq_num > 7) {
			fprintf(stderr, "pio_exec_instruction(): Internal ERROR. Illegal irq_num (IRQ in step %d).\n", linenum);
			exit(1);
		}

		irq_setmask	= (uint8_t)1 << irq_num;
//fprintf(stderr, "setmask %02x, num %d\n", irq_setmask, irq_num);
		irq_clrmask	= irq_setmask ^ 0xFF;

		// status check
		if (_pio_info_g.irq_stalling == false) {
			if (clr == true) {
				// clear int
				_pio_info_g.irq_o		&= irq_clrmask;
				_pio_info_g.irq_i		&= irq_clrmask;		// IMPORTANT: reflect to irq_in_buf
			}
			else {
				// set int
				_pio_info_g.irq_o		|= irq_setmask;
				_pio_info_g.irq_i		|= irq_setmask;		// IMPORTANT: reflect to irq_in_buf

				if (wait == true) {
					_pio_info_g.irq_stalling	= true;
				}
			}
		}
		else {	// stalling
			// handshake; waiting change of irq_i
			if ((_pio_info_g.irq_i & irq_setmask) == 0) {
				_pio_info_g.irq_stalling	= false;
				_pio_info_g.irq_o			&= irq_clrmask;
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (_pio_info_g.irq_stalling == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// SET
	/////////////////////////////////
	case PIO_INST_SET: {
		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(op2 & 0x1F);
			break;

		case PIO_X:
			_pio_info_g.x	= op2 & 0x1F;		// note: bit31-5 will be cleared
			break;

		case PIO_Y:
			_pio_info_g.y	= op2 & 0x1F;		// note: bit31-5 will be cleared
			break;

		case PIO_PINDIRS:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
// (Unsupported independent pin assignment between SET and OUT)
fprintf(stderr, "pio_exec_instruction(): WARNING. Unsupported destination PINDIRS, ignored (SET in step %d).\n", linenum);
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (SET in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction
		(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// pseudo instructions
	/////////////////////////////////
	case PIO_INST_NOP: {
		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction
		(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	default:
		fprintf(stderr, "pio_exec_instruction(): ERROR. Internal error (INST).\n");
		exit(1);
	}

	// inc cycle counter
	(_pio_info_g.cycles)++;				// increment cycle counter
}


void pio_run_emulation(int cycles, char *file_name_in, char *file_name_out)
{
	int	ctr;

	if (_pio_emu_state_g != PIO_SIMSTATE_RUN_START) {
		fprintf(stderr, "pio_run_emulation(): ERROR. Illegal run-start position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_RUN_END;

	/////////////////////////////////////
	// init
	/////////////////////////////////////
	if (_pio_emu_state_g == false) {
		fprintf(stderr, "pio_run_emulation(): ERROR. No asm code is given for emulation.\n");
		exit(1);
	}
	if (file_name_in != (char *)NULL) {		// open input csv
		if ((_pio_info_g.fin = fopen(file_name_in, "rt")) == (FILE *)NULL) {
			fprintf(stderr, "pio_run_emulation(): ERROR. Cannot open input CSV file \"%s\".\n", file_name_in);
			exit(1);
		}
	}
	if (file_name_out != (char *)NULL) {	// create output csv
		if ((_pio_info_g.fout = fopen(file_name_out, "wt")) == (FILE *)NULL) {
			fprintf(stderr, "pio_run_emulation(): ERROR. Cannot create output CSV file \"%s\".\n", file_name_out);
//			if (_pio_info_g.fin != (FILE *)NULL) {
//				fclose(_pio_info_g.fin);
//			}
			exit(1);
		}
	}

	/////////////////////////////////////
	// main loop
	/////////////////////////////////////
	if (pio_check_existence_of_code() == false) {
		fprintf(stderr, "pio_run_emulation(): ERROR. No instruction exists in the main loop (wrap_target to wrap).\n");
		exit(1);
	}

//	fprintf(stderr, "\nstart emulation\n");

	pio_read_csv_input_header();
	pio_write_csv_output_header();
	for (ctr = 0; ctr < cycles; ctr++) {
		pio_exec_instruction();
	}

	/////////////////////////////////////
	// closing
	/////////////////////////////////////
	if (_pio_info_g.fin != (FILE *)NULL) {
		fclose(_pio_info_g.fin);
	}
	if (_pio_info_g.fout != (FILE *)NULL) {
		fclose(_pio_info_g.fout);
	}

	_pio_emu_state_g	= false;
}


static void pio_register_instruction(int inst, int op1, int op2, int op3, int op4, int op5, int sideset, int delay, char *str)
{
	_PIO_INST	*ap;
	char		*strbuf;
	char		*asmbuf;
	int			linenum;
	char		tmpbuf[PIO_MAX_ASMLINE_LEN * 2 + 1];
	int			sideset_num, sideset_maxval, delay_maxval;
	bool		sideset_opt;

	if (_pio_info_g.asmline_ptr >= PIO_MAX_ASMLINE_NUM) {
		fprintf(stderr, "pio_register_instruction(): ERROR. Too many assembler steps.\n");
		exit(1);
	}

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);
	strbuf	= ap->strbuf;
	asmbuf	= ap->asmbuf;
	linenum	= _pio_info_g.asmline_ptr + 1;

	sideset_num		= _pio_info_g.sideset_num;
	sideset_maxval	= _pio_info_g.sideset_maxval;
	sideset_opt		= _pio_info_g.sideset_opt;
	delay_maxval	= _pio_info_g.delay_maxval;

	/////////////////////////////////////
	// copy contents
	/////////////////////////////////////
	ap->used		= true;
	ap->code_line	= linenum;

//	ap->addr		= _pio_info_g.inst_ptr;
	if (_pio_info_g.origin == PIO_UNUSE)
		ap->addr	= _pio_info_g.inst_ptr;
	else
		ap->addr	= (_pio_info_g.inst_ptr + _pio_info_g.origin) & 0x3F;

	ap->inst_type	= inst;
	ap->operand1	= op1;
	ap->operand2	= op2;
	ap->operand3	= op3;
	ap->operand4	= op4;
	ap->operand5	= op5;
	ap->sideset		= sideset;
	ap->delay		= delay;
	if (str != (char *)NULL) {
		strcpy(strbuf, str);
	}

	/////////////////////////////////////
	// create assembler line
	/////////////////////////////////////
	if (_pio_info_g.wrap_line != PIO_UNUSE) {
		fprintf(stderr, "pio_register_instruction(): ERROR. No statement is allowed after \".wrap\".\n");	//, linenum);
		exit(1);
	}

	switch (inst) {
	/////////////////////////////////
	// JMP
	/////////////////////////////////
	case PIO_INST_JMP:
		sprintf(asmbuf, "jmp");

		// condition
		switch (op1) {
		case PIO_ALWAYS:
			strcat(asmbuf, "\t");
			break;
		case PIO_X_EQ_0:
			strcat(asmbuf, "\t!x\t");
			break;
		case PIO_X_NEQ_0_DEC:
			strcat(asmbuf, "\tx--\t");
			break;
		case PIO_Y_EQ_0:
			strcat(asmbuf, "\t!y\t");
			break;
		case PIO_Y_NEQ_0_DEC:
			strcat(asmbuf, "\ty--\t");
			break;
		case PIO_X_NEQ_Y:
			strcat(asmbuf, "\tx!=y\t");
			break;
		case PIO_PIN:
			strcat(asmbuf, "\tpin\t");
			break;
		case PIO_OSRE_NOTEMPTY:
			strcat(asmbuf, "\t!osre\t");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal condition (JMP in step %d).\n", linenum);
			exit(1);
		}

		// address
		sprintf(tmpbuf, "%s%s", asmbuf, str);
		strcpy(asmbuf, tmpbuf);

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// WAIT
	/////////////////////////////////
	case PIO_INST_WAIT:
		sprintf(asmbuf, "wait");

		// polarity
		if (op1 == 0) {
			strcat(asmbuf, "\t0");
		}
		else {
			strcat(asmbuf, "\t1");
		}

		// source
		switch (op2) {
		case PIO_GPIO:
			strcat(asmbuf, " gpio");
			break;
		case PIO_PIN:
			strcat(asmbuf, " pin");
			break;
		case PIO_IRQ:
			strcat(asmbuf, " irq");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (WAIT in step %d).\n", linenum);
			exit(1);
		}

		// index
		sprintf(tmpbuf, " 0x%02x", op3);
		strcat(asmbuf, tmpbuf);

		// rel
		if (op4 == 1) {
			strcat(asmbuf, " _rel");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// IN
	/////////////////////////////////
	case PIO_INST_IN:
		sprintf(asmbuf, "in");

		// source
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_NULL:
			strcat(asmbuf, "\tnull");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "\tosr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (IN in step %d).\n", linenum);
			exit(1);
		}

		// bitcount
		if (op2 >= 1 && op2 <= 32) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal bit count (IN in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// OUT
	/////////////////////////////////
	case PIO_INST_OUT:
		sprintf(asmbuf, "out");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_NULL:
			strcat(asmbuf, "\tnull");
			break;
		case PIO_PINDIRS:
			strcat(asmbuf, "\tpindirs");
			break;
		case PIO_PC:
			strcat(asmbuf, "\tpc");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_EXEC:
			strcat(asmbuf, "\texec");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
			exit(1);
		}

		// bitcount
		if (op2 >= 1 && op2 <= 32) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal bit count (OUT in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// PUSH
	/////////////////////////////////
	case PIO_INST_PUSH:
		sprintf(asmbuf, "push");

		// iffull
		if (op1 == 1) {
			strcat(asmbuf, "\tiffull ");
		}
		else {
			strcat(asmbuf, "\t");
		}

		// block
		if (op2 == 0) {
			strcat(asmbuf, "noblock");
		}
		else {
			strcat(asmbuf, "block");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// PULL
	/////////////////////////////////
	case PIO_INST_PULL:
		sprintf(asmbuf, "pull");

		// ifempty
		if (op1 == 1) {
			strcat(asmbuf, "\tifempty ");
		}
		else {
			strcat(asmbuf, "\t");
		}

		// block
		if (op2 == 0) {
			strcat(asmbuf, "noblock");
		}
		else {
			strcat(asmbuf, "block");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// MOV
	/////////////////////////////////
	case PIO_INST_MOV:
		sprintf(asmbuf, "mov");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_EXEC:
			strcat(asmbuf, "\texec");
			break;
		case PIO_PC:
			strcat(asmbuf, "\tpc");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "\tosr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
			exit(1);
		}

		// operation
		switch (op2) {
		case PIO_NONE:
			strcat(asmbuf, " ");
			break;
		case PIO_INVERT:
			strcat(asmbuf, " !");
			break;
		case PIO_BIT_REVERSE:
			strcat(asmbuf, " ::");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal operation (MOV in step %d).\n", linenum);
			exit(1);
		}

		// source
		switch (op3) {
		case PIO_PINS:
			strcat(asmbuf, "pins");
			break;
		case PIO_X:
			strcat(asmbuf, "x");
			break;
		case PIO_Y:
			strcat(asmbuf, "y");
			break;
		case PIO_NULL:
			strcat(asmbuf, "null");
			break;
		case PIO_STATUS:
			strcat(asmbuf, "status");
			break;
		case PIO_ISR:
			strcat(asmbuf, "isr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "osr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (MOV in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// IRQ
	/////////////////////////////////
	case PIO_INST_IRQ:
		sprintf(asmbuf, "irq");

		// clr
		if (op1 == 1) {
			strcat(asmbuf, "\tclear");
			if (op2 == 1) {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal wait-condition (IRQ in step %d).\n", linenum);
				exit(1);
			}
		}
		else {
			// NOTE: Instructions "irq" and "irq set" are written as "irq nowait".
			if (op2 == 0)
				strcat(asmbuf, "\tnowait");
			else
				strcat(asmbuf, "\twait");
		}

		// irq_num
		if (op3 >= 0 && op3 <= 7) {
			sprintf(tmpbuf, " %d", op3);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal irq_num (IRQ in step %d).\n", linenum);
			exit(1);
		}

		// rel
		if (op4 == 1) {
			strcat(asmbuf, " rel");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// SET
	/////////////////////////////////
	case PIO_INST_SET:
		sprintf(asmbuf, "set");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_PINDIRS:
			strcat(asmbuf, "\tpindirs");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (SET in step %d).\n", linenum);
			exit(1);
		}

		// data
		if (op2 >= 0 && op2 <= 31) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal data (SET in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// pseudo instructions
	/////////////////////////////////
	case PIO_INST_COMMENT:
		sprintf(asmbuf, "; %s", strbuf);
		break;

	case PIO_INST_LABEL:
		sprintf(asmbuf, "%s:", strbuf);
		break;

	case PIO_INST_NOP:
		sprintf(asmbuf, "nop");

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	case PIO_INST_WRAP_TARGET:
		sprintf(asmbuf, ".wrap_target");

		if (_pio_info_g.wrap_target_line != PIO_UNUSE) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Multiple wrap_targets are written.\n");	//, linenum);
			exit(1);
		}
		_pio_info_g.wrap_target_line	= linenum;

		break;

	case PIO_INST_WRAP:
		sprintf(asmbuf, ".wrap");

		_pio_info_g.wrap_line			= linenum;
		break;

	case PIO_INST_ORIGIN:
		sprintf(asmbuf, ".origin %d", op1);

		if (_pio_info_g.origin != PIO_UNUSE) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal origin statement location.\n");
			exit(1);
		}
		if (op1 < 0 || op1 > 31) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal origin value.\n");
			exit(1);
		}
		_pio_info_g.origin	= op1;
		break;

	default:
		fprintf(stderr, "pio_register_instruction(): ERROR. Internal error (INST).\n");
		exit(1);
	}

	/////////////////////////////////////
	// increment asm buffer pointer
	/////////////////////////////////////
	(_pio_info_g.asmline_ptr)++;
}


void pio_jmp(int cond, char *lbl, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_JMP, cond, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, lbl);
}


void pio_wait(bool polarity, int src, int index, bool rel, int sideset, int delay)
{
	int	polarity_i	= (polarity == true)	? 1 : 0;
	int	rel_i		= (rel == true)			? 1 : 0;
	pio_register_instruction(PIO_INST_WAIT, polarity_i, src, index, rel_i, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_in(int src, int bitcount, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_IN, src, bitcount, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_out(int dest, int bitcount, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_OUT, dest, bitcount, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_push(bool iffull, bool block, int sideset, int delay)
{
	int	iffull_i	= (iffull == true)	? 1 : 0;
	int	block_i		= (block == true)	? 1 : 0;
	pio_register_instruction(PIO_INST_PUSH, iffull_i, block_i, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_pull(bool ifempty, bool block, int sideset, int delay)
{
	int	ifempty_i	= (ifempty == true)	? 1 : 0;
	int	block_i		= (block == true)	? 1 : 0;
	pio_register_instruction(PIO_INST_PULL, ifempty_i, block_i, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_mov(int dest, int op, int src, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_MOV, dest, op, src, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_irq(bool clr, bool wait, int index, bool rel, int sideset, int delay)
{
	int	clr_i	= (clr == true)		? 1 : 0;
	int	wait_i	= (wait == true)	? 1 : 0;
	int	rel_i	= (rel == true)		? 1 : 0;
	pio_register_instruction(PIO_INST_IRQ, clr_i, wait_i, index, rel_i, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_set(int dest, int data, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_SET, dest, data, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_comment(char *string)
{
	pio_register_instruction(PIO_INST_COMMENT, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, string);
}


void pio_label(char *lbl)
{
	pio_register_instruction(PIO_INST_LABEL, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, lbl);
}


void pio_nop(int sideset, int delay)
{
	pio_register_instruction(PIO_INST_NOP, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_wrap_target(void)
{
	pio_register_instruction(PIO_INST_WRAP_TARGET, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}


void pio_wrap(void)
{
	pio_register_instruction(PIO_INST_WRAP, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}


void pio_origin(int addr)
{
	pio_register_instruction(PIO_INST_ORIGIN, addr, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}

#endif	// PICOPIO_EMU
// end of file

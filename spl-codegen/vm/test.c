#include <stdio.h>
#include "machine_types.h"
#include "instruction.h"

#define MEMORY_SIZE_IN_WORDS 4096
#define NUM_REGISTERS 8

// the VM's memory, both in word and binary instruction views.
static union mem_u {
    word_type words[MEMORY_SIZE_IN_WORDS];
    uword_type uwords[MEMORY_SIZE_IN_WORDS];
    bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

// general purpose registers
static word_type GPR[NUM_REGISTERS];

int main()
{
    printf("0xffff is %d\n", 0xffff);
    GPR[0] = 0;
    memory.words[GPR[0]] = 0xffff;
    printf("memory.words[GPR[0]] is %d\n", memory.words[GPR[0]]);
    fprintf(stdout, "%8d: %d\n", GPR[0], memory.words[GPR[0]]);
    printf("zeroExt(0xff00) is %x in hex, %d in decimal\n",
	   machine_types_zeroExt(0xff00),
	   machine_types_zeroExt(0xff00));
    GPR[1] = 1;
    immed_instr_t ii;
    ii.immed = machine_types_zeroExt(0xff00);
    printf("ii.immed is %x in hex, %d in decimal\n", ii.immed, ii.immed);
    memory.words[GPR[1]] = 0 | ii.immed;
    fprintf(stdout, "%8d: %d\n", GPR[1], memory.words[GPR[1]]);
    memory.words[GPR[1]] = ii.immed | machine_types_zeroExt(0xff);
    fprintf(stdout, "%8d: %d\n", GPR[1], memory.words[GPR[1]]);

    GPR[2] = 2;
    uimmed_instr_t ui;
    ui.uimmed = machine_types_zeroExt(0xff00);
    printf("ui.uimmed is %x in hex, %d in decimal\n", ui.uimmed, ui.uimmed);
    memory.uwords[GPR[2]] = 0 | ui.uimmed;
    fprintf(stdout, "%8d: %d\n", GPR[2], memory.words[GPR[2]]);
    memory.uwords[GPR[2]] = memory.uwords[GPR[2]] | machine_types_zeroExt(0xff);
    fprintf(stdout, "%8d: %d\n", GPR[2], memory.uwords[GPR[2]]);

}

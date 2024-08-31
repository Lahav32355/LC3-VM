#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* windows only */
#include <Windows.h>
#include <conio.h> 


/*LC-3 architecture*/

/*The LC-3 has 65,536 memory locations each of which stores
a 16-bit value. This means it can store a total of only 128KB*/
#define MEMORY_MAX (1 << 16) 
uint16_t memory[MEMORY_MAX];  /* 65536 locations */

/*Registers*/

/*A register is a slot for storing a single value on the CPU
The LC-3 has 10 total registers, each of which is 16 bits.
8 general purpose registers (R0-R7)  
1 program counter (PC) register 
1 condition flags (COND) register
*/
enum
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,    /*program counter*/
    R_COND,  /*Condition flags register*/
    R_COUNT  /*Total number of registers*/
};

uint16_t reg[R_COUNT]; /*Array to store the values of all registers*/

/*Instruction set*/

/*An instruction in the LC-3 CPU is a 16-bit command consisting:
Opcode (4 bits): Specifies the task.
Parameters (12 bits): Provide inputs for the task.
The LC-3 has 16 opcodes, each representing a basic task the 
CPU can perform.*/

enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};

/*Condition flags*/

/*The R_COND register in the LC-3 stores 3 flags indicating
if the last calculation was positive, negative, or zero.*/

enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};


/*Procedure*/
/*
Load one instruction from memory at the address of the PC register.
Increment the PC register.
Look at the opcode to determine which type of instruction it should perform.
Perform the instruction using the parameters in the instruction.
Go back to step 1.
*/

uint16_t sign_extend(uint16_t x , int bit_count)
{
    if((x >> (bit_count -1)) & 1 )
    {
        x|= (0xFFFF << bit_count);
    }
    return x;
}

int main(int argc, const char* argv[])
{    
    /*Load Arguments*/
    if (argc < 2)
    {
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }
    for (int j = 1; j < argc; ++j)
    {
        if (!read_image(argv[j]))
        {
             printf("failed to load image: %s\n", argv[j]);
             exit(1);
        }
    }
    
    
}


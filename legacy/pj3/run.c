/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   run.c                                                     */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

int PCSrc;
uint32_t BRTarget;
int PCWrite;
int LW_STALL;

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc) {
	return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){
	/** Your implementation here */
	int i=0;
	FETCH_BIT = 1;

	if(LW_STALL){
		for(i=4; i>=3; i--)
			CURRENT_STATE.PIPE[i] = CURRENT_STATE.PIPE[i-1];
		CURRENT_STATE.PIPE[2] = 0;
	} else {
		for(i=4; i>=1; i--)
		CURRENT_STATE.PIPE[i] = CURRENT_STATE.PIPE[i-1];
	}

	BRTarget = CURRENT_STATE.MEM_WB_BR_TARGET;
	PCSrc = CURRENT_STATE.MEM_WB_PCSrc;

	LW_STALL = 0;

	WB_Stage();
	MEM_Stage();
	EX_Stage();
	ID_Stage();
	IF_Stage();

	for(i=0;i<4;i++)
		if(CURRENT_STATE.PIPE[i] != 0)
			break;
	if(i == 4) RUN_BIT = FALSE;
}

void IF_Stage()
{
	if(FETCH_BIT){
		switch(PCSrc){
		case 0:
			if(CYCLE_COUNT == 0) break;
			CURRENT_STATE.PC = CURRENT_STATE.IF_ID_NPC;
			break;
		case 1:
			CURRENT_STATE.PC = BRTarget;
			break;
		case 2:
			CURRENT_STATE.PC = CURRENT_STATE.EX_MEM_JUMP_TARGET;
			break;
		}
		if((CURRENT_STATE.PC-0x400000) >> 2 >= NUM_INST){
			CURRENT_STATE.PIPE[0] = 0;
			return;
		}
		CURRENT_STATE.PIPE[0] = CURRENT_STATE.PC;
	} else {
		CURRENT_STATE.PIPE[0] = 0;
		return;
	}
	instruction* inst = get_inst_info(CURRENT_STATE.PC);
	if(!LW_STALL){
		CURRENT_STATE.PC += 4;
		CURRENT_STATE.IF_ID_NPC = CURRENT_STATE.PC;
		CURRENT_STATE.IF_ID_INST = inst;
	}
	return;
}

void ID_Stage()
{
	if(CURRENT_STATE.PIPE[1] == 0) //instruction not loaded
		return;

	CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(CURRENT_STATE.IF_ID_INST)];
	CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.REGS[RT(CURRENT_STATE.IF_ID_INST)];
	CURRENT_STATE.ID_EX_NPC = CURRENT_STATE.IF_ID_NPC;
	CURRENT_STATE.ID_EX_IMM = SIGN_EX(IMM(CURRENT_STATE.IF_ID_INST));
	CURRENT_STATE.ID_EX_DEST = RD(CURRENT_STATE.IF_ID_INST);
	CURRENT_STATE.ID_EX_RT = RT(CURRENT_STATE.IF_ID_INST);
	CURRENT_STATE.ID_EX_JUMP_TARGET = (CURRENT_STATE.ID_EX_NPC & 0xf0000000) | (TARGET(CURRENT_STATE.IF_ID_INST)<<2);

	CURRENT_STATE.ID_EX_RegWrite = 1;
	CURRENT_STATE.ID_EX_RegDst = 0;
	CURRENT_STATE.ID_EX_MemWrite = 0;
	CURRENT_STATE.ID_EX_MemRead = 0;
	CURRENT_STATE.ID_EX_Branch = 0;
	CURRENT_STATE.ID_EX_Jump = 0;
	CURRENT_STATE.ID_EX_MemtoReg = 0;
	CURRENT_STATE.ID_EX_BR_TAKE = 0;

	if(RS(CURRENT_STATE.IF_ID_INST) == CURRENT_STATE.MEM_WB_FORWARD_REG &&
		CURRENT_STATE.MEM_WB_FORWARD_REG != 0){
		CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.MEM_WB_FORWARD_VALUE;
	}
	if(RT(CURRENT_STATE.IF_ID_INST) == CURRENT_STATE.MEM_WB_FORWARD_REG &&
		CURRENT_STATE.MEM_WB_FORWARD_REG != 0){
		CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.MEM_WB_FORWARD_VALUE;
	}
	if(RS(CURRENT_STATE.IF_ID_INST) == CURRENT_STATE.EX_MEM_FORWARD_REG &&
		CURRENT_STATE.EX_MEM_FORWARD_REG != 0){
		CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.EX_MEM_FORWARD_VALUE;
	}
	if(RT(CURRENT_STATE.IF_ID_INST) == CURRENT_STATE.EX_MEM_FORWARD_REG &&
		CURRENT_STATE.EX_MEM_FORWARD_REG != 0){
		CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.EX_MEM_FORWARD_VALUE;
	}

	switch(OPCODE(CURRENT_STATE.IF_ID_INST)){
		case 0x0: //R format
			switch(FUNC(CURRENT_STATE.IF_ID_INST)){
				case 0x0: //sll
					CURRENT_STATE.ID_EX_ALUOp = LSHIFT;
					CURRENT_STATE.ID_EX_REG1 = SHAMT(CURRENT_STATE.IF_ID_INST);
					break;
				case 0x2: //srl
					CURRENT_STATE.ID_EX_ALUOp = RSHIFT;
					CURRENT_STATE.ID_EX_REG1 = SHAMT(CURRENT_STATE.IF_ID_INST);
					break;
				case 0x8: //jr
					CURRENT_STATE.ID_EX_RegWrite = 0;
					CURRENT_STATE.ID_EX_Jump = 1;
					CURRENT_STATE.ID_EX_JUMP_TARGET = CURRENT_STATE.ID_EX_REG1;
					break;
				case 0x21: //addu
					CURRENT_STATE.ID_EX_ALUOp = ADD;
					break;
				case 0x23: //sub
					CURRENT_STATE.ID_EX_ALUOp = SUB;
					break;
				case 0x24: ///and
					CURRENT_STATE.ID_EX_ALUOp = AND;
					break;
				case 0x25: //or
					CURRENT_STATE.ID_EX_ALUOp = OR;
					break;
				case 0x27: //nor
					CURRENT_STATE.ID_EX_ALUOp = NOR;
					break;
				case 0x2b: //slt
					CURRENT_STATE.ID_EX_ALUOp = SLT;
					break;
			}
			CURRENT_STATE.ID_EX_RegDst = 1;
			break;
		case 0x3: //jal
			CURRENT_STATE.ID_EX_DEST = 31;
			CURRENT_STATE.ID_EX_RegDst = 1;
			CURRENT_STATE.ID_EX_ALUOp = ADD;
			CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.ID_EX_NPC;
			CURRENT_STATE.ID_EX_REG2 = 4;
			CURRENT_STATE.ID_EX_Jump = 1;
			break;
		case 0x2: //jump
			CURRENT_STATE.ID_EX_Jump = 1;
			CURRENT_STATE.ID_EX_RegWrite = 0;
			break;
		case 0x4: //beq
			CURRENT_STATE.ID_EX_BR_TAKE = 1;
		case 0x5: //bne
			CURRENT_STATE.ID_EX_Branch = 1;
			CURRENT_STATE.ID_EX_RegWrite = 0;
			CURRENT_STATE.ID_EX_ALUOp = SUB;
			break;
		case 0x2b://sw
			CURRENT_STATE.ID_EX_MemWrite = 1;
			CURRENT_STATE.ID_EX_RegWrite = 0;
			CURRENT_STATE.ID_EX_ALUOp = ADD;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0x23://lw
			CURRENT_STATE.ID_EX_MemtoReg = 1;
			CURRENT_STATE.ID_EX_MemRead = 1;
			CURRENT_STATE.ID_EX_ALUOp = ADD;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0x9://add
			CURRENT_STATE.ID_EX_ALUOp = ADD;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0xb: //slt
			CURRENT_STATE.ID_EX_ALUOp = SLT;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0xc: //and
			CURRENT_STATE.ID_EX_ALUOp = AND;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0xd: //or
			CURRENT_STATE.ID_EX_ALUOp = OR;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
		case 0xf: //lshift
			CURRENT_STATE.ID_EX_ALUOp = LSHIFT;
			CURRENT_STATE.ID_EX_REG1 = 16;
			CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.ID_EX_IMM;
			break;
	}


	return;
}

void EX_Stage()
{
	CURRENT_STATE.EX_MEM_NPC = CURRENT_STATE.ID_EX_NPC;
	CURRENT_STATE.EX_MEM_JUMP_TARGET = CURRENT_STATE.ID_EX_JUMP_TARGET;
	CURRENT_STATE.EX_MEM_W_VALUE = CURRENT_STATE.ID_EX_REG2;
	CURRENT_STATE.EX_MEM_BR_TAKE = CURRENT_STATE.ID_EX_BR_TAKE;

	CURRENT_STATE.EX_MEM_RegWrite = CURRENT_STATE.ID_EX_RegWrite;
	CURRENT_STATE.EX_MEM_MemWrite = CURRENT_STATE.ID_EX_MemWrite;
	CURRENT_STATE.EX_MEM_MemRead = CURRENT_STATE.ID_EX_MemRead;
	CURRENT_STATE.EX_MEM_Branch = CURRENT_STATE.ID_EX_Branch;
	CURRENT_STATE.EX_MEM_Jump = CURRENT_STATE.ID_EX_Jump;
	CURRENT_STATE.EX_MEM_MemtoReg = CURRENT_STATE.ID_EX_MemtoReg;

	CURRENT_STATE.EX_MEM_FORWARD_REG = 0;
	CURRENT_STATE.EX_MEM_FORWARD_VALUE = 0;

	if(CURRENT_STATE.PIPE[2] == 0)
		return;

	if(CURRENT_STATE.ID_EX_RegDst == 1){ //R format
		CURRENT_STATE.EX_MEM_DEST = CURRENT_STATE.ID_EX_DEST;
	}
	else {
		CURRENT_STATE.EX_MEM_DEST = CURRENT_STATE.ID_EX_RT; //rt becomes dest
	}

	switch(CURRENT_STATE.ID_EX_ALUOp){  //ALU Exe
		case LSHIFT:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG2 << CURRENT_STATE.ID_EX_REG1;
			break;
		case RSHIFT:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG2 >> CURRENT_STATE.ID_EX_REG1;
			break;
		case ADD:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 + CURRENT_STATE.ID_EX_REG2;
			break;
		case SUB:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 - CURRENT_STATE.ID_EX_REG2;
			break;
		case AND:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 & CURRENT_STATE.ID_EX_REG2;
			break;
		case OR:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 | CURRENT_STATE.ID_EX_REG2;
			break;
		case NOR:
			CURRENT_STATE.EX_MEM_ALU_OUT = ~(CURRENT_STATE.ID_EX_REG1 | CURRENT_STATE.ID_EX_REG2);
			break;
		case SLT:
			CURRENT_STATE.EX_MEM_ALU_OUT = CURRENT_STATE.ID_EX_REG1 < CURRENT_STATE.ID_EX_REG2;
			break;
	}

	//Branch ALU
	CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.EX_MEM_NPC + (CURRENT_STATE.ID_EX_IMM << 2);

	CURRENT_STATE.EX_MEM_Zero = (CURRENT_STATE.EX_MEM_ALU_OUT == 0); //Zero Signal

	if(CURRENT_STATE.EX_MEM_RegWrite){
		CURRENT_STATE.EX_MEM_FORWARD_REG = CURRENT_STATE.EX_MEM_DEST;
		CURRENT_STATE.EX_MEM_FORWARD_VALUE = CURRENT_STATE.EX_MEM_ALU_OUT;
	}

	if(CURRENT_STATE.EX_MEM_Jump){
		//flush ID
		PCSrc = 2;
		CURRENT_STATE.ID_EX_RegWrite = 0;
		CURRENT_STATE.ID_EX_RegDst = 0;
		CURRENT_STATE.ID_EX_MemWrite = 0;
		CURRENT_STATE.ID_EX_MemRead = 0;
		CURRENT_STATE.ID_EX_Branch = 0;
		CURRENT_STATE.ID_EX_Jump = 0;
		CURRENT_STATE.ID_EX_MemtoReg = 0;
		CURRENT_STATE.ID_EX_BR_TAKE = 0;
		CURRENT_STATE.PIPE[1] = 0;
	}

	if(CURRENT_STATE.ID_EX_MemRead &&
		((CURRENT_STATE.ID_EX_RT == RS(CURRENT_STATE.IF_ID_INST)) || (CURRENT_STATE.ID_EX_RT == RT(CURRENT_STATE.IF_ID_INST)))){
		//noop
		CURRENT_STATE.ID_EX_RegWrite = 0;
		LW_STALL = 1;
		return;
	}

	return;
}

void MEM_Stage()
{
	CURRENT_STATE.MEM_WB_BR_TAKE = CURRENT_STATE.EX_MEM_BR_TAKE;
	CURRENT_STATE.MEM_WB_NPC = CURRENT_STATE.EX_MEM_NPC;
	CURRENT_STATE.MEM_WB_JUMP_TARGET = CURRENT_STATE.EX_MEM_JUMP_TARGET;
	CURRENT_STATE.MEM_WB_BR_TARGET = CURRENT_STATE.EX_MEM_BR_TARGET;
	CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
	CURRENT_STATE.MEM_WB_DEST = CURRENT_STATE.EX_MEM_DEST;
	CURRENT_STATE.MEM_WB_RegWrite = CURRENT_STATE.EX_MEM_RegWrite;
	CURRENT_STATE.MEM_WB_MemtoReg = CURRENT_STATE.EX_MEM_MemtoReg;
	CURRENT_STATE.MEM_WB_PCSrc = 0;

	if(CURRENT_STATE.PIPE[3] == 0)
		return;

	if(CURRENT_STATE.EX_MEM_Branch){
		if (CURRENT_STATE.EX_MEM_BR_TAKE == CURRENT_STATE.EX_MEM_Zero){ //Branch;
			Flush_Branch();
			CURRENT_STATE.MEM_WB_PCSrc = 1;
		}
	}

	if(CURRENT_STATE.EX_MEM_MemWrite){ //sw
		mem_write_32(CURRENT_STATE.EX_MEM_ALU_OUT, CURRENT_STATE.EX_MEM_W_VALUE);
	}

	if(CURRENT_STATE.EX_MEM_MemRead){ //lw
		CURRENT_STATE.MEM_WB_MEM_OUT = mem_read_32(CURRENT_STATE.EX_MEM_ALU_OUT);
	}

	if(CURRENT_STATE.MEM_WB_RegWrite){
		CURRENT_STATE.MEM_WB_FORWARD_REG = CURRENT_STATE.MEM_WB_DEST;
		if(CURRENT_STATE.MEM_WB_MemtoReg == 0){
			CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_ALU_OUT;
		} else {
			CURRENT_STATE.MEM_WB_FORWARD_VALUE = CURRENT_STATE.MEM_WB_MEM_OUT;
		}
	}

	return;
}

void WB_Stage()
{
	if(CURRENT_STATE.PIPE[4] == 0)
		return;

	if(CURRENT_STATE.MEM_WB_RegWrite){
		if(CURRENT_STATE.MEM_WB_MemtoReg == 0){
			CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST] = CURRENT_STATE.MEM_WB_ALU_OUT;
		} else if (CURRENT_STATE.MEM_WB_MemtoReg == 1){
			CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST] = CURRENT_STATE.MEM_WB_MEM_OUT;
		}
	}

	if(CURRENT_STATE.PIPE[4] != 0)
		INSTRUCTION_COUNT++;

	return;
}

void Flush_Branch()
{
	int i;
	for(i=0; i<3; i++)
		CURRENT_STATE.PIPE[i] = 0; //flush pipe
	FETCH_BIT = 0;

	CURRENT_STATE.ID_EX_ALUOp = 0;
	CURRENT_STATE.ID_EX_RegDst = 0; //0 for RT, 1 for RD, can be used for determine R type
	CURRENT_STATE.ID_EX_ALUSrc = 0;
	CURRENT_STATE.ID_EX_MemWrite = 0;
	CURRENT_STATE.ID_EX_MemRead = 0;
	CURRENT_STATE.ID_EX_RegWrite = 0;
	CURRENT_STATE.ID_EX_Branch = 0;
	CURRENT_STATE.ID_EX_Jump = 0;
	CURRENT_STATE.ID_EX_MemtoReg = 0;
}

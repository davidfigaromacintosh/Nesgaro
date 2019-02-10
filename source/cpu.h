namespace CPU {

	//Zwraca dan¹ instrukcjê jako identyfikator
	u16 getOpcode(u8 opcode) {
		return opcodeMnemonic[opcode];
	}

	//Zwraca wskaŸnik do ³añcucha znaków z mnemonikiem danej instrukcji (nielegalna instrukcja zwróci mnemonik "ILL")
	const char* getOpcodeMnemonic(u8 opcode) {
		switch (opcodeMnemonic[opcode]) {
		case ADC: { return "ADC"; }
		case AND: { return "AND"; }
		case CMP: { return "CMP"; }
		case EOR: { return "EOR"; }
		case LDA: { return "LDA"; }
		case ORA: { return "ORA"; }
		case SBC: { return "SBC"; }
		case STA: { return "STA"; }

		case ASL: { return "ASL"; }
		case LDX: { return "LDX"; }
		case LDY: { return "LDY"; }
		case LSR: { return "LSR"; }
		case ROL: { return "ROL"; }
		case ROR: { return "ROR"; }

		case DEC: { return "DEC"; }
		case INC: { return "INC"; }
		case STX: { return "STX"; }
		case STY: { return "STY"; }

		case CPX: { return "CPX"; }
		case CPY: { return "CPY"; }

		case BIT: { return "BIT"; }

		case JMP: { return "JMP"; }

		case BCC: { return "BCC"; }
		case BCS: { return "BCS"; }
		case BEQ: { return "BEQ"; }
		case BMI: { return "BMI"; }
		case BNE: { return "BNE"; }
		case BPL: { return "BPL"; }
		case BRK: { return "BRK"; }
		case BVC: { return "BVC"; }
		case BVS: { return "BVS"; }
		case CLC: { return "CLC"; }
		case CLD: { return "CLD"; }
		case CLI: { return "CLI"; }
		case CLV: { return "CLV"; }
		case DEX: { return "DEX"; }
		case DEY: { return "DEY"; }
		case INX: { return "INX"; }
		case INY: { return "INY"; }
		case NOP: { return "NOP"; }
		case PHA: { return "PHA"; }
		case PHP: { return "PHP"; }
		case PLA: { return "PLA"; }
		case PLP: { return "PLP"; }
		case RTI: { return "RTI"; }
		case RTS: { return "RTS"; }
		case SEC: { return "SEC"; }
		case SED: { return "SED"; }
		case SEI: { return "SEI"; }
		case TAX: { return "TAX"; }
		case TAY: { return "TAY"; }
		case TSX: { return "TSX"; }
		case TXA: { return "TXA"; }
		case TXS: { return "TXS"; }
		case TYA: { return "TYA"; }
		case JSR: { return "JSR"; }

		case ILL: { return "ILL"; }

		default: { return "???"; }
		}
	}

	void init() {

		A = 0;
		X = 0;
		Y = 0;

		PC = 0xc000;
		S = 0xfd;
		P = 0x24;

	}

	void reset() {
		//TODO gdy napiszê menedzera pamiêci
	}

	void NMI() {
		//TODO -||-
	}

	//Zwraca ile cykli zajmuje wykonanie danej instrukcji
	int getOpcodeCycle(u8 opcode) {
		return (int)(opcodeCycle[opcode] - '0');
	}

	/* Wartoœci zwracane przez funkcje:
	0 = Accumulator
	1 = Immediate
	2 = Implied
	3 = Relative
	4 = Absolute
	5 = Zero-Page
	6 = Indirect
	7 = Absolute X
	8 = Absolute Y
	9 = Zero-page X
	10 = Zero-page Y
	11 = Indexed Indirect (X)
	12 = Indirect Indexed (Y)
	13 = Error
	*/
	u8 getOpcodeAddressingMode(u8 opcode) {

		/* Grupy
		0 = 1A
		1 = 1B
		2 = 2A
		3 = 2B
		4 = 3A
		5 = 3B
		6 = 4
		7 = Error
		*/
		u8 group = 7;
		switch (opcode) {

			/*1A
			case XXX_ABS: case XXX_ABS_X: case XXX_ABS_Y: case XXX_IMM: case XXX_IND_X: case XXX_IND_Y: case XXX_ZP: case XXX_ZP_X:	8  */
		case ADC_ABS: case ADC_ABS_X: case ADC_ABS_Y: case ADC_IMM: case ADC_IND_X: case ADC_IND_Y: case ADC_ZP: case ADC_ZP_X:	//ADC
		case AND_ABS: case AND_ABS_X: case AND_ABS_Y: case AND_IMM: case AND_IND_X: case AND_IND_Y: case AND_ZP: case AND_ZP_X:	//AND
		case CMP_ABS: case CMP_ABS_X: case CMP_ABS_Y: case CMP_IMM: case CMP_IND_X: case CMP_IND_Y: case CMP_ZP: case CMP_ZP_X:	//CMP
		case EOR_ABS: case EOR_ABS_X: case EOR_ABS_Y: case EOR_IMM: case EOR_IND_X: case EOR_IND_Y: case EOR_ZP: case EOR_ZP_X:	//EOR
		case LDA_ABS: case LDA_ABS_X: case LDA_ABS_Y: case LDA_IMM: case LDA_IND_X: case LDA_IND_Y: case LDA_ZP: case LDA_ZP_X:	//LDA
		case ORA_ABS: case ORA_ABS_X: case ORA_ABS_Y: case ORA_IMM: case ORA_IND_X: case ORA_IND_Y: case ORA_ZP: case ORA_ZP_X:	//ORA
		case SBC_ABS: case SBC_ABS_X: case SBC_ABS_Y: case SBC_IMM: case SBC_IND_X: case SBC_IND_Y: case SBC_ZP: case SBC_ZP_X:	//SBC
		case STA_ABS: case STA_ABS_X: case STA_ABS_Y:               case STA_IND_X: case STA_IND_Y: case STA_ZP: case STA_ZP_X:	//STA
		{ group = 0; break; }

		/*1B
		case XXX_ACC: case XXX_ABS: case XXX_ABS_X: case XXX_ABS_Y: case XXX_IMM: case XXX_ZP: case XXX_ZP_X: case XXX_ZP_Y:	6  */
		case ASL_ACC: case ASL_ABS: case ASL_ABS_X:                               case ASL_ZP: case ASL_ZP_X:					//ASL
		case LDX_ABS:                 case LDX_ABS_Y: case LDX_IMM: case LDX_ZP:                case LDX_ZP_Y:	//LDX
		case LDY_ABS: case LDY_ABS_X:                 case LDY_IMM: case LDY_ZP: case LDY_ZP_X:					//LDY
		case LSR_ACC: case LSR_ABS: case LSR_ABS_X:                               case LSR_ZP: case LSR_ZP_X:					//LSR
		case ROL_ACC: case ROL_ABS: case ROL_ABS_X:                               case ROL_ZP: case ROL_ZP_X:					//ROL
		case ROR_ACC: case ROR_ABS: case ROR_ABS_X:                               case ROR_ZP: case ROR_ZP_X:					//ROR
		{ group = 1; break; }

		/*2A
		case XXX_ABS: case XXX_ABS_X: case XXX_ABS_Y: case XXX_ZP: case XXX_ZP_X: case XXX_ZP_Y:								4  */
		case DEC_ABS: case DEC_ABS_X:                 case DEC_ZP: case DEC_ZP_X:												//DEC
		case INC_ABS: case INC_ABS_X:                 case INC_ZP: case INC_ZP_X:												//INC
		case STX_ABS:                                 case STX_ZP:                case STX_ZP_Y:								//STX
		case STY_ABS:                                 case STY_ZP: case STY_ZP_X:												//STY
		{ group = 2; break; }

		/*2B
		case XXX_ABS: case XXX_IMM: case XXX_ZP																					2  */
		case CPX_ABS: case CPX_IMM: case CPX_ZP:																				//CPX
		case CPY_ABS: case CPY_IMM: case CPY_ZP:																				//CPY
		{ group = 3; break; }

		/*3A
		case XXX_ABS: case XXX_ZP																								1  */
		case BIT_ABS: case BIT_ZP:																								//BIT
		{ group = 4; break; }

		/*3B
		case XXX_ABS: case XXX_IND																								1  */
		case JMP_ABS: case JMP_IND:																								//JMP
		{ group = 5; break; }

		/*4
		Reszta instrukcji																										34 */
		default:
		{ group = 6; break; }
		}

		switch (group) {
		case 0: {	//1A
			switch ((opcode & _1A_MASK) >> 2) {
			case 0: {
				return INDIRECT_X;
			}
			case 1: {
				return ZEROPAGE;
			}
			case 2: {
				return IMMEDIATE;
			}
			case 3: {
				return ABSOLUTE;
			}
			case 4: {
				return INDIRECT_Y;
			}
			case 5: {
				return ZEROPAGE_X;
			}
			case 6: {
				return ABSOLUTE_Y;
			}
			case 7: {
				return ABSOLUTE_X;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 1: {	//1B
			switch ((opcode & _1B_MASK) >> 2) {
			case 0: {
				return IMMEDIATE;
			}
			case 1: {
				return ZEROPAGE;
			}
			case 2: {
				return ACCUMULATOR;
			}
			case 3: {
				return ABSOLUTE;
			}
			case 5: {
				if (opcode == LDX_ABS || opcode == LDX_ABS_Y || opcode == LDX_IMM || opcode == LDX_ZP || opcode == LDX_ZP_Y)
				{
					return ZEROPAGE_Y;
				}
				else
				{
					return ZEROPAGE_X;
				}
			}
			case 7: {
				if (opcode == LDX_ABS || opcode == LDX_ABS_Y || opcode == LDX_IMM || opcode == LDX_ZP || opcode == LDX_ZP_Y)
				{
					return ABSOLUTE_Y;
				}
				else
				{
					return ABSOLUTE_X;
				}
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 2: {	//2A
			switch ((opcode & _2A_MASK) >> 3) {
			case 0: {
				return ZEROPAGE;
			}
			case 1: {
				return ABSOLUTE;
			}
			case 2: {
				if (opcode == STX_ABS || opcode == STX_ZP || opcode == STX_ZP_Y)
				{
					return ZEROPAGE_Y;
				}
				else
				{
					return ZEROPAGE_X;
				}
			}
			case 3: {
				return ABSOLUTE_X;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 3: {	//2B
			switch ((opcode & _2B_MASK) >> 2) {
			case 0: {
				return IMMEDIATE;
			}
			case 1: {
				return ZEROPAGE;
			}
			case 3: {
				return ABSOLUTE;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 4: {	//3A
			switch ((opcode & _3A_MASK) >> 3) {
			case 0: {
				return ZEROPAGE;
			}
			case 1: {
				return ABSOLUTE;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 5: {	//3B
			switch ((opcode & _3B_MASK) >> 5) {
			case 0: {
				return ABSOLUTE;
			}
			case 1: {
				return INDIRECT;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		case 6: {	//4
			switch (opcode) {
			case BPL: case BMI: case BVC: case BVS: case BCC: case BCS: case BNE: case BEQ: {
				return RELATIVE;
			}
			case BRK: case CLC: case CLD: case CLI: case CLV: case DEX: case DEY: case INX: case INY: case NOP: case PHA: case PHP: case PLA: case PLP: case RTI: case RTS: case SEC: case SED: case SEI: case TAX: case TAY: case TSX: case TXA: case TXS: case TYA: {
				return IMPLIED;
			}
			case JSR: {
				return ABSOLUTE;
			}
			default: {
				return ADDRMODE_ERROR;
			}
			}
		}
		default: {	//Error
			return ADDRMODE_ERROR;
		}

		}

		return ADDRMODE_ERROR;
	}

	int getOpcodeLength(u8 opcode) {
		switch (getOpcodeAddressingMode(opcode)) {
		case ACCUMULATOR: {
			return 1;
		}
		case IMMEDIATE: {
			return 2;
		}
		case IMPLIED: {
			return 1;
		}
		case RELATIVE: {
			return 2;
		}
		case ABSOLUTE: {
			return 3;
		}
		case ZEROPAGE: {
			return 2;
		}
		case INDIRECT: {
			return 3;
		}
		case ABSOLUTE_X: {
			return 3;
		}
		case ABSOLUTE_Y: {
			return 3;
		}
		case ZEROPAGE_X: {
			return 2;
		}
		case ZEROPAGE_Y: {
			return 2;
		}
		case INDIRECT_X: {
			return 2;
		}
		case INDIRECT_Y: {
			return 2;
		}
		default: {
			return 0;
		}
		}
	}

	//Wyœwietla tekst opisuj¹cy tryb adresowania danej instrukcji
	const char* getOpcodeAddressingModeName(u8 opcode) {
		switch (getOpcodeAddressingMode(opcode)) {
		case ACCUMULATOR: {
			return "Accumulator";
		}
		case IMMEDIATE: {
			return "Immediate";
		}
		case IMPLIED: {
			return "Implied";
		}
		case RELATIVE: {
			return "Relative";
		}
		case ABSOLUTE: {
			return "Absolute";
		}
		case ZEROPAGE: {
			return "Zero-Page";
		}
		case INDIRECT: {
			return "Indirect";
		}
		case ABSOLUTE_X: {
			return "Absolute X";
		}
		case ABSOLUTE_Y: {
			return "Absolute Y";
		}
		case ZEROPAGE_X: {
			return "Zero-Page X";
		}
		case ZEROPAGE_Y: {
			return "Zero-Page Y";
		}
		case INDIRECT_X: {
			return "Indexed Indirect (X)";
		}
		case INDIRECT_Y: {
			return "Indirect Indexed (Y)";
		}
		default: {
			return "Illegal";
		}
		}
	}

	/*
	//Definicje zadañ dla instrukcji
	void executeADC();

	//Tutaj zaczyna siê wykonywanie instrukcji
	void execute() {
		u8 addrmode = getOpcodeAddressingMode(PC);
		u16 opcode = getOpcode(PC);


	}
	*/
}
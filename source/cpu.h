namespace CPU {

	//Zwraca daną instrukcję jako identyfikator
	u16 getOpcode(u8 opcode) {
		return opcodeMnemonic[opcode];
	}

	//Zwraca wskaźnik do łańcucha znaków z mnemonikiem danej instrukcji (nielegalna instrukcja zwróci mnemonik "ILL")
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
		P = 0b00110100;

	}

	void reset() {
		//TODO gdy napiszę menedzera pamięci
	}

	void NMI() {
		//TODO -||-
	}

	//Zwraca ile cykli zajmuje wykonanie danej instrukcji
	u8 getOpcodeCycle(u8 opcode) {
		return opcodeCycle[opcode];
	}

	/* Wartości zwracane przez funkcje:
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

	//Wyświetla tekst opisujący tryb adresowania danej instrukcji
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

	//Ta funkcja sprawdza, czy została przekroczona strona. Jeśli tak, dodaj +1 do cyklu
	void checkPageCross(u16 pagea, u16 pageb, u8 value) {

		if ((pagea & 0xff00) != (pageb & 0xff00)) {
			cyclesLeft += value; //Jeżeli strona zostanie przkroczona, dodaj +value do cyklu
		}
	}

	//Ustaw flagi Z i N w zależności od podanego parametru
	void setFlagsZN(u8 value) {
		setZ(!value);
		setN(!!(value & 0x80));
	}

	//Zwraca wartość flagi
	b getC() {
		return (P & 0b00000001);
	}
	b getZ() {
		return ((P & 0b00000010) >> 1);
	}
	b getI() {
		return ((P & 0b00000100) >> 2);
	}
	b getD() {
		return ((P & 0b00001000) >> 3);
	}
	b getV() {
		return ((P & 0b01000000) >> 6);
	}
	b getN() {
		return ((P & 0b10000000) >> 7);
	}

	//Ustaw flagę na 1
	void setC() {
		P |= 0b00000001;
	}
	void setZ() {
		P |= 0b00000010;
	}
	void setI() {
		P |= 0b00000100;
	}
	void setD() {
		P |= 0b00001000;
	}
	void setV() {
		P |= 0b01000000;
	}
	void setN() {
		P |= 0b10000000;
	}

	/*
	
	u8 tf =
			(flag) |
			getZ() << 1 |
			getI() << 2 |
			getD() << 3 |
			P & 0b00010000 |
			0b00100000 |
			getV() << 6 |
			getN() << 7;

		P = tf;
		return;

	*/

	//Ustaw flagę w zależności od parametru
	void setC(u8 flag) {

		if (flag) { setC(); }
		else { clrC(); }
	}
	void setZ(u8 flag) {

		if (flag) { setZ(); }
		else { clrZ(); }
	}
	void setI(u8 flag) {

		if (flag) { setI(); }
		else { clrI(); }
	}
	void setD(u8 flag) {

		if (flag) { setD(); }
		else { clrD(); }
	}
	void setV(u8 flag) {

		if (flag) { setV(); }
		else { clrV(); }
	}
	void setN(u8 flag) {

		if (flag) { setN(); }
		else { clrN(); }
	}

	//Wyczyść flagę
	void clrC() {
		P &= 0b11111110;
	}
	void clrZ() {
		P &= 0b11111101;
	}
	void clrI() {
		P &= 0b11111011;
	}
	void clrD() {
		P &= 0b11110111;
	}
	void clrV() {
		P &= 0b10111111;
	}
	void clrN() {
		P &= 0b01111111;
	}

	//Zrób przerwanie
	void interrupt(u8 int_type) {

		// Wepchnij aktualny wskaźnik programu do stosu
		MAINBUS::pushStack((0xff00 & PC) >> 8);
		MAINBUS::pushStack(0xff & PC);

		// Jeżeli BRK, ustawiamy pozorną flagę B na 1
		P |= ((int_type == INT_BRK) << 4);

		// Wpychamy status procka do stosu
		MAINBUS::pushStack(P);

		switch (int_type) {
		case INT_NMI: {
			PC = MAINBUS::readAddr(MEM::NMI);
		}
		case INT_IRQ:
		case INT_BRK: {
			PC = MAINBUS::readAddr(MEM::IRQ);
		}

		}

	}

	//Jak na podstawie typu opokdu pobrać dane z operandu?
	//Na podstawie typu adresowania oraz danego operandu, zwraca adres danej wartości w pamięci
	u16 getAddressFromType(u8 addrmode, u16 pointer) {
		
		switch (addrmode) {
			
		case ABSOLUTE: {
			return MAINBUS::read(pointer) + MAINBUS::read(pointer + 1) * 256;
		}
		case ABSOLUTE_X: {
			return MAINBUS::read(pointer) + MAINBUS::read(pointer + 1) * 256 + X;
		}
		case ABSOLUTE_Y: {
			return MAINBUS::read(pointer) + MAINBUS::read(pointer + 1) * 256 + Y;
		}
		case IMMEDIATE: {
			return pointer;
		}
		case ZEROPAGE: {
			return MAINBUS::read(pointer);
		}
		case ZEROPAGE_X: {
			return (MAINBUS::read(pointer) + X) % 256;
		}
		case ZEROPAGE_Y: {
			return (MAINBUS::read(pointer) + Y) % 256;
		}
		case INDIRECT: {
			//INDIRECT używa jedynie instrukcja JMP
			u8 polo = MAINBUS::read(pointer);
			u16 pohi = 256 * MAINBUS::read(pointer + 1);

			//Typ INDIRECT posiada bardzo specyficznego buga: Nie potrafi przekraczać stron.
			//Przykład: Jeżeli jako operand mamy (Adresik) i pierwsze 2 bity od adresu "Adresik" to np. $24FF to MSB pobierze już nie z $2500 a z $2400.
			
			return MAINBUS::read(polo + pohi) +	MAINBUS::read(((polo + 1) % 256) + pohi) * 256;

		}
		case INDIRECT_X: {
			u8 val = MAINBUS::read(pointer);
			return MAINBUS::read((val + X) % 256) + MAINBUS::read((val + X + 1) % 256) * 256;
		}
		case INDIRECT_Y: {
			u8 val = MAINBUS::read(pointer);
			return MAINBUS::read(val) + MAINBUS::read((val + 1) % 256) * 256 + Y;
		}
		default: {
			return pointer;
		}
		}
		return pointer;
	}



	void executeBranch(u8 branch_type) {
		bool br = false;
		
		switch (branch_type) {
			case BPL: {
				br = !getN();
				break;
			}
			case BMI: {
				br = getN();
				break;
			}
			case BVC: {
				br = !getV();
				break;
			}
			case BVS: {
				br = getV();
				break;
			}
			case BCC: {
				br = !getC();
				break;
			}
			case BCS: {
				br = getC();
				break;
			}
			case BNE: {
				br = !getZ();
				break;
			}
			case BEQ: {
				br = getZ();
				break;
			}
		}

		if (br) {
			s8 off = MAINBUS::read(PC);
			cyclesLeft++;

			u16 PC2 = PC + off;
			checkPageCross(PC, PC2, 2);
			PC = PC2;
		}
	}


	//Definicje zadań dla instrukcji
	//1A - 8 typów adresacji
	void executeADC(u8 addrmode) {	//ADC
		
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC));

		u16 sum = A + operand + getC();
		setC(!!(sum & 0x100));
		setV( !!((A ^ sum) & (operand ^ sum) & 0x80) );
		A = sum & 0xff;

		setFlagsZN(A);
	}
	void executeAND(u8 addrmode) { //AND
		A &= MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(A);
	}
	void executeCMP(u8 addrmode) { //CMP
		u16 diff = A - MAINBUS::read(getAddressFromType(addrmode, PC));
		setC(!(diff & 0x100));
		setFlagsZN(diff & 0xff);
	}
	void executeEOR(u8 addrmode) { //EOR
		A ^= MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(A);
	}
	void executeLDA(u8 addrmode) { //LDA
		A = MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(A);
	}
	void executeORA(u8 addrmode) { //ORA
		A |= MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(A);
	}
	void executeSBC(u8 addrmode) { //SBC

		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC));

		u16 diff = A - operand - !getC();

		setC( !(diff & 0x100) );
		setV( !!((A ^ diff) & (~operand ^ diff) & 0x80) );
		A = diff & 0xff;

		setFlagsZN(A);
	}
	void executeSTA(u8 addrmode) { //STA
		MAINBUS::write(getAddressFromType(addrmode, PC), A);
	}

	//1B - 6 typów adresacji
	void executeASL(u8 addrmode) {	//ASL
		u8 tempC = getC();
		switch (addrmode) {
			case ACCUMULATOR: {
				setC(!!(A & 0x80));
				A <<= 1;
				setFlagsZN(A);
				break;
			}
			default: {
				u16 address = getAddressFromType(addrmode, PC);
				u8 operand = MAINBUS::read(address);
				setC(!!(operand & 0x80));
				operand = (operand << 1);
				setFlagsZN(operand);
				MAINBUS::write(address, operand);
				break;
			}
		}
	}
	void executeLDX(u8 addrmode) { //LDX
		X = MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(X);
	}
	void executeLDY(u8 addrmode) { //LDY
		Y = MAINBUS::read(getAddressFromType(addrmode, PC));
		setFlagsZN(Y);
	}
	void executeLSR(u8 addrmode) {	//LSR
		u8 tempC = getC();
		switch (addrmode) {
			case ACCUMULATOR: {
				setC(!!(A & 0x01));
				A >>= 1;
				setFlagsZN(A);
				break;
			}
			default: {
				u16 address = getAddressFromType(addrmode, PC);
				u8 operand = MAINBUS::read(address);
				setC(operand & 0x01);
				operand = (operand >> 1);
				setFlagsZN(operand);
				MAINBUS::write(address, operand);
				break;
			}
		}
	}
	void executeROL(u8 addrmode) {	//ROL
		u8 tempC = getC();
		switch (addrmode) {
			case ACCUMULATOR: {
				setC(!!(A & 0x80));
				A = (A << 1) | (tempC);
				setFlagsZN(A);
				break;
			}
			default: {
				u16 address = getAddressFromType(addrmode, PC);
				u8 operand = MAINBUS::read(address);
				setC(!!(operand & 0x80));
				operand = (operand << 1) | (tempC);
				setFlagsZN(operand);
				MAINBUS::write(address, operand);
				break;
			}
		}
	}
	void executeROR(u8 addrmode) {	//ROR
		u8 tempC = getC();
		switch (addrmode) {
			case ACCUMULATOR: {
				setC(!!(A & 0x01));
				A = (A >> 1) | (tempC << 7);
				setFlagsZN(A);
				break;
			}
			default: {
				u16 address = getAddressFromType(addrmode, PC);
				u8 operand = MAINBUS::read(address);
				setC(operand & 0x01);
				operand = (operand >> 1) | (tempC << 7);
				setFlagsZN(operand);
				MAINBUS::write(address, operand);
				break;
			}
		}
	}

	//2A - 4 typów adresacji
	void executeDEC(u8 addrmode) {	//DEC
		u16 addr = getAddressFromType(addrmode, PC);
		u8 temp = MAINBUS::read(addr) - 1u;
		MAINBUS::write(addr, temp);
	}
	void executeINC(u8 addrmode) {	//INC
		u16 addr = getAddressFromType(addrmode, PC);
		u8 temp = MAINBUS::read(addr) + 1u;
		MAINBUS::write(addr, temp);
	}
	void executeSTX(u8 addrmode) {	//STX
		u16 addr = getAddressFromType(addrmode, PC);
		MAINBUS::write(addr, X);
		return;
	}
	void executeSTY(u8 addrmode) {	//STY
		u16 addr = getAddressFromType(addrmode, PC);
		MAINBUS::write(addr, Y);
		return;
	}

	//2B - 3 typów adresacji
	void executeCPX(u8 addrmode) {	//CPX
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC));

		u16 result = X - operand;
		//Flagi C Z i N
		setC( !(result & 0x100) );
		setFlagsZN(0xff & result);
		return;
	}
	void executeCPY(u8 addrmode) {	//CPY
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC));

		u16 result = Y - operand;
		//Flagi C Z i N
		setC( !(result & 0x100) );
		setFlagsZN(0xff & result);
		return;
	}

	//3A - 2 typów adresacji
	void executeBIT(u8 addrmode) {	//BIT
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC));

		//Na podstawie wartości otrzymanej z "operand" ustaw flagi Z V i N
		setZ(!(operand & A));
		setV(!!(operand & 0b01000000));
		setN(!!(operand & 0b10000000));
		return;
	}

	//3B - 2 typów adresacji
	void executeJMP(u8 addrmode) {	//JMP

		u16 address = getAddressFromType(addrmode, PC);
		PC = address;
		
	}

	//4 - 1 typ adresacji
	void executeBCC() {	//BCC
		executeBranch(BCC);
	}
	void executeBCS() {	//BCS
		executeBranch(BCS);
	}
	void executeBEQ() {	//BEQ
		executeBranch(BEQ);
	}
	void executeBMI() {	//BMI
		executeBranch(BMI);
	}
	void executeBNE() {	//BNE
		executeBranch(BNE);
	}
	void executeBPL() {	//BPL
		executeBranch(BPL);
	}
	void executeBRK() {	//BRK
		interrupt(BRK);
	}
	void executeBVC() {	//BVC
		executeBranch(BVC);
	}
	void executeBVS() {	//BVS
		executeBranch(BVS);
	}
	void executeCLC() {	//CLC
		clrC();
	}
	void executeCLD() {	//CLD
		clrD();
	}
	void executeCLI() {	//CLI
		clrI();
	}
	void executeCLV() {	//CLV
		clrV();
	}
	void executeDEX() {	//DEX
		X--;
		setFlagsZN(X);
	}
	void executeDEY() {	//DEY
		Y--;
		setFlagsZN(X);
	}
	void executeINX() {	//INX
		X++;
		setFlagsZN(X);
	}
	void executeINY() {	//INY
		Y++;
		setFlagsZN(Y);
	}
	void executeNOP() {	//NOP
		/* ZONK!!! Zabrałem Ci 2 cenne cykle, pracuj dalej XD */
	}
	void executePHA() {	//PHA
		MAINBUS::pushStack(A);
	}
	void executePHP() {	//PHP

		P |= 0b00010000;	//Ustawiamy pozorną flagę B na 1
		MAINBUS::pushStack(P);	//Wpychamy stan procka do stosu

	}
	void executePLA() {	//PLA
		A = MAINBUS::pullStack();
	}
	void executePLP() {	//PLP
		P = MAINBUS::pullStack();
	}
	void executeRTI() {	//RTI
		P = MAINBUS::pullStack();
		PC = MAINBUS::pullStack();
		PC |= MAINBUS::pullStack() << 8;
	}
	void executeRTS() {	//RTS
		PC = MAINBUS::pullStack() | MAINBUS::pullStack() << 8;
	}
	void executeSEC() {	//SEC
		setC();
	}
	void executeSED() {	//SED
		setD();
	}
	void executeSEI() {	//SEI
		setI();
	}
	void executeTAX() {	//TAX
		X = A;
		setFlagsZN(X);
	}
	void executeTAY() {	//TAY
		Y = A;
		setFlagsZN(Y);
	}
	void executeTSX() {	//TSX
		X = S;
		setFlagsZN(X);
	}
	void executeTXA() {	//TXA
		A = X;
		setFlagsZN(A);
	}
	void executeTXS() {	//TXS
		S = X;
	}
	void executeTYA() {	//TYA
		A = Y;
		setFlagsZN(A);
	}
	void executeJSR() {	//JSR
		MAINBUS::pushStack( (u8)( (PC + 1)>>8 ) );	//Najpierw wpychamy PC do stosu
		MAINBUS::pushStack((u8)(PC));
		PC = MAINBUS::readAddr(PC);	//Potem ustawiamy PC na wartość, którą niesie operand
	}

	//Podajesz rozkazy, otrzymujesz instrukcje!
	void disassemblyC(const char* num) {
		int stringptr = 0;
		int stringlen = strlen(num);
		int opindex;
		u8 _opcode;
		u8 _operand[2];

		while (stringptr < stringlen) {

			_opcode = 0;
			_operand[0] = 0;
			_operand[1] = 0;

			while (num[stringptr] == ' ') { stringptr++; }

			//Najpierw odczytaj jaki to opcode:
			//High nibble
			switch (num[stringptr]) {
			
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
					_opcode |= (num[stringptr] - '0') << 4; break;
				}

				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': {
					_opcode |= (num[stringptr] - 'A' + 10) << 4; break;
				}

				case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': {
					_opcode |= (num[stringptr] - 'a' + 10) << 4; break;
				}

				default: break;
	
			}
			stringptr++;

			//Low nibble
			switch (num[stringptr]) {

				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
					_opcode |= num[stringptr] - '0'; break;
				}

				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': {
					_opcode |= num[stringptr] - 'A' + 10; break;
				}

				case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': {
					_opcode |= num[stringptr] - 'a' + 10; break;
				}

				default: break;

			}
			stringptr++;

			std::cout << '\n' << getOpcodeMnemonic(_opcode) << ' ';

			int howmany = getOpcodeLength(_opcode) - 1;
			opindex = 0;

			while (howmany > 0) {

				while (num[stringptr] == ' ') { stringptr++; }
			
				//Potem odczytujemy operandy:
				//High nibble
				switch (num[stringptr]) {

				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
					_operand[opindex] += (num[stringptr] - '0') << 4; break;
				}

				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': {
					_operand[opindex] += (num[stringptr] - 'A' + 10) << 4; break;
				}

				case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': {
					_operand[opindex] += (num[stringptr] - 'a' + 10) << 4; break;
				}

				default: break;

				}
				stringptr++;

				//Low nibble
				switch (num[stringptr]) {

				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
					_operand[opindex] += (num[stringptr] - '0'); break;
				}

				case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': {
					_operand[opindex] += (num[stringptr] - 'A' + 10); break;
				}

				case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': {
					_operand[opindex] += (num[stringptr] - 'a' + 10); break;
				}

				default: break;

				}
				stringptr++;
				opindex++;
				howmany--;

				if ( howmany == 0) {
					switch (getOpcodeAddressingMode(_opcode)) {
					
					case ACCUMULATOR: {
						putchar('A'); break;
					}
					case IMMEDIATE: {
						printf("#$%02x", _operand[0]); break;
						
					}
					case RELATIVE: case ZEROPAGE: {
						printf("$%02x", _operand[0]); break;
					}
					case ZEROPAGE_X: {
						printf("$%02x,X", _operand[0]); break;
					}
					case ZEROPAGE_Y: {
						printf("$%02x,Y", _operand[0]); break;
					}
					case INDIRECT: {
						printf("($%02x%02x)", _operand[1], _operand[0]); break;
					}
					case INDIRECT_X: {
						printf("($%02x,X)", _operand[0]); break;
					}
					case INDIRECT_Y: {
						printf("($%02x),Y", _operand[0]); break;
					}
					case ABSOLUTE: {
						printf("$%02x%02x", _operand[1], _operand[0]); break;
					}
					case ABSOLUTE_X: {
						printf("$%02x%02x,X", _operand[1], _operand[0]); break;
					}
					case ABSOLUTE_Y: {
						printf("$%02x%02x,Y", _operand[1], _operand[0]); break;
					}

					default: break;

					}
				}
			}
		}
	}

	//Tutaj zaczyna się wykonywanie instrukcji (jeszcze nie wiem)
	void step() {

		if (cyclesLeft == 0) {

			u8 addrmode = getOpcodeAddressingMode(MAINBUS::read(PC));
			u16 opcode = getOpcode(MAINBUS::read(PC));

			cyclesLeft = opcodeCycle[opcode];
			PC++;

			//Wertujesz listę 
			switch (opcode) {

				//1A - 8 typów adresacji
				case ADC: {
					executeADC(addrmode); break;
				}
				case AND: {
					executeAND(addrmode); break;
				}
				case CMP: {
					executeCMP(addrmode); break;
				}
				case EOR: {
					executeEOR(addrmode); break;
				}
				case LDA: {
					executeLDA(addrmode); break;
				}
				case ORA: {
					executeORA(addrmode); break;
				}
				case SBC: {
					executeSBC(addrmode); break;
				}
				case STA: {
					executeSTA(addrmode); break;
				}
				
				//1B - 6 typów adresacji
				case ASL: {
					executeASL(addrmode); break;
				}
				case LDX: {
					executeLDX(addrmode); break;
				}
				case LDY: {
					executeLDY(addrmode); break;
				}
				case LSR: {
					executeLSR(addrmode); break;
				}
				case ROL: {
					executeROL(addrmode); break;
				}
				case ROR: {
					executeROR(addrmode); break;
				}
				
				//2A - 4 typy adresacji
				case DEC: {
					executeDEC(addrmode); break;
				}
				case INC: {
					executeINC(addrmode); break;
				}
				case STX: {
					executeSTX(addrmode); break;
				}
				case STY: {
					executeSTY(addrmode); break;
				}

				//2B - 3 typy adresacji
				case CPX: {
					executeCPX(addrmode); break;
				}
				case CPY: {
					executeCPY(addrmode); break;
				}
				
				//3A - 2 typy adresacji
				case BIT: {
					executeBIT(addrmode); break;
				}

				//3B - 2 typy adresacji
				case JMP: {
					executeJMP(addrmode); break;
				}

				//4 - 1 typ adresacji
				case BCC: case BCS: case BEQ: case BMI: case BNE: case BPL: case BVC: case BVS: {
					executeBranch(opcode); break;
				}
				case BRK: {
					interrupt(BRK); break;
				}
				case CLC: {
					clrC(); break;
				}
				case CLD: {
					clrD(); break;
				}
				case CLI: {
					clrI(); break;
				}
				case CLV: {
					clrV(); break;
				}
				case DEX: {
					executeDEX(); break;
				}
				case DEY: {
					executeDEY(); break;
				}
				case INX: {
					executeINX(); break;
				}
				case INY: {
					executeINY(); break;
				}
				case PHA: {
					executePHA(); break;
				}
				case PHP: {
					executePHP(); break;
				}
				case PLA: {
					executePLA(); break;
				}
				case PLP: {
					executePLP(); break;
				}
				case RTI: {
					executeRTI(); break;
				}
				case RTS: {
					executeRTS(); break;
				}
				case SEC: {
					setC(); break;
				}
				case SED: {
					setD(); break;
				}
				case SEI: {
					setI(); break;
				}
				case TAX: {
					executeTAX(); break;
				}
				case TAY: {
					executeTAY(); break;
				}
				case TSX: {
					executeTSX(); break;
				}
				case TXA: {
					executeTXA(); break;
				}
				case TXS: {
					executeTXS(); break;
				}
				case TYA: {
					executeTYA(); break;
				}
				case JSR: {
					executeJSR(); break;
				}

				default: {
					break;
				}
			}

			PC += getOpcodeLength(opcode) - 1;
		}

		if (cyclesLeft > 0) cyclesLeft--;
	}

}

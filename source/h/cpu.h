#pragma once

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

	u16 getOpcodeMnemonicCode(u8 opcode) {

		switch (opcode) {

		case ADC_ABS: case ADC_ABS_X: case ADC_ABS_Y: case ADC_IMM: case ADC_IND_X: case ADC_IND_Y: case ADC_ZP: case ADC_ZP_X: {
			return ADC;
		}

		case AND_ABS: case AND_ABS_X: case AND_ABS_Y: case AND_IMM: case AND_IND_X: case AND_IND_Y: case AND_ZP: case AND_ZP_X: {
			return AND;
		}

		case ASL_ABS: case ASL_ABS_X: case ASL_ACC: case ASL_ZP: case ASL_ZP_X: {
			return ASL;
		}

		case BIT_ABS: case BIT_ZP: {
			return BIT;
		}

		case CMP_ABS: case CMP_ABS_X: case CMP_ABS_Y: case CMP_IMM: case CMP_IND_X: case CMP_IND_Y: case CMP_ZP: case CMP_ZP_X: {
			return CMP;
		}

		case CPX_ABS: case CPX_IMM: case CPX_ZP: {
			return CPX;
		}

		case CPY_ABS: case CPY_IMM: case CPY_ZP: {
			return CPY;
		}

		case DEC_ABS: case DEC_ABS_X: case DEC_ZP: case DEC_ZP_X: {
			return DEC;
		}

		case EOR_ABS: case EOR_ABS_X: case EOR_ABS_Y: case EOR_IMM: case EOR_IND_X: case EOR_IND_Y: case EOR_ZP: case EOR_ZP_X: {
			return EOR;
		}

		case INC_ABS: case INC_ABS_X: case INC_ZP: case INC_ZP_X: {
			return INC;
		}

		case JMP_ABS: case JMP_IND: {
			return JMP;
		}

		case LDA_ABS: case LDA_ABS_X: case LDA_ABS_Y: case LDA_IMM: case LDA_IND_X: case LDA_IND_Y: case LDA_ZP: case LDA_ZP_X: {
			return LDA;
		}

		case LDX_ABS: case LDX_ABS_Y: case LDX_IMM: case LDX_ZP: case LDX_ZP_Y: {
			return LDX;
		}

		case LDY_ABS: case LDY_ABS_X: case LDY_IMM: case LDY_ZP: case LDY_ZP_X: {
			return LDY;
		}

		case LSR_ABS: case LSR_ABS_X: case LSR_ACC: case LSR_ZP: case LSR_ZP_X: {
			return LSR;
		}

		case ORA_ABS: case ORA_ABS_X: case ORA_ABS_Y: case ORA_IMM: case ORA_IND_X: case ORA_IND_Y: case ORA_ZP: case ORA_ZP_X: {
			return ORA;
		}

		case ROL_ABS: case ROL_ABS_X: case ROL_ACC: case ROL_ZP: case ROL_ZP_X: {
			return ROL;
		}

		case ROR_ABS: case ROR_ABS_X: case ROR_ACC: case ROR_ZP: case ROR_ZP_X: {
			return ROR;
		}

		case SBC_ABS: case SBC_ABS_X: case SBC_ABS_Y: case SBC_IMM: case SBC_IND_X: case SBC_IND_Y: case SBC_ZP: case SBC_ZP_X: {
			return SBC;
		}

		case STA_ABS: case STA_ABS_X: case STA_ABS_Y: case STA_IND_X: case STA_IND_Y: case STA_ZP: case STA_ZP_X: {
			return STA;
		}

		case STX_ABS: case STX_ZP: case STX_ZP_Y: {
			return STX;
		}

		case STY_ABS: case STY_ZP: case STY_ZP_X: {
			return STY;
		}

		default: {
			return opcode;
		}

		}

	}

	void init() {

		A = 0;
		X = 0;
		Y = 0;

		MEM::init();
		PC = MAINBUS::readAddr(MEM::reset);
		oddCycle = 1;
		S = 0xfd;
		P = 0b00110100;
		NMIoccured = 0;
		readyForNMI = 0;
		cycles = 0;
		APUelapsed = 0;
		APU::reset(tvregion == PAL);

	}

	void power() {
		P = 0x34;
		S = 0xfd;
		A = 0;
		X = 0;
		Y = 0;
		NMIoccured = 0;
		readyForNMI = 0;
		cycles = 0;
		oddCycle = 1;
		APUelapsed = 0;
		APU::reset(tvregion == PAL);
		PC = MAINBUS::readAddr(MEM::reset);
	}

	void reset() {
		P |= 0x04;
		S -= 3;
		APU::reset(tvregion == PAL);
		PC = MAINBUS::readAddr(MEM::reset);
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

		switch (opcode) {

		//INDIRECT_X
		/*1*/ case ADC_IND_X: case AND_IND_X: case CMP_IND_X: case EOR_IND_X: case LDA_IND_X: case ORA_IND_X: case SBC_IND_X: case STA_IND_X:
		/*2*/
		/*3*/
		/*4*/
		/*5*/
		/*6*/
		{
			return INDIRECT_X;
		}

		//ZEROPAGE
		/*1*/ case ADC_ZP: case AND_ZP: case CMP_ZP: case EOR_ZP: case LDA_ZP: case ORA_ZP: case SBC_ZP: case STA_ZP:
		/*2*/ case ASL_ZP: case LDX_ZP: case LDY_ZP: case LSR_ZP: case ROL_ZP: case ROR_ZP:
		/*3*/ case DEC_ZP: case INC_ZP: case STX_ZP: case STY_ZP:
		/*4*/ case CPX_ZP: case CPY_ZP:
		/*5*/ case BIT_ZP:
		/*6*/
		{
			return ZEROPAGE;
		}

		//IMMEDIATE
		/*1*/ case ADC_IMM: case AND_IMM: case CMP_IMM: case EOR_IMM: case LDA_IMM: case ORA_IMM: case SBC_IMM:
		/*2*/               case LDX_IMM: case LDY_IMM:
		/*3*/
		/*4*/ case CPX_IMM: case CPY_IMM:
		/*5*/
		/*6*/
		{
			return IMMEDIATE;
		}

		//ABSOLUTE
		/*1*/ case ADC_ABS: case AND_ABS: case CMP_ABS: case EOR_ABS: case LDA_ABS: case ORA_ABS: case SBC_ABS: case STA_ABS:
		/*2*/ case ASL_ABS: case LDX_ABS: case LDY_ABS: case LSR_ABS: case ROL_ABS: case ROR_ABS:
		/*3*/ case DEC_ABS: case INC_ABS: case STX_ABS: case STY_ABS:
		/*4*/ case CPX_ABS: case CPY_ABS:
		/*5*/ case BIT_ABS:
		/*6*/ case JMP_ABS:
		/*7*/ case JSR:
		{
			return ABSOLUTE;
		}

		//INDIRECT_Y
		/*1*/ case ADC_IND_Y: case AND_IND_Y: case CMP_IND_Y: case EOR_IND_Y: case LDA_IND_Y: case ORA_IND_Y: case SBC_IND_Y: case STA_IND_Y:
		/*2*/
		/*3*/
		/*4*/
		/*5*/
		/*6*/
		{
			return INDIRECT_Y;
		}

		//ZEROPAGE_X
		/*1*/ case ADC_ZP_X: case AND_ZP_X: case CMP_ZP_X: case EOR_ZP_X: case LDA_ZP_X: case ORA_ZP_X: case SBC_ZP_X: case STA_ZP_X:
		/*2*/ case ASL_ZP_X:                case LDY_ZP_X: case LSR_ZP_X: case ROL_ZP_X: case ROR_ZP_X:
		/*3*/ case DEC_ZP_X: case INC_ZP_X:                case STY_ZP_X:
		/*4*/
		/*5*/
		/*6*/
		{
			return ZEROPAGE_X;
		}

		//ZEROPAGE_Y
		/*1*/
		/*2*/                case LDX_ZP_Y:
		/*3*/                               case STX_ZP_Y:
		/*4*/
		/*5*/
		/*6*/
		{
			return ZEROPAGE_Y;
		}

		//ABSOLUTE_Y
		/*1*/ case ADC_ABS_Y: case AND_ABS_Y: case CMP_ABS_Y: case EOR_ABS_Y: case LDA_ABS_Y: case ORA_ABS_Y: case SBC_ABS_Y: case STA_ABS_Y:
		/*2*/                 case LDX_ABS_Y:
		/*3*/
		/*4*/
		/*5*/
		/*6*/
		{
			return ABSOLUTE_Y;
		}

		//ABSOLUTE_X
		/*1*/ case ADC_ABS_X: case AND_ABS_X: case CMP_ABS_X: case EOR_ABS_X: case LDA_ABS_X: case ORA_ABS_X: case SBC_ABS_X: case STA_ABS_X:
		/*2*/ case ASL_ABS_X:                 case LDY_ABS_X: case LSR_ABS_X: case ROL_ABS_X: case ROR_ABS_X:
		/*3*/ case DEC_ABS_X: case INC_ABS_X:
		/*4*/
		/*5*/
		/*6*/
		{
			return ABSOLUTE_X;
		}

		//ACCUMULATOR
		/*1*/
		/*2*/ case ASL_ACC:                             case LSR_ACC: case ROL_ACC: case ROR_ACC:
		/*3*/
		/*4*/
		/*5*/
		/*6*/
		{
			return ACCUMULATOR;
		}

		//INDIRECT
		/*1*/
		/*2*/
		/*3*/
		/*4*/
		/*5*/
		/*6*/ case JMP_IND:
		{
			return INDIRECT;
		}

		//RELATIVE
		case BCC: case BCS: case BEQ: case BMI: case BNE: case BPL: case BVC: case BVS:
		{
			return RELATIVE;
		}

		//IMPLIED
		case BRK: case CLC: case CLD: case CLI: case CLV: case DEX: case DEY: case INX: case INY: case NOP: case PHA: case PHP: case PLA: case PLP: case RTI: case RTS: case SEC: case SED: case SEI: case TAX: case TAY: case TSX: case TXA: case TXS: case TYA:
		{
			return IMPLIED;
		}

		default: {
			return ADDRMODE_ERROR;
		}


		}
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
			if (opcode == BRK) return 2;
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
			return 1;
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

	//Ta funkcja sprawdza, czy zosta³a przekroczona strona. Jeœli tak, dodaj +1 do cyklu
	void checkPageCross(u16 pagea, u16 pageb, u8 value) {

		if ((pagea & 0xff00) != (pageb & 0xff00)) {
			cyclesLeft += value; //Je¿eli strona zostanie przkroczona, dodaj +value do cyklu
		}
	}

	//Ustaw flagi Z i N w zale¿noœci od podanego parametru
	void setFlagsZN(u8 value) {
		setZ(!value);
		setN(!!(value & 0x80));
	}

	//Zwraca wartoœæ flagi
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

	//Ustaw flagê na 1
	void setC() {
		P = P | 0b00000001;
	}
	void setZ() {
		P = P | 0b00000010;
	}
	void setI() {
		P = P | 0b00000100;
	}
	void setD() {
		P = P | 0b00001000;
	}
	void setV() {
		P = P | 0b01000000;
	}
	void setN() {
		P = P | 0b10000000;
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

	//Ustaw flagê w zale¿noœci od parametru
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

	//Wyczyœæ flagê
	void clrC() {
		P = P & 0b11111110;
	}
	void clrZ() {
		P = P & 0b11111101;
	}
	void clrI() {
		P = P & 0b11111011;
	}
	void clrD() {
		P = P & 0b11110111;
	}
	void clrV() {
		P = P & 0b10111111;
	}
	void clrN() {
		P = P & 0b01111111;
	}

	//Zrób przerwanie
	void interrupt(u8 int_type) {

		if (getI() && int_type != INT_NMI && int_type != INT_BRK) return;

		if (int_type == INT_BRK) PC++;

		// Wepchnij aktualny wskaŸnik programu do stosu
		MAINBUS::pushStack(PC >> 8);
		MAINBUS::pushStack(0xff & PC);

		// Je¿eli BRK, ustawiamy pozorn¹ flagê B na 1
		u8 tempP = (P & 0b11101111) | ((int_type == INT_BRK) << 4) | 0b00100000;

		// Wpychamy status procka do stosu
		MAINBUS::pushStack(tempP);

		setI();

		switch (int_type) {
		case INT_NMI: {
			PC = MAINBUS::readAddr(MEM::NMI);
			break;
		}
		case INT_IRQ:
		case INT_BRK: {
			PC = MAINBUS::readAddr(MEM::IRQ);
			break;
		}

		}
		if (int_type != INT_BRK) cyclesLeft += 7;
	}

	//Jak na podstawie typu opokdu pobraæ dane z operandu?
	//Na podstawie typu adresowania oraz danego operandu, zwraca adres danej wartoœci w pamiêci
	u16 getAddressFromType(u8 addrmode, u16 pointer, u8 addCycleOnBoundCross) {

		switch (addrmode) {

			case ABSOLUTE: {
				return MAINBUS::read(pointer) | MAINBUS::read(pointer + 1) << 8;
			}
			case ABSOLUTE_X: {
				u16 address = (MAINBUS::read(pointer) | (MAINBUS::read(pointer + 1) << 8));
				checkPageCross(address, address + X, addCycleOnBoundCross);
				return (address + X);
			}
			case ABSOLUTE_Y: {
				u16 address = (MAINBUS::read(pointer) | (MAINBUS::read(pointer + 1) << 8));
				checkPageCross(address, address + Y, addCycleOnBoundCross);
				return (address + Y);
			}
			case IMMEDIATE: {
				return pointer;
			}
			case ZEROPAGE: {
				return MAINBUS::read(pointer);
			}
			case ZEROPAGE_X: {
				return (MAINBUS::read(pointer) + X) & 0xff;
			}
			case ZEROPAGE_Y: {
				return (MAINBUS::read(pointer) + Y) & 0xff;
			}
			case INDIRECT: {
				//INDIRECT u¿ywa jedynie instrukcja JMP
				u16 address = MAINBUS::readAddr(pointer);
				u16 page = address & 0xff00;
				//u8 polo = MAINBUS::read(pointer);
				//u8 pohi = MAINBUS::read(pointer + 1);

				//Typ INDIRECT posiada bardzo specyficznego buga: Nie potrafi przekraczaæ stron.
				//Przyk³ad: Je¿eli jako operand mamy (Adresik) i pierwsze 2 bity od adresu "Adresik" to np. $24FF to MSB pobierze ju¿ nie z $2500 a z $2400.

				return MAINBUS::read(address) | MAINBUS::read(page | ((address + 1) & 0xff)) << 8;
				//return MAINBUS::read(polo | (pohi << 8)) | (MAINBUS::read((polo + 1) | (pohi << 8)) << 8);

			}
			case INDIRECT_X: {
				u8 val = MAINBUS::read(pointer) + X;
				return MAINBUS::read(val & 0xff) | (MAINBUS::read((val + 1) & 0xff) << 8);
				//return pointer;
				//return (MAINBUS::read(pointer) + X) & 0xff;
			}
			case INDIRECT_Y: {
				u8 val = MAINBUS::read(pointer);
				u16 address = MAINBUS::read(val & 0xff) | (MAINBUS::read((val + 1) & 0xff) << 8) ;
				checkPageCross(address, address + Y, addCycleOnBoundCross);
				return (address + Y);
			}
		}

		return pointer;
	}



	void executeBranch(u8 branch_type) {
		u8 br = 0;

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
			u16 PC2 = PC + off;

			checkPageCross(PC, PC2, 1);

			cyclesLeft++;
			PC = PC2;
		}
	}


	//Definicje zadañ dla instrukcji
	//1A - 8 typów adresacji
	void executeADC(u8 addrmode) {	//ADC

		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC, 1));

		u16 sum = A + operand + getC();
		setC(!!(sum & 0x100));
		setV(!!((A ^ sum) & (operand ^ sum) & 0x80));
		A = 0xff & sum;

		setFlagsZN(A);
	}
	void executeAND(u8 addrmode) { //AND
		A &= MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(A);
	}
	void executeCMP(u8 addrmode) { //CMP
		u16 diff = A - MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setC(!(diff & 0x100));
		setFlagsZN(0xff & diff);
	}
	void executeEOR(u8 addrmode) { //EOR
		A ^= MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(A);
	}
	void executeLDA(u8 addrmode) { //LDA
		A = MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(A);
	}
	void executeORA(u8 addrmode) { //ORA
		A |= MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(A);
	}
	void executeSBC(u8 addrmode) { //SBC

		u16 operand = MAINBUS::read(getAddressFromType(addrmode, PC, 1));

		u16 diff = A - operand - !getC();

		setC( !(diff & 0x100) );
		setV( !!((A ^ diff) & (~operand ^ diff) & 0x80) );
		A = 0xff & diff;

		setFlagsZN(A);
	}
	void executeSTA(u8 addrmode) { //STA
		MAINBUS::write(getAddressFromType(addrmode, PC, 0), A);
	}

	//1B - 6 typów adresacji
	void executeASL(u8 addrmode) {	//ASL

		if (addrmode == ACCUMULATOR) {
			setC(!!(A & 0x80));
			A <<= 1;
			setFlagsZN(A);
		} else {
			u16 address = getAddressFromType(addrmode, PC, 0);
			u8 operand = MAINBUS::read(address);
			setC(!!(operand & 0x80));
			operand = operand << 1;
			setFlagsZN(operand);
			MAINBUS::write(address, operand);
		}

	}
	void executeLDX(u8 addrmode) { //LDX
		X = MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(X);
	}
	void executeLDY(u8 addrmode) { //LDY
		Y = MAINBUS::read(getAddressFromType(addrmode, PC, 1));
		setFlagsZN(Y);
	}
	void executeLSR(u8 addrmode) {	//LSR

		if (addrmode == ACCUMULATOR) {
			setC(!!(A & 0x01));
			A = A >> 1;
			setFlagsZN(A);
		} else {
			u16 address = getAddressFromType(addrmode, PC, 0);
			u8 operand = MAINBUS::read(address);
			setC(!!(operand & 0x01));
			operand = operand >> 1;
			setFlagsZN(operand);
			MAINBUS::write(address, operand);
		}

	}
	void executeROL(u8 addrmode) {	//ROL

		if (addrmode == ACCUMULATOR) {
			u8 tempC = getC();
			setC(!!(A & 0x80));
			A = (A << 1) | tempC;
			setFlagsZN(A);
		} else {
			u8 tempC = getC();
			u16 address = getAddressFromType(addrmode, PC, 0);
			u8 operand = MAINBUS::read(address);
			setC(!!(operand & 0x80));
			operand = (operand << 1) | tempC;
			setFlagsZN(operand);
			MAINBUS::write(address, operand);
		}

	}
	void executeROR(u8 addrmode) {	//ROR

		if(addrmode == ACCUMULATOR) {

			u8 tempC = getC();
			setC(!!(A & 0x01));
			A = (A >> 1) | (tempC << 7);
			setFlagsZN(A);
		} else {
			u8 tempC = getC();
			u16 address = getAddressFromType(addrmode, PC, 0);
			u8 operand = MAINBUS::read(address);
			setC(!!(operand & 0x01));
			operand = (operand >> 1) | (tempC << 7);
			setFlagsZN(operand);
			MAINBUS::write(address, operand);
		}

	}

	//2A - 4 typów adresacji
	void executeDEC(u8 addrmode) {	//DEC
		u16 addr = getAddressFromType(addrmode, PC, 0);
		u8 temp = MAINBUS::read(addr) - 0x01;
		setFlagsZN(temp);
		MAINBUS::write(addr, temp);
	}
	void executeINC(u8 addrmode) {	//INC
		u16 addr = getAddressFromType(addrmode, PC, 0);
		u8 temp = MAINBUS::read(addr) + 0x01;
		setFlagsZN(temp);
		MAINBUS::write(addr, temp);
	}
	void executeSTX(u8 addrmode) {	//STX
		u16 addr = getAddressFromType(addrmode, PC, 0);
		MAINBUS::write(addr, X);
		return;
	}
	void executeSTY(u8 addrmode) {	//STY
		u16 addr = getAddressFromType(addrmode, PC, 0);
		MAINBUS::write(addr, Y);
		return;
	}

	//2B - 3 typów adresacji
	void executeCPX(u8 addrmode) {	//CPX
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC, 0));

		u16 result = X - operand;
		//Flagi C Z i N
		setC( !(result & 0x100) );
		setFlagsZN(0xff & result);
		return;
	}
	void executeCPY(u8 addrmode) {	//CPY
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC, 0));

		u16 result = Y - operand;
		//Flagi C Z i N
		setC( !(result & 0x100) );
		setFlagsZN(0xff & result);
		return;
	}

	//3A - 2 typów adresacji
	void executeBIT(u8 addrmode) {	//BIT
		u8 operand = MAINBUS::read(getAddressFromType(addrmode, PC, 0));

		//Na podstawie wartoœci otrzymanej z "operand" ustaw flagi Z V i N
		setZ(!(A & operand));
		setV(!!(operand & 0b01000000));
		setN(!!(operand & 0b10000000));
		return;
	}

	//3B - 2 typów adresacji
	void executeJMP(u8 addrmode) {	//JMP

		u16 address = getAddressFromType(addrmode, PC, 0);
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
		interrupt(INT_BRK);
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
		--X;
		setFlagsZN(X);
	}
	void executeDEY() {	//DEY
		--Y;
		setFlagsZN(Y);
	}
	void executeINX() {	//INX
		++X;
		setFlagsZN(X);
	}
	void executeINY() {	//INY
		++Y;
		setFlagsZN(Y);
	}
	void executeNOP() {	//NOP
		/* ZONK!!! Zabra³em Ci 2 cenne cykle, pracuj dalej XD */
	}
	void executePHA() {	//PHA
		MAINBUS::pushStack(A);
	}
	void executePHP() {	//PHP
		u8 tempP = P;
		tempP = tempP | 0b00110000;	//Ustawiamy pozorn¹ flagê B na 1
		MAINBUS::pushStack(tempP);	//Wpychamy stan procka do stosu

	}
	void executePLA() {	//PLA
		A = MAINBUS::pullStack();
		setFlagsZN(A);
	}
	void executePLP() {	//PLP
		u8 tempP = MAINBUS::pullStack();
		setC(!!(tempP & 0b00000001));
		setZ(!!(tempP & 0b00000010));
		setI(!!(tempP & 0b00000100));
		setD(!!(tempP & 0b00001000));
		setV(!!(tempP & 0b01000000));
		setN(!!(tempP & 0b10000000));
	}
	void executeRTI() {	//RTI
		u8 tempP = MAINBUS::pullStack();

		setC(!!(tempP & 0b00000001));
		setZ(!!(tempP & 0b00000010));
		setI(!!(tempP & 0b00000100));
		setD(!!(tempP & 0b00001000));
		setV(!!(tempP & 0b01000000));
		setN(!!(tempP & 0b10000000));

		PC = MAINBUS::pullStack();
		PC |= MAINBUS::pullStack() << 8;
	}
	void executeRTS() {	//RTS
		PC = (MAINBUS::pullStack() | MAINBUS::pullStack() << 8) + 1;
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
		MAINBUS::pushStack( (0xff00 & (PC + 1)) >> 8 );	//Najpierw wpychamy PC do stosu
		MAINBUS::pushStack(0x00ff & (PC + 1));
		PC = MAINBUS::readAddr(PC);	//Potem ustawiamy PC na wartoœæ, któr¹ niesie operand
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

			putchar('\n'); puts(getOpcodeMnemonic(_opcode));

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

	void step() {

		if (!getI() && (APU::irqBefore() == APUelapsed)) {
			IRQoccured = 1;
		}

		//if (!getI() && APU::earliest_irq_before(29781) <= APUelapsed) {
		//	IRQoccured = 1;
		//}

		cycles++;

		#ifdef DEBUG_MODE
		printf("\nCPU Cycle!");
		#endif

		if (cyclesLeft == 0) {

			if (readyForNMI == 1) {
				readyForNMI = 0;
				//NMIoccured = 0;
				interrupt(INT_NMI);
				#ifdef DEBUG_MODE
				printf(" NMI occured @ Dot=%d Scanline=%d", PPU::dot, PPU::scanline);
				#endif
			}
			else if (IRQoccured == 1) {
				IRQoccured = 0;
				interrupt(INT_IRQ);
				#ifdef DEBUG_MODE
				printf(" IRQ occured @ Dot=%d Scanline=%d", PPU::dot, PPU::scanline);
				#endif
			}
			else {

				u8 op = MAINBUS::read(PC);

				u8 addrmode = getOpcodeAddressingMode(op);
				u16 opcode = getOpcodeMnemonicCode(op);

				#ifdef DEBUG_MODE
				u8 opr1 = MAINBUS::read(PC + 1);
				u8 opr2 = MAINBUS::read(PC + 2);
				printf(" Opcode=%02x", op);
				switch (getOpcodeLength(op)) {
					case 2: {
						printf(" Operands=%02x", opr1);
						break;
					}
					case 3: {
						printf(" Operands=%02x%02x", opr2, opr1);
						break;
					}
				}

				printf(" (%s %s, %d length, %d cycles) @ PC=%04x (pointing at %04x)", getOpcodeMnemonic(op), getOpcodeAddressingModeName(op), getOpcodeLength(op), opcodeCycle[op], PC, getAddressFromType(addrmode, PC+1, 0));
				#endif

				//cyclesLeft = opcodeCycle[op];
				PC++;

				//Wertujesz listê
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
						executeBranch(0xff & opcode); break;
					}
					case BRK: {
						interrupt(INT_BRK); break;
					}
					case CLC: {
						executeCLC(); break;
					}
					case CLD: {
						executeCLD(); break;
					}
					case CLI: {
						executeCLI(); break;
					}
					case CLV: {
						executeCLV(); break;
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
						executeSEC(); break;
					}
					case SED: {
						executeSED(); break;
					}
					case SEI: {
						executeSEI(); break;
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


				if (opcode != JSR && opcode != JMP && opcode != BRK) { PC += getOpcodeLength(op) - 1; }

				cyclesLeft += opcodeCycle[op];
				#ifdef DEBUG_MODE
				printf(" A=%02x X=%02x Y=%02x S=%02x C=%x Z=%x I=%x D=%x B=%x V=%x N=%x", A, X, Y, S, (P & 1) >> 0, (P & 2) >> 1, (P & 4) >> 2, (P & 8) >> 3, (P & 16) >> 4, (P & 64) >> 6, (P & 128) >> 7);

				/*puts("\nSTACK:");
				for (int i = 0; i < 0x10; i++) {
					for (int j = 0; j < 0x10; j++) {
						printf("%02x  ", MEM::RAM[0x0100 + 0x10 * i + j]);
					}
					putchar('\n');
				}*/
				#endif
			}

			if (NMIoccured == 1) {
				readyForNMI = 1;
				NMIoccured = 0;
			}

		} else {



		#ifdef DEBUG_MODE
		printf(" Still executing...");
		#endif

		}

		if (cyclesLeft > 0) cyclesLeft--;
		oddCycle = !oddCycle;

		APUelapsed++;

	}

}

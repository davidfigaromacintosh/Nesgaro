// Wszystkie "legalne" instrukcje mikroprocesora Ricol 2A03
#define	ADC_IMM		0x69	//Add With Carry Immediate
#define	ADC_ZP		0x65	//Add With Carry Zero-Page
#define	ADC_ZP_X	0x75	//Add With Carry Zero-Page X
#define	ADC_ABS		0x6d	//Add With Carry Absolute
#define	ADC_ABS_X	0x7d	//Add With Carry Absolute X
#define	ADC_ABS_Y	0x79	//Add With Carry Absolute Y
#define	ADC_IND_X	0x61	//Add With Carry Indexed Indirect (X)
#define	ADC_IND_Y	0x71	//Add With Carry Indirect Indexed (Y)
#define	AND_IMM		0x29	//AND
#define	AND_ZP		0x25
#define	AND_ZP_X	0x35
#define	AND_ABS		0x2d
#define	AND_ABS_X	0x3d
#define	AND_ABS_Y	0x39
#define	AND_IND_X	0x21
#define	AND_IND_Y	0x31
#define	ASL_ACC		0x0a	//ASL
#define	ASL_ZP		0x06
#define	ASL_ZP_X	0x16
#define	ASL_ABS		0x0e
#define	ASL_ABS_X	0x1e
#define	BIT_ZP		0x24	//BIT
#define	BIT_ABS		0x2c
#define	BPL			0x10	//Branches
#define	BMI			0x30
#define	BVC			0x50
#define	BVS			0x70
#define	BCC			0x90
#define	BCS			0xb0
#define	BNE			0xd0
#define	BEQ			0xf0
#define BRK			0x00	//Break
#define	CMP_IMM		0xc9	//CMP
#define	CMP_ZP		0xc5
#define	CMP_ZP_X	0xd5
#define	CMP_ABS		0xcd
#define	CMP_ABS_X	0xdd
#define	CMP_ABS_Y	0xd9
#define	CMP_IND_X	0xc1
#define	CMP_IND_Y	0xd1
#define	CPX_IMM		0xe0	//CPX
#define	CPX_ZP		0xe4
#define	CPX_ABS		0xec
#define	CPY_IMM		0xc0	//CPY
#define	CPY_ZP		0xc4
#define	CPY_ABS		0xcc
#define	DEC_ZP		0xc6	//DEC
#define	DEC_ZP_X	0xd6
#define	DEC_ABS		0xce
#define	DEC_ABS_X	0xde
#define EOR_IMM		0x49	//EOR
#define EOR_ZP		0x45
#define EOR_ZP_X	0x55
#define EOR_ABS		0x4d
#define EOR_ABS_X	0x5d
#define EOR_ABS_Y	0x59
#define EOR_IND_X	0x41
#define EOR_IND_Y	0x51
#define	CLC			0x18	//Flagi
#define	SEC			0x38
#define	CLI			0x58
#define	SEI			0x78
#define	CLV			0xb8
#define	CLD			0xd8
#define	SED			0xf8
#define	INC_ZP		0xe6	//INC
#define	INC_ZP_X	0xf6
#define	INC_ABS		0xee
#define	INC_ABS_X	0xfe
#define JMP_ABS		0x4c	//JMP
#define JMP_IND		0x6c
#define	JSR			0x20	//JSR
#define LDA_IMM		0xa9	//LDA
#define	LDA_ZP		0xa5
#define LDA_ZP_X	0xb5
#define LDA_ABS		0xad
#define LDA_ABS_X	0xbd
#define LDA_ABS_Y	0xb9
#define LDA_IND_X	0xa1
#define LDA_IND_Y	0xb1
#define LDX_IMM		0xa2	//LDX
#define	LDX_ZP		0xa6
#define LDX_ZP_Y	0xb6
#define LDX_ABS		0xae
#define LDX_ABS_Y	0xbe
#define LDY_IMM		0xa0	//LDY
#define	LDY_ZP		0xa4
#define LDY_ZP_X	0xb4
#define LDY_ABS		0xac
#define LDY_ABS_X	0xbc
#define LSR_ACC		0x4a	//LSR
#define LSR_ZP		0x46
#define LSR_ZP_X	0x56
#define LSR_ABS		0x4e
#define LSR_ABS_X	0x5e
#define NOP			0xea	//NOP
#define ORA_IMM		0x09	//ORA
#define ORA_ZP		0x05
#define ORA_ZP_X	0x15
#define ORA_ABS		0x0d
#define ORA_ABS_X	0x1d
#define ORA_ABS_Y	0x19
#define ORA_IND_X	0x01
#define ORA_IND_Y	0x11
#define TAX			0xaa	//Instrukcje rejestr�w
#define TXA			0x8a
#define	DEX			0xca
#define	INX			0xe8
#define	TAY			0xa8
#define	TYA			0x98
#define	DEY			0x88
#define	INY			0xc8
#define ROL_ACC		0x2a	//ROL
#define ROL_ZP		0x26
#define ROL_ZP_X	0x36
#define ROL_ABS		0x2e
#define ROL_ABS_X	0x3e
#define ROR_ACC		0x6a	//ROR
#define ROR_ZP		0x66
#define ROR_ZP_X	0x76
#define ROR_ABS		0x6e
#define ROR_ABS_X	0x7e
#define RTI			0x40	//RTI
#define RTS			0x60	//RTS
#define SBC_IMM		0xe9	//SBC
#define SBC_ZP		0xe5
#define SBC_ZP_X	0xf5
#define SBC_ABS		0xed
#define SBC_ABS_X	0xfd
#define SBC_ABS_Y	0xf9
#define SBC_IND_X	0xe1
#define SBC_IND_Y	0xf1
#define STA_ZP		0x85	//STA
#define STA_ZP_X	0x95
#define STA_ABS		0x8d
#define STA_ABS_X	0x9d
#define STA_ABS_Y	0x99
#define STA_IND_X	0x81
#define STA_IND_Y	0x91
#define TXS			0x9a	//Instrukcje stosu
#define	TSX			0xba
#define	PHA			0x48
#define	PLA			0x68
#define	PHP			0x08
#define	PLP			0x28
#define STX_ZP		0x86	//STX
#define	STX_ZP_Y	0x96
#define	STX_ABS		0x8e
#define STY_ZP		0x84	//STY
#define	STY_ZP_X	0x94
#define	STY_ABS		0x8c

//Maski wszystkich "legalnych" instrukcji (PS: okaza�o si�, �e nie b�d� tego potrzebowa�, wi�c okomentowa�em)
/*
#define ADC_MASK	ADC_ABS&ADC_ABS_X&ADC_ABS_Y&ADC_IMM&ADC_IND_X&ADC_IND_Y&ADC_ZP&ADC_ZP_X	//Maska instrukcji ADC
#define AND_MASK	AND_ABS&AND_ABS_X&AND_ABS_Y&AND_IMM&ADC_IND_X&AND_IND_Y&AND_ZP&AND_ZP_X	//Maska instrukcji AND
#define ASL_MASK	ASL_ABS&ASL_ABS_X&ASL_ACC&ASL_ZP&ASL_ZP_X								//Maska instrukcji ASL
#define BIT_MASK	BIT_ABS&BIT_ZP															//Maska instrukcji BIT
#define CMP_MASK	CMP_ABS&CMP_ABS_X&CMP_ABS_Y&CMP_IMM&CMP_IND_X&CMP_IND_Y&CMP_ZP&CMP_ZP_X	//Maska instrukcji CMP
#define CPX_MASK	CPX_ABS&CPX_IMM&CPX_ZP													//Maska instrukcji CPX
#define CPY_MASK	CPY_ABS&CPY_IMM&CPY_ZP													//Maska instrukcji CPY
#define DEC_MASK	DEC_ABS&DEC_ABS_X&DEC_ZP&DEC_ZP_X										//Maska instrukcji DEC
#define EOR_MASK	EOR_ABS&EOR_ABS_X&EOR_ABS_Y&EOR_IMM&EOR_IND_X&EOR_IND_Y&EOR_ZP&EOR_ZP_X	//Maska instrukcji EOR
#define INC_MASK	INC_ABS&INC_ABS_X&INC_ZP&INC_ZP_X										//Maska instrukcji INC
#define JMP_MASK	JMP_ABS&JMP_IND															//Maska instrukcji JMP
#define LDA_MASK	LDA_ABS&LDA_ABS_X&LDA_ABS_Y&LDA_IMM&LDA_IND_X&LDA_IND_Y&LDA_ZP&LDA_ZP_X	//Maska instrukcji LDA
#define LDX_MASK	LDX_ABS&LDX_ABS_Y&LDX_IMM&LDX_ZP&LDX_ZP_Y								//Maska instrukcji LDX
#define LDY_MASK	LDY_ABS&LDY_ABS_X&LDY_IMM&LDY_ZP&LDY_ZP_X								//Maska instrukcji LDY
#define	LSR_MASK	LSR_ABS&LSR_ABS_X&LSR_ACC&LSR_ZP&LSR_ZP_X								//Maska instrukcji LSR
#define	ORA_MASK	ORA_ABS&ORA_ABS_X&ORA_ABS_Y&ORA_IMM&ORA_IND_X&ORA_IND_Y&ORA_ZP&ORA_ZP_X	//Maska instrukcji ORA
#define	ROL_MASK	ROL_ABS&ROL_ABS_X&ROL_ACC&ROL_ZP&ROL_ZP_X								//Maska instrukcji ROL
#define	ROR_MASK	ROR_ABS&ROR_ABS_X&ROR_ACC&ROR_ZP&ROR_ZP_X								//Maska instrukcji ROR
#define	SBC_MASK	SBC_ABS&SBC_ABS_X&SBC_ABS_Y&SBC_IMM&SBC_IND_X&SBC_IND_Y&SBC_ZP&SBC_ZP_X	//Maska instrukcji SBC
#define	STA_MASK	STA_ABS&STA_ABS_X&STA_ABS_Y&STA_IND_X&STA_IND_Y&STA_ZP&STA_ZP_X			//Maska instrukcji STA
#define	STX_MASK	STX_ABS&STX_ZP&STX_ZP_Y													//Maska instrukcji STX
#define STY_MASK	STY_ABS&STY_ZP&STY_ZP_X													//Maska instrukcji STY
*/

#define ADC 0x100
#define AND	0x101
#define ASL	0x102
#define BIT	0x103
#define CMP	0x104
#define CPX	0x105
#define CPY	0x106
#define DEC	0x107
#define EOR	0x108
#define INC	0x109
#define JMP	0x10a
#define LDA	0x10b
#define LDX	0x10c
#define LDY	0x10d
#define	LSR	0x10e
#define	ORA	0x10f
#define	ROL	0x110
#define	ROR	0x111
#define	SBC	0x112
#define	STA	0x113
#define	STX	0x114
#define STY	0x115
#define ILL	0x200

//Grupy bit�w (maska grupy 4 to po prostu 0 wi�c nie definiujemy)
#define _1A_MASK	0b00011100	//Maska grupy 1A
#define _1B_MASK	0b00011100	//Maska grupy 1B
#define _2A_MASK	0b00011000	//Maska grupy 2A
#define _2B_MASK	0b00001100	//Maska grupy 2B
#define _3A_MASK	0b00001000	//Maska grupy 3A
#define _3B_MASK	0b00100000	//Maska grupy 3B

//Nieindeksowane, nie wymagaj� dost�pu do pami�ci
#define ACCUMULATOR	0	//Accumulator
#define IMMEDIATE	1	//Immediate
#define IMPLIED		2	//Implied

//Nieindeksowane, wymagaj� dost�pu do pami�ci
#define RELATIVE	3	//Relative
#define ABSOLUTE	4	//Absolute
#define ZEROPAGE	5	//Zero-Page
#define INDIRECT	6	//indirect

//Indeksowane, wymagaj� dost�pu do pami�ci
#define ABSOLUTE_X	7	//Absolute X
#define	ABSOLUTE_Y	8	//Absolute Y
#define ZEROPAGE_X	9	//Zero-Page X
#define ZEROPAGE_Y	10	//Zero-Page Y
#define INDIRECT_X	11	//Indexed Indirect (X)
#define	INDIRECT_Y	12	//Indirect Indexed (Y)

#define ADDRMODE_ERROR 13 //B��d odczytu trybu adresowania lub nielegalna instrukcja

/*
Wszystkie potrzebne informacje znalaz�em tu:
http://www.emulator101.com/6502-addressing-modes.html
https://www.cs.otago.ac.nz/cosc243/pdf/6502Poster.pdf
https://www.atarimax.com/jindroush.atari.org/aopc.html
https://link.springer.com/content/pdf/bbm%3A978-1-349-07360-3%2F1.pdf
http://www.thealmightyguru.com/Games/Hacking/Wiki/index.php/6502_Opcodes

Architektura mikroprocesora Ricoh 2A03 jest prawie identyczna jak
architektura mikroprocesora MOS Technology 6502 z jednym wyj�tkiem:
Ricoh 2A03 nie wspiera trybu dziesi�tnego.
*/

//Mikroprocesor Ricol 2A03
namespace CPU {

	u8 A;	//Akumulator
	u8 X;	//Rejestr X
	u8 Y;	//Rejsetr Y
	u8 P;	//Flagi C, Z, I, D, flaga czwarta i pi�ta s� pozorne, V, N
	u8 S;	//Wska�nik stosu
	u16 PC;	//Wska�nik programu
	u64 cycles; //Licznik cykli	

	//Wska�nik do �a�cucha znak�w zawieraj�cego mnemoniki wszystkich 256 instrukcji (nielegalne instrukcje zosta�y nazwane "ILL")
	u16 opcodeMnemonic[256] = { /*

			00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F	/*
	00	*/	BRK, ORA, ILL, ILL, ILL, ORA, ASL, ILL, PHP, ORA, ASL, ILL, ILL, ORA, ASL, ILL,	/*
	10	*/	BPL, ORA, ILL, ILL, ILL, ORA, ASL, ILL, CLC, ORA, ILL, ILL, ILL, ORA, ASL, ILL,	/*
	20	*/	JSR, AND, ILL, ILL, BIT, AND, ROL, ILL, PLP, AND, ROL, ILL, BIT, AND, ROL, ILL, /*
	30	*/	BMI, AND, ILL, ILL, ILL, AND, ROL, ILL, SEC, AND, ILL, ILL, ILL, AND, ROL, ILL,	/*
	40	*/	RTI, EOR, ILL, ILL, ILL, EOR, LSR, ILL, PHA, EOR, LSR, ILL, JMP, EOR, LSR, ILL,	/*
	50	*/	BVC, EOR, ILL, ILL, ILL, EOR, LSR, ILL, CLI, EOR, ILL, ILL, ILL, EOR, LSR, ILL, /*
	60	*/	RTS, ADC, ILL, ILL, ILL, ADC, ROR, ILL, PLA, ADC, ROR, ILL, JMP, ADC, ROR, ILL,	/*
	70	*/	BVS, ADC, ILL, ILL, ILL, ADC, ROR, ILL, SEI, ADC, ILL, ILL, ILL, ADC, ROR, ILL, /*
	80	*/	ILL, STA, ILL, ILL, STY, STA, STX, ILL, DEY, ILL, TXA, ILL, STY, STA, STX, ILL,	/*
	90	*/	BCC, STA, ILL, ILL, STY, STA, STX, ILL, TYA, STA, TXS, ILL, ILL, STA, ILL, ILL,	/*
	A0	*/	LDY, LDA, LDX, ILL, LDY, LDA, LDX, ILL, TAY, LDA, TAX, ILL, LDY, LDA, LDX, ILL,	/*
	B0	*/	BCS, LDA, ILL, ILL, LDY, LDA, LDX, ILL, CLV, LDA, TSX, ILL, LDY, LDA, LDX, ILL,	/*
	C0	*/	CPY, CMP, ILL, ILL, CPY, CMP, DEC, ILL, INY, CMP, DEX, ILL, CPY, CMP, DEC, ILL,	/*
	D0	*/	BNE, CMP, ILL, ILL, ILL, CMP, DEC, ILL, CLD, CMP, ILL, ILL, ILL, CMP, DEC, ILL,	/*
	E0	*/	CPX, SBC, ILL, ILL, CPX, SBC, INC, ILL, INX, SBC, NOP, ILL, CPX, SBC, INC, ILL,	/*
	F0	*/	BEQ, SBC, ILL, ILL, ILL, SBC, INC, ILL, SED, SBC, ILL, ILL, ILL, SBC, INC, ILL	/*
		*/																					};

	
	

	//Zwraca dan� instrukcj� jako identyfikator
	u16 getOpcode(u8 opcode) {
		return opcodeMnemonic[opcode];
	}

	//Zwraca wska�nik do �a�cucha znak�w z mnemonikiem danej instrukcji (nielegalna instrukcja zwr�ci mnemonik "ILL")
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

			default:  { return "???"; }
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
		//TODO gdy napisz� menedzera pami�ci
	}

	void NMI() {
		//TODO -||-
	}

/*	u8 opcodeCycle[256] = {
	
		7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
		6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
		6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
		6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
		0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
		2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
		2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
		2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
		2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
		2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 2, 4, 4, 6, 0,
		2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0
	
	};*/

	//Zawiera d�ugo�ci cykl�w wszystkich 256 instrukcji (nielegalne zwr�c� 0)
	u8 *opcodeCycle = (u8*)
	"7600035032200460250004602400047066003350422044602500046024000470660003503220346025000460240004706600035042205460250004602400047006003330202044402600444025200500262033302220444025004440242044402600335022204460250004602400047026003350222244602500046024000470";

	//Zwraca ile cykli zajmuje wykonanie danej instrukcji
	int getOpcodeCycle(u8 opcode) {
		return (int)(opcodeCycle[opcode] - '0');
	}

	/* Warto�ci zwracane przez funkcje:
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
							{ return ZEROPAGE_Y; }
						else 
							{ return ZEROPAGE_X; }
					}
					case 7: {
						if (opcode == LDX_ABS || opcode == LDX_ABS_Y || opcode == LDX_IMM || opcode == LDX_ZP || opcode == LDX_ZP_Y)
							{ return ABSOLUTE_Y; }
						else
							{ return ABSOLUTE_X; }
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
							{ return ZEROPAGE_Y; }
						else
							{ return ZEROPAGE_X; }
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

	//Wy�wietla tekst opisuj�cy tryb adresowania danej instrukcji
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
}

namespace CPU {

	//
	void execute(u16 *pointer) {
		

	}
}
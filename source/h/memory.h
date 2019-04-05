#pragma once

namespace MEM {

	//CPU
	u8 RAM[0x800];			//2 kb RAM of $0000 do $07FF

	u8 PRGRAM[0x2000];		//Od $6000 do $7FFF
	u8 PRGROM[0x8000];		//Od $8000 do $FFFF

	u8 PRGBANKS[0x8000 * 256];	//Banki danych PRG
	u8 CHRBANKS[0x2000 * 256];	//Banki danych CHR

	//PPU
	u8 VRAM[0x4000];		//16 kb VRAM
	u8 OAM[0x100];			//64*4 bajtów OAM

	//WEKTORY
	u16 NMI = 0xfffa;
	u16 reset = 0xfffc;
	u16 IRQ = 0xfffe;

	// byte 4
	u64 prgsize = 0;

	// byte 5
	u64 chrsize = 0;

	// byte 6
	u16 mapper = 0;
	u8 mirroring = 0;	//0 = hor, 1 = vert, 2 or 3 = four-screen (or 4 = no mirroring, for mappers only)
	u8 battery = 0;
	u8 trainer = 0;

	// byte 7
	u8 playchoice = 0;
	u8 nes2 = 0;

	void init() {
	
		//Sekcja RAM
		for (int i = 0; i < 0x800; i++) {
			RAM[i] = 0x00;
		}

		//Sekcja PRGRAM
		for (int i = 0; i < 0x2000; i++) {
			PRGRAM[i] = rand();
		}

		//Sekcja PRGROM
		for (int i = 0; i < 0x8000; i++) {
			PRGROM[i] = 0xff;
		}

		//Sekcja VRAM
		for (int i = 0; i < 0x4000; i++) {
			VRAM[i] = 0x00;
		}
		//Sekcja OAM
		for (int i = 0; i < 0x100; i++) {
			OAM[i] = 0xff;
		}
	}

	int loadROM(const char* filename) {

		if (strlen(filename) == 0) return 1;

		printf("ROM FIlename: %s\n", filename);

		char header[16];
		FILE* f;
		int ferror = fopen_s(&f, filename, "rb");

		if (ferror != 0) {
			return 1;
		}

		puts(filename);

		//Odczytujemy nag³ówek iNES
		for (int i = 0; i < 0x10; i++) {
			fread_s(&header[i], sizeof(header), 1, 1, f);
		}

		if (header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 0x1a) {
			puts("This file is a NES rom!");
		}
		else {
			puts("This file is not a NES rom!");
			return 1;
		}

		prgsize = /*(((header[9] & 0b00001111) << 8) |*/ header[4] * 16384; printf("%llu KB of PRGROM\n", prgsize / 1024);
		chrsize = /*(((header[9] & 0b11110000) << 4) |*/ header[5] * 8192; printf("%llu KB of CHRROM\n", chrsize / 1024);

		mirroring = header[6] & 0b00000001 | ((header[6] & 0b00001000) >> 2);
		battery = !!(header[6] & 0b00000010);
		trainer = !!(header[6] & 0b00000100);
		mapper = (header[6] & 0b11110000) >> 4;

		nes2 = (header[7] & 0b00001100) >> 2;

		mapper |= (header[7] & 0b11110000);
		MAPPER::setMapper(mapper);

		printf("Mapper %d\n", mapper);
		printf("Mirroring %d\n", mirroring);

		//Je¿eli wystêpuj¹ banki PRG, za³aduj je
		if (prgsize > 0) {

			// £adujemy wszystkie banki PRG do bufora
			for (u64 i = 0; i < prgsize; i++)
			fread_s(&PRGBANKS[i], sizeof(u8), 1, 1, f);

			// Kopiujemy pierwszy i ostatni bank PRG do pamiêci
			for (u64 i = 0; i < 0x4000; i++) {
				PRGROM[i] = PRGBANKS[i];
				PRGROM[i + 0x4000] = PRGBANKS[i + prgsize - 0x4000];
				//PRGROM[i + 0x4000] = PRGBANKS[i + 0x4000];
			}
		}

		//Je¿eli wystêpuj¹ banki CHR, za³aduj je
		if (chrsize > 0) {

			// £adujemy wszystkie banki CHR do bufora
			for (u64 i = 0; i < chrsize; i++)
			fread_s(&CHRBANKS[i], sizeof(u8), 1, 1, f);

			// Kopiujemy pierwszy i drugi bank PRG do pamiêci
			for (int i = 0; i < 0x2000; i++) {
				VRAM[i] = CHRBANKS[i];
			}
		}

		// zamykamy
		fclose(f);
		return 0;
	}

	void DMA(u8 page) {
		
		CPU::cyclesLeft = CPU::cyclesLeft + 513 + CPU::oddCycle;
		for (int i = 0; i < 0x100; i++) {
			OAM[i] = MAINBUS::read((page << 8) + i);
		}

	}
	
	int dmc_read(void*, cpu_addr_t addr) {
		return MAINBUS::read(addr);
	}
}
#pragma once

namespace MEM {

	//CPU
	u8 RAM[0x800];			//2 kb RAM of $0000 do $07FF

	u8 PRGRAM[0x2000];		//Od $6000 do $7FFF
	u8 PRGROM[0x8000];		//Od $8000 do $FFFF

	u8 *PRGBANKS;	//Banki danych PRG
	u8 *CHRBANKS;	//Banki danych CHR

	//PPU
	u8 VRAM[0x4000];		//16 kb VRAM
	u8 OAM[0x100];			//64*4 bajtów OAM

	//WEKTORY
	u16 NMI = 0xfffa;
	u16 reset = 0xfffc;
	u16 IRQ = 0xfffe;

	char ROMname[261];

	// byte 4
	u32 prgsize = 0;

	// byte 5
	u32 chrsize = 0;

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
			PRGRAM[i] = 0x00;
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

	void power() {

		//Sekcja RAM
		for (int i = 0; i < 0x800; i++) {
			RAM[i] = rand();
		}

		//Sekcja PRGRAM
		if (!battery) {
            for (int i = 0; i < 0x2000; i++) {
                PRGRAM[i] = rand();
            }
		}
		//Sekcja VRAM
		for (int i = (chrsize == 0 ? 0 : 0x2000); i < 0x3f00; i++) {
			VRAM[i] = rand();
		}

		//Paleta
		for (int i = 0x3f00; i < 0x4000; i++) {
			VRAM[i] = 0x00;
		}

		//Sekcja OAM
		for (int i = 0; i < 0x100; i++) {
			OAM[i] = rand();
		}

		// Kopiujemy banki PRG do pamiêci
		MAPPER::init();
		switch (mapper) {

			case 4: case 254: {
				//for (u32 i = 0; i < 0x6000; i++) PRGROM[i] = PRGBANKS[i];
				//for (u32 i = 0; i < 0x8000; i++) PRGROM[i] = PRGBANKS[i + prgsize - 0x8000];
				for (u32 i = 0; i < 0x8000; i++) PRGROM[i] = PRGBANKS[(i & 0x3fff) + prgsize - 0x4000];
				break;
			}

			case 9: {
				for (u32 i = 0; i < 0x2000; i++) PRGROM[i] = PRGBANKS[i];
				for (u32 i = 0; i < 0x6000; i++) PRGROM[i + 0x2000] = PRGBANKS[i + prgsize - 0x6000];
				break;
			}

			case 15: {
				for (u32 i = 0; i < 0x8000; i++) {
					PRGROM[i] = PRGBANKS[i];
				} break;
			}

			case 71: {
			    memset(RAM, 0, 0x800);
				for (u32 i = 0; i < 0x4000; i++) {
					PRGROM[i] = PRGBANKS[i];
					PRGROM[i + 0x4000] = PRGBANKS[i + std::min(prgsize - 0x4000, 0x3c000ul)];
				} break;
			}

			case 228: {
			    MAPPER::writebus(0x8000, 0x00);
				 break;
			}

			case 232: {
				for (u32 i = 0; i < 0x4000; i++) {
					PRGROM[i] = PRGBANKS[i];
					PRGROM[i + 0x4000] = PRGBANKS[i + 0xc000];
				} break;
			}

			default: {
				for (u32 i = 0; i < 0x4000; i++) {
					PRGROM[i] = PRGBANKS[i];
					PRGROM[i + 0x4000] = PRGBANKS[i + prgsize - 0x4000];
				} break;
			}

		}

	}

	int loadROM(const char* filename) {

		if (strlen(filename) == 0) return 1;

		#ifdef DEBUG_MODE
		printf("ROM FIlename: %s\n", filename);
		#endif

		u8 header[16];
		FILE* f;
		f = fopen(filename, "rb");

		if (f == NULL) {
			return 1;
		}

		int pos = strlen(filename);
		while (pos--) {
			if (filename[pos] == '\\') {
				strcpy(ROMname, &filename[pos]); break;
			}
		}

		//Odczytujemy nag³ówek iNES
		for (int i = 0; i < 0x10; i++) {
			fread(&header[i], 1, 1, f);
		}

		if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1a) {
			#ifdef DEBUG_MODE
			puts("This file is not a NES rom!");
			#endif
			return 1;
		}

		#ifdef DEBUG_MODE
		else {
			puts("This file is a NES rom!");
		}
		#endif

		nes2 = (header[7] & 0b00001100) >> 2;

		prgsize = header[4];
		chrsize = header[5];
		if (nes2 == 2) {
			prgsize += (header[9] & 0b00001111) << 8;
			chrsize += (header[9] & 0b11110000) << 4;
			mapper  |= (header[8] & 0b00001111) << 8;
		}
		prgsize *= 16384;
		chrsize *= 8192;

		#ifdef DEBUG_MODE
		printf("%lu KB of PRGROM\n", prgsize / 1024);
		printf("%lu KB of CHRROM\n", chrsize / 1024);
		#endif

		//Rezerwacja pamiêci dla PRG i CHR
		PRGBANKS = (u8*)malloc(prgsize * sizeof(u8));
		CHRBANKS = (u8*)malloc(chrsize * sizeof(u8));

		mirroring = header[6] & 0b00000001 | ((header[6] & 0b00001000) >> 2);
		PPU::mirroring = MIRR_4SCREEN;
		if (mirroring == 0) { PPU::mirroring = MIRR_HORIZONTAL; }
		else if (mirroring == 1) { PPU::mirroring = MIRR_VERTICAL; }

		battery = !!(header[6] & 0b00000010);
		trainer = !!(header[6] & 0b00000100);
		mapper |= (header[6] & 0b11110000) >> 4;

		mapper |= (header[7] & 0b11110000);

		//if (mapper == 7) PPU::mirroring = MIRR_SINGLE1;
		MAPPER::setMapper(mapper);

		#ifdef DEBUG_MODE
		printf("Mapper %d\n", mapper);
		printf("Mirroring %d\n", mirroring);
		#endif

		//Je¿eli wystêpuj¹ banki PRG, za³aduj je
		if (prgsize > 0) {

			// £adujemy wszystkie banki PRG do bufora
			//for (u32 i = 0; i < prgsize; i++)
			fread(PRGBANKS, sizeof(u8), prgsize, f);

		}

		//Je¿eli wystêpuj¹ banki CHR, za³aduj je
		if (chrsize > 0) {

			// £adujemy wszystkie banki CHR do bufora
			//for (u32 i = 0; i < chrsize; i++)
			fread(CHRBANKS, sizeof(u8), chrsize, f);

			// Kopiujemy pierwszy i drugi bank PRG do pamiêci
			for (int i = 0; i < 0x2000; i++) {
				if (mapper != 4) VRAM[i] = CHRBANKS[i];
			}
		}

		// zamykamy
		fclose(f);

		MAPPER::init();
		GUI::power();
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

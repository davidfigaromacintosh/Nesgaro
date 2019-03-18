#pragma once

namespace MEM {

	//CPU
	u8 RAM[0x800];		//2 kb RAM of $0000 do $07FF

	u8 PRGRAM[0x2000];	//Od $6000 do $7FFF
	u8 PRGROM[0x8000];	//Od $8000 do $FFFF

	//PPU
	u8 VRAM[0x4000];	//16 kb VRAM
	u8 OAM[0x100];		//64*4 bajtów OAM
	u8 OAM2[0x20];		//8*4 bajty OAM2

	//WEKTORY
	u16 NMI = 0xfffa;
	u16 reset = 0xfffc;
	u16 IRQ = 0xfffe;

	// byte 4
	u16 prgsize = 0;

	// byte 5
	u16 chrsize = 0;

	// byte 6
	u16 mapper = 0;
	u8 mirroring = 0;	//0 = hor, 1 = vert, 2 or 3 = four-screen
	u8 battery = 0;
	u8 trainer = 0;

	// byte 7
	u8 playchoice = 0;
	u8 nes2 = 0;

	void init() {
	
		//Sekcja RAM
		for (int i = 0; i < 0x800; i++) {
			RAM[i] = rand();
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
			OAM[i] = rand();
		}
	}

	int loadROM(const char* filename) {
		char header[16];
		FILE* f;
		fopen_s(&f, filename, "rb");

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

		prgsize = header[4] * 16384; printf("%d KB of PRGROM\n", prgsize / 1024);
		chrsize = header[5] * 8192; printf("%d KB of CHRROM\n", chrsize / 1024);

		mirroring = header[6] & 0b00000001 | ((header[6] & 0b00001000) >> 2);
		battery = !!(header[6] & 0b00000010);
		trainer = !!(header[6] & 0b00000100);
		mapper = (header[6] & 0b11110000) >> 4;

		mapper |= (header[7] & 0b11110000);

		printf("Mapper %d\n", mapper);
		printf("Mirroring %d\n", mirroring);

		char buff[0x4000] = { 0 };


		// £adujemy pierwszy bank PRG
		fread_s(buff, sizeof(buff), 1, 0x4000, f);
		for (int i = 0; i < 0x4000; i++) {
			//fread_s(buff, sizeof(buff), 1, 1, f);
			PRGROM[i] = buff[i];
			PRGROM[i + 0x4000] = buff[i];
		}

		// £adujemy pierwszy ostatni bank PRG
		if (header[4] > 1) {
			fread_s(buff, sizeof(buff), 1, 0x4000, f);
			for (int i = 0; i < 0x4000; i++) {
				//fread_s(buff, sizeof(buff), 1, 1, f);
				PRGROM[i + 0x4000] = buff[i];
			}
		}

		//£adujemy bank CHR
		if (header[5] > 0) {
			fread_s(buff, sizeof(buff), 1, 0x2000, f);
			for (int i = 0; i < 0x2000; i++) {
				//fread_s(buff, sizeof(buff), 1, 1, f);
				VRAM[i] = buff[i];
			}
		}

		// zamykamy
		fclose(f);
		return 0;
	}

	void DMA(u8 page) {
		
		CPU::cyclesLeft += 513 + CPU::oddCycle;
		for (int i = 0; i < 0x100; i++) {
			OAM[i] = MAINBUS::read((page << 8) + i);
		}

	}
	
}
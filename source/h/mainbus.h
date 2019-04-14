#pragma once

//G³ówna szyna danych konsoli (zapis, odczyt, itd itp...)
//Typów przetwarzania danych w NESie mamy dwa: zapis i odczyt

namespace MAINBUS {

	u16 readAddr(u16 addr) {
		return (read(addr) | (read(addr+1) << 8));
	}

	// ### ZAPIS ###
	void write(u16 address, u8 value) {

		u16 addr = address;

		//  === MIRRORING ===
		//Mirroring 2kb pamiêci RAM
		while (addr >= 0x0800 && addr < 0x2000) {
			addr -= 0x0800;
		}

		//Mirroring rejestrów wejœcia/wyjœcia PPU
		while (addr >= 0x2008 && addr < 0x4000) {
			addr -= 0x0008;
		}



		//  === DANE ===
		//Je¿eli robimy odczyt z pamiêci RAM
		if (addr >= 0x0000 && addr < 0x0800) {
			MEM::RAM[addr] = value;
		}
		//Wpis z rejestrów PPU
		if (addr >= 0x2000 && addr < 0x2008) {
			PPU::writebus(addr, value);
		}
		//APU
		if ((addr >= 0x4000 && addr <= 0x4013) || addr == 0x4015 || addr == 0x4017) {
			APU::writebus(CPU::APUelapsed, addr, value);
		}
		//DMA
		if (addr == 0x4014) {
			MEM::DMA(value);
		}
		//Kontroler
		if (addr == 0x4016) {
			PAD::strobe(value);
		}

		//Je¿eli robimy wpis do PRGRAM
		if (addr >= 0x6000 && addr < 0x8000) {
			MEM::PRGRAM[addr - 0x6000] = value;
		}

		//Je¿eli robimy wpis do regionu PRGROM (mapper)
		if (addr >= 0x8000 && addr <= 0xffff) {
			MAPPER::writebus(addr, value);
		}


	}

	// ### ODCZYT ###
	u8 read(u16 address) {
	
		u16 addr = address;

		//  === MIRRORING ===
		//Mirroring 2kb pamiêci RAM
		while (addr >= 0x0800 && addr < 0x2000) {
			addr -= 0x0800;
		}
		//Mirroring rejestrów wejœcia/wyjœcia PPU
		while (addr >= 0x2008 && addr < 0x4000) {
			addr -= 0x0008;
		}



		//  === DANE ===
		//Je¿eli robimy odczyt z pamiêci RAM
		if (addr >= 0x0000 && addr < 0x0800) {
			readval = MEM::RAM[addr];

		}
		//Odczyt z rejestrów PPU
		if (addr >= 0x2000 && addr < 0x2008) {
			readval = PPU::readbus(addr);
		}
		//Status APU
		if (addr == 0x4015) {
			readval = APU::readbus(CPU::APUelapsed, addr);
		}
		//Je¿eli robimy odczyt z PRGRAM
		if (addr >= 0x6000 && addr < 0x8000) {
			readval = MEM::PRGRAM[addr - 0x6000];
		}

		//Je¿eli robimy odczyt z PRGROM
		if (addr >= 0x8000 && addr <= 0xffff) {
			readval = MEM::PRGROM[addr - 0x8000];
		}
		//Kontroler
		if (addr == 0x4016) {
			readval = PAD::read();
		}

		//Game Genie
		for (int i = 0; i < GAMEGENIE::codeno; i++) {

				if ((address == GAMEGENIE::address[i]) && (GAMEGENIE::is8long[i] ? readval == GAMEGENIE::compare[i] : true)) {
					readval = GAMEGENIE::replace[i];
				}

		}

		//Zwróæ odczytan¹ wartoœæ
		return readval;
	}

	//Wepchnij do stosu
	void pushStack(u8 value) {
		MEM::RAM[0x0100 | CPU::S] = value;
		CPU::S--;
	}

	//Wyjmij ze stosu
	u8 pullStack() {
		CPU::S++;
		return MEM::RAM[0x0100 | CPU::S];
	}
}
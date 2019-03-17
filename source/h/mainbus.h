#pragma once

//G³ówna szyna danych konsoli (zapis, odczyt, itd itp...)
//Typów przetwarzania danych w NESie mamy dwa: zapis i odczyt

namespace MAINBUS {

	u16 readAddr(u16 addr) {
		return (read(addr) | (read(addr+1) << 8));
	}

	// ### ZAPIS ###
	void write(u16 address, u8 value) {



		//  === MIRRORING ===
		//Mirroring 2kb pamiêci RAM
		while (address >= 0x0800 && address < 0x2000) {
			address -= 0x0800;
		}

		//Mirroring rejestrów wejœcia/wyjœcia PPU
		while (address >= 0x2008 && address < 0x4000) {
			address -= 0x0008;
		}



		//  === DANE ===
		//Je¿eli robimy odczyt z pamiêci RAM
		if (address >= 0x0000 && address < 0x0800) {
			MEM::RAM[address] = value;
		}
		//Wpis z rejestrów PPU
		if (address >= 0x2000 && address < 0x2008) {
			PPU::writebus(address, value);
		}
		//DMA
		if (address == 0x4014) {
			MEM::DMA(value);
		}
		//Kontroler
		if (address == 0x4016) {
			PAD::strobe(value);
		}


	}

	// ### ODCZYT ###
	u8 read(u16 address) {
	


		//  === MIRRORING ===
		//Mirroring 2kb pamiêci RAM
		while (address >= 0x0800 && address < 0x2000) {
			address -= 0x0800;
		}
		//Mirroring rejestrów wejœcia/wyjœcia PPU
		while (address >= 0x2008 && address < 0x4000) {
			address -= 0x0008;
		}



		//  === DANE ===
		//Je¿eli robimy odczyt z pamiêci RAM
		if (address >= 0x0000 && address < 0x0800) {
			return MEM::RAM[address];

		}
		//Odczyt z rejestrów PPU
		if (address >= 0x2000 && address < 0x2008) {
			return PPU::readbus(address);
		}

		//Je¿eli robimy odczyt z PRGRAM
		if (address >= 0x6000 && address < 0x8000) {
			return MEM::PRGRAM[address - 0x6000];
		}

		//Je¿eli robimy odczyt z PRGROM
		if (address >= 0x8000 && address <= 0xffff) {
			return MEM::PRGROM[address - 0x8000];
		}
		//Kontroler
		if (address == 0x4016) {
			return PAD::read();
		}

		return 0;
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
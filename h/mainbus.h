//G³ówna szyna danych konsoli (zapis, odczyt, itd itp...)
//Typów przetwarzania danych w NESie mamy dwa: zapis i odczyt

namespace MAINBUS {

	u16 readAddr(u16 addr) {
		return (read(addr) | (read(addr+1) << 8));
	}

	// ### ZAPIS ###
	void write(u16 address, u8 value) {
		
		//std::cout << "WRITE: ";

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

			//std::cout << "Value 0x" << std::setfill('0') << std::setw(2) << std::hex << (u16)value << " to $" << std::setfill('0') << std::setw(4) << address << std::dec << std::endl;
			MEM::RAM[address] = value;
		}
		//Wpis z rejestrów PPU
		else if (address >= 0x2000 && address < 0x2008) {
			PPU::writebus(address, value);
		}
		//Je¿eli robimy odczyt z rejestrów PPU
		else if (address >= 0x2000 && address < 0x2008) {

		}

	}

	// ### ODCZYT ###
	u8 read(u16 address) {

		//std::cout << "READ: ";
	
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

			//std::cout << "Value 0x" << std::setfill('0') << std::setw(2) << std::hex << (u16)MEM::RAM[address] << " from $" << std::setfill('0') << std::setw(4) << address << std::dec << std::endl;
			return MEM::RAM[address];

		}
		//Odczyt z rejestrów PPU
		else if (address >= 0x2000 && address < 0x2008) {
			return PPU::readbus(address);
		}

		//Je¿eli robimy odczyt z PRGRAM
		else if (address >= 0x6000 && address < 0x8000) {
			return MEM::PRGRAM[address - 0x6000];
		}

		//Je¿eli robimy odczyt z PRGROM
		else if (address >= 0x8000 && address <= 0xffff) {
			return MEM::PRGROM[address - 0x8000];
		}

	}

	//Wepchnij do stosu
	void pushStack(u8 value) {
		//std::cout << "STACK: Pushed $" << std::setfill('0') << std::setw(2) << std::hex << (u16)value << " at $" << std::setfill('0') << std::setw(2) << 0x0100 + CPU::S << std::dec << std::endl;
		MEM::RAM[0x0100 | CPU::S] = value;
		CPU::S--;
	}

	//Wyjmij ze stosu
	u8 pullStack() {
		CPU::S++;
		//std::cout << "STACK: Pulled $" << std::setfill('0') << std::setw(2) << std::hex << (u16)MEM::RAM[0x0100 + CPU::S] << " at $" << std::setfill('0') << std::setw(2) << 0x0100 + CPU::S << std::dec << std::endl;
		return MEM::RAM[0x0100 | CPU::S];
	}
}
namespace MAPPER {

	void init() {
		mapper = 0;

		mmc1Count = 0;
		mmc1Control = 0x0c;
		mmc1CHRmode = 0;
		mmc1PRGmode = 3;
		mmc1Shift = 0;
	}

	void setMapper(u32 mapperid) {
		mapper = mapperid;
	}

	// DEFINICJE DLA MAPPERÓW
	void writebus(u16 address, u8 value) {
		switch (mapper) {
			
			//MMC1
			#pragma region mapper1
			case 1: {	
				mmc1Shift = ((value & 0b00001) << 4) | (mmc1Shift >> 1);
				mmc1Count++;

				//Reset shiftu gdy bit na MSB
				if (value & 0b10000000) {
					mmc1PRGmode = 3;
					mmc1Count = 0;
					mmc1Shift = 0;
					mmc1SetPRGBanks();
					break;
				}

				//Po 5-tym wpisie...
				if (mmc1Count == 5) {
				
					//Control
					if (address >= 0x8000 && address <= 0x9fff) {
						mmc1PRGmode = (mmc1Shift & 0b01100) >> 2;
						mmc1CHRmode = (mmc1Shift & 0b10000) >> 4;
						MEM::mirroring = 3 - (mmc1Shift & 0b00011);
					}

					//CHR0
					if (address >= 0xa000 && address <= 0xbfff) {

						if (MEM::chrsize == 0) return;

						if (mmc1CHRmode == 0) {
							memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * (mmc1Shift & 0b11110)) % MEM::chrsize), 0x2000);
						}
						if (mmc1CHRmode == 1) {
							memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (mmc1Shift & 0b11111)) % MEM::chrsize), 0x1000);
						}
					}

					//CHR1
					if (address >= 0xc000 && address <= 0xdfff) {

						if (MEM::chrsize == 0) return;

						if (mmc1CHRmode == 1) {
							memcpy(MEM::VRAM + 0x1000, MEM::CHRBANKS + ((0x1000 * (mmc1Shift & 0b11111)) % MEM::chrsize), 0x1000);
						}
					}

					//PRG
					if (address >= 0xe000 && address <= 0xffff) {

						if (MEM::prgsize == 0) return;

						mmc1SetPRGBanks();
					}


					mmc1Shift = 0;
					mmc1Count = 0;
				}
				break;
			}
			#pragma endregion

			//UxROM
			#pragma region mapper2
			case 2: {
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & (MEM::nes2 == 2 ? 0b11111111 : 0b1111))) % MEM::prgsize), 0x4000);
				break;
			}
			#pragma endregion
			
			//CNROM
			#pragma region mapper3
			case 3: {
				memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * value) % MEM::chrsize), 0x2000);
				break;
			}
			#pragma endregion

			//AxROM
			#pragma region mapper7
			case 7: {	
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * (value & 0b111)) % MEM::prgsize), 0x8000);
			}
			#pragma endregion

			//Camerica
			#pragma region mapper71
			case 71: {
				if (address >= 0xc000 && address <= 0xffff)	memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & 0b1111)) % MEM::prgsize), 0x4000);
			}
			#pragma endregion

		}
	}

	void mmc1SetPRGBanks() {

		if (mmc1PRGmode <= 1) {
			memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize), 0x8000);
			//memcpy(MEM::PRGROM + 0x4000,	MEM::PRGBANKS + 0x4000	+ ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize),			0x4000);
		}
		else if (mmc1PRGmode == 2) {
			memcpy(MEM::PRGROM, MEM::PRGBANKS, 0x4000);
			memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
		}
		else if (mmc1PRGmode == 3) {
			memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
			memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + MEM::prgsize - 0x4000, 0x4000);
		}

	}
}
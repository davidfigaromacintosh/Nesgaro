//MMC3
//https://wiki.nesdev.com/w/index.php/MMC3				//Rejestry
//http://bobrost.com/nes/files/mmc3irqs.txt				//Wszystko o ¿¹daniach przerwania


namespace MAPPER {

	void init() {
		mapper = 0;

		//MMC1
		mmc1Count = 0;
		mmc1Control = 0x0c;
		mmc1CHRmode = 0;
		mmc1PRGmode = 3;
		mmc1Shift = 0;

		//MMC3
		mmc3BankMode = 0;
		mmc3PRGmode = 0;
		mmc3CHRinversion = 0;
		mmc3IRQenable = 0;
		mmc3IRQlatch = 0;
		mmc3IRQcounter = 0;
		mmc3IRQreloadRequest = 0;
		mmc3IRQhalt = 0;
		mmc3risingEdge = 0;
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

						if (MEM::chrsize > 0) {

							if (mmc1CHRmode == 0) {
								memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x4000 * (mmc1Shift >> 1)) % MEM::chrsize), 0x2000);
							}
							if (mmc1CHRmode == 1) {
								memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (mmc1Shift & 0b11111)) % MEM::chrsize), 0x1000);
							}

						}
					}

					//CHR1
					if (address >= 0xc000 && address <= 0xdfff) {

						if (MEM::chrsize > 0) {

							if (mmc1CHRmode == 1) {
								memcpy(MEM::VRAM + 0x1000, MEM::CHRBANKS + ((0x1000 * (mmc1Shift & 0b11111)) % MEM::chrsize), 0x1000);
							}

						}
					}

					//PRG
					if (address >= 0xe000 && address <= 0xffff) {

						if (MEM::prgsize > 0)
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
				if (MEM::prgsize > 0)
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & (MEM::nes2 == 2 ? 0b11111111 : 0b1111))) % MEM::prgsize), 0x4000);
				break;
			}
			#pragma endregion
			
			//CNROM
			#pragma region mapper3
			case 3: {
				if (MEM::chrsize > 0)
				memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * value) % MEM::chrsize), 0x2000);
				break;
			}
			#pragma endregion

			//MMC3
			#pragma region mapper4
			case 4: {
				if (address >= 0x8000 && address <= 0x9fff) {
					
					//Bank select (even)
					if (address % 2 == 0) {	
						mmc3BankMode = value & 0b111;
						mmc3PRGmode = !!(value & 0b01000000);
						mmc3CHRinversion = !!(value & 0b10000000);
					}

					//Bank data (odd)
					else {	
						switch (mmc3BankMode) {
						case 0: {	//Select 2 KB CHR bank at PPU $0000-$07FF (or $1000-$17FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM			+ 0x1000 *  mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x800 * (value >> 1)) % MEM::chrsize), 0x800);
							break;
						}
						case 1: {	//Select 2 KB CHR bank at PPU $0800-$0FFF (or $1800-$1FFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x800	+ 0x1000 *  mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x800 * (value >> 1)) % MEM::chrsize), 0x800);
							break;
						}
						case 2: {	//Select 1 KB CHR bank at PPU $1000-$13FF (or $0000-$03FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM			+ 0x1000 * !mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 3: {	//Select 1 KB CHR bank at PPU $1400-$17FF (or $0400-$07FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x400	+ 0x1000 * !mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 4: {	//Select 1 KB CHR bank at PPU $1800-$1BFF (or $0800-$0BFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x800	+ 0x1000 * !mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 5: {	//Select 1 KB CHR bank at PPU $1C00-$1FFF (or $0C00-$0FFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0xc00	+ 0x1000 * !mmc3CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 6: {	//Select 8 KB PRG ROM bank at $8000-$9FFF (or $C000-$DFFF)
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM + 0x4000 *  mmc3PRGmode, MEM::PRGBANKS + ((0x2000 * (value & 0b00111111)) % MEM::prgsize), 0x2000);
								memcpy(MEM::PRGROM + 0x4000 * !mmc3PRGmode, MEM::PRGBANKS + MEM::prgsize - 0x4000, 0x2000);
							}
							break;
						}
						case 7: {	//Select 8 KB PRG ROM bank at $A000-$BFFF
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM + 0x2000, MEM::PRGBANKS + ((0x2000 * (value & 0b00111111)) % MEM::prgsize), 0x2000);
							}
							break;
						}


						}
					}
				}

				if (address >= 0xa000 && address <= 0xbfff) {
					if (address % 2 == 0) {	//Mirroring (even)
						MEM::mirroring = !(value & 1);
					}

					else {	//PRGRAM protection (odd)
					
					}
				}

				if (address >= 0xc000 && address <= 0xdfff) {
					if (address % 2 == 0) {	//IRQ latch (even)
						mmc3IRQlatch = value;
						if (mmc3IRQcounter == 0) mmc3IRQreloadRequest = 1;
					}

					else {	//IRQ reload (odd)
						mmc3IRQreloadRequest = 1;
					}
				}

				if (address >= 0xe000 && address <= 0xffff) {
					if (address % 2 == 0) {	//IRQ disable (even)
						mmc3IRQenable = 0;
					}

					else {	//IRQ enable (odd)
						mmc3IRQenable = 1;
					}
				}

				break;
			}
			#pragma endregion

			//AxROM
			#pragma region mapper7
			case 7: {	
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * (value & 0b111)) % MEM::prgsize), 0x8000);
				break;
			}
			#pragma endregion

			//Camerica
			#pragma region mapper71
			case 71: {
				if (address >= 0xc000 && address <= 0xffff)	memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & 0b1111)) % MEM::prgsize), 0x4000);
				break;
			}
			#pragma endregion

		}
	}

	void mmc1SetPRGBanks() {

		if (mmc1PRGmode <= 1) {
			for (int i = 0; i < 0x8000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i + (0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize), 0x8000);
			//memcpy(MEM::PRGROM + 0x4000,	MEM::PRGBANKS + 0x4000	+ ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize),			0x4000);
		}
		else if (mmc1PRGmode == 2) {
			for (int i = 0; i < 0x4000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i];
				MEM::PRGROM[i + 0x4000] = MEM::PRGBANKS[i + (0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS, 0x4000);
			//memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
		}
		else if (mmc1PRGmode == 3) {
			for (int i = 0; i < 0x4000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize)];
				MEM::PRGROM[i + 0x4000] = MEM::PRGBANKS[i + MEM::prgsize - 0x4000];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
			//memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + MEM::prgsize - 0x4000, 0x4000);
		}

	}
}
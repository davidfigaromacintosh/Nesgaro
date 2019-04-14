//MMC3
//https://wiki.nesdev.com/w/index.php/MMC3				//Rejestry
//http://bobrost.com/nes/files/mmc3irqs.txt				//Wszystko o ¿¹daniach przerwania


namespace MAPPER {

	void init() {

		mapper = MEM::mapper;

		//MMC1
		#pragma region mapper1
		MMC1::count = 0;
		MMC1::control = 0x0c;
		MMC1::CHRmode = 0;
		MMC1::PRGmode = 3;
		MMC1::shift = 0;
		#pragma endregion

		//MMC3
		#pragma region mapper4
		MMC3::bankMode = 0;
		MMC3::PRGmode = 0;
		MMC3::CHRinversion = 0;
		MMC3::IRQenable = 0;
		MMC3::IRQlatch = 0;
		MMC3::IRQcounter = 0;
		MMC3::IRQreloadRequest = 0;
		MMC3::IRQhalt = 0;
		MMC3::risingEdge = 0;
		#pragma endregion

		//Educational Computer
		#pragma region mapper178
		EDU178::bankMode = 0;
		#pragma endregion

		//Camerica Quattro
		#pragma region mapper232
		CAMQUATTRO::bankBlock = 0;
		CAMQUATTRO::bankPage = 0;
		#pragma endregion
	}

	void setMapper(u32 mapperid) {
		mapper = mapperid;
	}

	// DEFINICJE DLA MAPPERÓW
	void writebus(u16 address, u8 value) {
		switch (mapper) {
			
			//MMC1
			case 1: {	
				MMC1::shift = ((value & 0b00001) << 4) | (MMC1::shift >> 1);
				MMC1::count++;

				//Reset shiftu gdy bit na MSB
				if (value & 0b10000000) {
					MMC1::PRGmode = 3;
					MMC1::count = 0;
					MMC1::shift = 0;
					MMC1::setPRGBanks();
					break;
				}

				//Po 5-tym wpisie...
				if (MMC1::count == 5) {
				
					//Control
					if (address >= 0x8000 && address <= 0x9fff) {
						MMC1::PRGmode = (MMC1::shift & 0b01100) >> 2;
						MMC1::CHRmode = (MMC1::shift & 0b10000) >> 4;

						switch (MMC1::shift & 0b00011) {
							case 0: {
								PPU::mirroring = MIRR_SINGLE1; break;
							}
							case 1: {
								PPU::mirroring = MIRR_SINGLE2; break;
							}
							case 2: {
								PPU::mirroring = MIRR_VERTICAL; break;
							}
							case 3: {
								PPU::mirroring = MIRR_HORIZONTAL; break;
							}
						}

					}

					//CHR0
					if (address >= 0xa000 && address <= 0xbfff) {

						if (MEM::chrsize > 0) {

							if (MMC1::CHRmode == 0) {
								memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (MMC1::shift & 0b11110)) % MEM::chrsize), 0x2000);
							}
							if (MMC1::CHRmode == 1) {
								memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (MMC1::shift & 0b11111)) % MEM::chrsize), 0x1000);
							}

						}
					}

					//CHR1
					if (address >= 0xc000 && address <= 0xdfff) {

						if (MEM::chrsize > 0) {

							if (MMC1::CHRmode == 1) {
								memcpy(MEM::VRAM + 0x1000, MEM::CHRBANKS + ((0x1000 * (MMC1::shift & 0b11111)) % MEM::chrsize), 0x1000);
							}

						}
					}

					//PRG
					if (address >= 0xe000 && address <= 0xffff) {

						if (MEM::prgsize > 0)
							MMC1::setPRGBanks();
						
					}


					MMC1::shift = 0;
					MMC1::count = 0;
				}
				break;
			}

			//UxROM
			case 2: {
				if (MEM::prgsize > 0)
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & (MEM::nes2 == 2 ? 0b11111111 : 0b1111))) % MEM::prgsize), 0x4000);
				break;
			}
		
			//CNROM
			case 3: {
				if (MEM::chrsize > 0)
				memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * value) % MEM::chrsize), 0x2000);
				break;
			}

			//MMC3
			case 4: {
				if (address >= 0x8000 && address <= 0x9fff) {
					
					//Bank select (even)
					if (address % 2 == 0) {	
						MMC3::bankMode = value & 0b111;
						MMC3::PRGmode = !!(value & 0b01000000);
						MMC3::CHRinversion = !!(value & 0b10000000);
					}

					//Bank data (odd)
					else {	
						switch (MMC3::bankMode) {
						case 0: {	//Select 2 KB CHR bank at PPU $0000-$07FF (or $1000-$17FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM			+ 0x1000 * MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x800 * (value >> 1)) % MEM::chrsize), 0x800);
							break;
						}
						case 1: {	//Select 2 KB CHR bank at PPU $0800-$0FFF (or $1800-$1FFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x800	+ 0x1000 * MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x800 * (value >> 1)) % MEM::chrsize), 0x800);
							break;
						}
						case 2: {	//Select 1 KB CHR bank at PPU $1000-$13FF (or $0000-$03FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM			+ 0x1000 * !MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 3: {	//Select 1 KB CHR bank at PPU $1400-$17FF (or $0400-$07FF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x400	+ 0x1000 * !MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 4: {	//Select 1 KB CHR bank at PPU $1800-$1BFF (or $0800-$0BFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x800	+ 0x1000 * !MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 5: {	//Select 1 KB CHR bank at PPU $1C00-$1FFF (or $0C00-$0FFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0xc00	+ 0x1000 * !MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * value) % MEM::chrsize), 0x400);
							break;
						}
						case 6: {	//Select 8 KB PRG ROM bank at $8000-$9FFF (or $C000-$DFFF)
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM + 0x4000 * MMC3::PRGmode, MEM::PRGBANKS + ((0x2000 * (value & 0b00111111)) % MEM::prgsize), 0x2000);
								memcpy(MEM::PRGROM + 0x4000 * !MMC3::PRGmode, MEM::PRGBANKS + MEM::prgsize - 0x4000, 0x2000);
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
						PPU::mirroring = !(value & 1);
					}

					else {	//PRGRAM protection (odd)
					
					}
				}

				if (address >= 0xc000 && address <= 0xdfff) {
					if (address % 2 == 0) {	//IRQ latch (even)
						MMC3::IRQlatch = value;
						if (MMC3::IRQcounter == 0) MMC3::IRQreloadRequest = 1;
					}

					else {	//IRQ reload (odd)
						MMC3::IRQreloadRequest = 1;
					}
				}

				if (address >= 0xe000 && address <= 0xffff) {
					if (address % 2 == 0) {	//IRQ disable (even)
						MMC3::IRQenable = 0;
					}

					else {	//IRQ enable (odd)
						MMC3::IRQenable = 1;
					}
				}

				break;
			}

			//AxROM
			case 7: {	
				memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * (value & 0b111)) % MEM::prgsize), 0x8000);
				PPU::mirroring = MIRR_SINGLE1 + !!(value & 0b10000);
				break;
			}

			//100-in-1 Contra Function 16
			case 15: {
				if (address & 0x8000) {

					PPU::mirroring = !(value & 0x40);

					u8 bank = value & 0x3f;
					u8 subbank = !!(value & 0x80);
					switch (address & 3) {
					
						//32K
						case 0: {
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM			, MEM::PRGBANKS + ((0x4000 * bank) % MEM::prgsize), 0x4000);	//Bank B
								memcpy(MEM::PRGROM + 0x4000	, MEM::PRGBANKS + ((0x4000 * (bank | 1)) % MEM::prgsize), 0x4000);	//Bank B OR 1
							}
							break;
						}

						//128K
						case 1: {
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM			, MEM::PRGBANKS + ((0x4000 * bank) % MEM::prgsize), 0x4000);	//Bank B
								memcpy(MEM::PRGROM + 0x4000	, MEM::PRGBANKS + ((0x4000 * (bank | 7)) % MEM::prgsize), 0x4000);	//Bank B OR 7
							}
							break;
						}

						//8K
						case 2: {
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM			, MEM::PRGBANKS + (((0x4000 * bank) + (0x2000 * subbank)) % MEM::prgsize), 0x2000);	//Subbank b of bank B
								memcpy(MEM::PRGROM + 0x2000	, MEM::PRGBANKS + (((0x4000 * bank) + (0x2000 * subbank)) % MEM::prgsize), 0x2000);	//Mirror of $8000-$9FFF
								memcpy(MEM::PRGROM + 0x4000	, MEM::PRGBANKS + (((0x4000 * bank) + (0x2000 * subbank)) % MEM::prgsize), 0x2000);	//Mirror of $8000-$9FFF
								memcpy(MEM::PRGROM + 0x6000	, MEM::PRGBANKS + (((0x4000 * bank) + (0x2000 * subbank)) % MEM::prgsize), 0x2000);	//Mirror of $8000-$9FFF
							}
							break;
						}

						//16K
						case 3: {
							if (MEM::prgsize > 0) {
								memcpy(MEM::PRGROM			, MEM::PRGBANKS + ((0x4000 * bank) % MEM::prgsize), 0x4000);	//Bank B
								memcpy(MEM::PRGROM + 0x4000	, MEM::PRGBANKS + ((0x4000 * bank) % MEM::prgsize), 0x4000);	//Mirror of $8000-$BFFF
							}
							break;
						}
					
					}

				}
				break;
			}

			//BNROM NINA-001
			case 34: {
				if (MEM::prgsize > 0) memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * value) % MEM::prgsize), 0x8000);
				break;
			}

			//Camerica
			case 71: {

				if (address >= 0x9000 && address <= 0x9fff) {
					PPU::mirroring = !!(value & 0b00010000) + MIRR_SINGLE1;
				}

				else if (address >= 0xc000 && address <= 0xffff) {
					memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & 0b1111)) % MEM::prgsize), 0x4000);
				}

				break;
			}

			//Camerica Quattro
			case 232: {

				if (address >= 0x8000 && address <= 0x9fff) {
					CAMQUATTRO::bankBlock = (value & 0b00011000) >> 3;
					CAMQUATTRO::setPRGbanks();
				}

				else if (address >= 0xa000 && address <= 0xffff) {
					CAMQUATTRO::bankPage = value & 0b11;
					CAMQUATTRO::setPRGbanks();
				}

				break;
			}

		}
	}

	void MMC1::setPRGBanks() {

		if (PRGmode <= 1) {
			for (int i = 0; i < 0x8000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i + (0x4000 * (shift & 0b1110)) % MEM::prgsize];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize), 0x8000);
			//memcpy(MEM::PRGROM + 0x4000,	MEM::PRGBANKS + 0x4000	+ ((0x4000 * (mmc1Shift & 0b1110)) % MEM::prgsize),			0x4000);
		}
		else if (PRGmode == 2) {
			for (int i = 0; i < 0x4000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i];
				MEM::PRGROM[i + 0x4000] = MEM::PRGBANKS[i + (0x4000 * (shift & 0b1111)) % MEM::prgsize];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS, 0x4000);
			//memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
		}
		else if (PRGmode == 3) {
			for (int i = 0; i < 0x4000; i++) {
				MEM::PRGROM[i] = MEM::PRGBANKS[i + ((0x4000 * (shift & 0b1111)) % MEM::prgsize)];
				MEM::PRGROM[i + 0x4000] = MEM::PRGBANKS[i + MEM::prgsize - 0x4000];
			}
			//memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (mmc1Shift & 0b1111)) % MEM::prgsize), 0x4000);
			//memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + MEM::prgsize - 0x4000, 0x4000);
		}

	}

	void CAMQUATTRO::setPRGbanks() {
		memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x10000 * CAMQUATTRO::bankBlock + 0x4000 * CAMQUATTRO::bankPage) % MEM::prgsize), 0x4000);
		memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x10000 * CAMQUATTRO::bankBlock + 0xc000) % MEM::prgsize), 0x4000);
	}
}
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
		MMC1::PRGRAMenable = 1;
		#pragma endregion

		//MMC3
		#pragma region mapper4
		MMC3::bankMode = 0;
		MMC3::PRGmode = 0;
		MMC3::PRGRAMenable = 0;
		MMC3::PRGRAMprotect = 0;
		MMC3::CHRinversion = 0;
		MMC3::IRQenable = 0;
		MMC3::IRQlatch = 0;
		MMC3::IRQcounter = 0;
		MMC3::IRQreloadRequest = 0;
		MMC3::IRQhalt = 0;
		MMC3::risingEdge = 0;
		#pragma endregion

		//MMC2
		#pragma region mapper9
		MMC2::latch0 = 0xfd;
		MMC2::latch1 = 0xfd;
		#pragma endregion

		//Camerica
		#pragma region mapper71
		CAMERICA::bankBlock = 0;
		CAMERICA::bankProtect = 0;
		CAMERICA::bankPage = 0;
		#pragma endregion

		//Educational Computer
		#pragma region mapper178
		EDU178::bankMode = 0;
		EDU178::PRGlowBank = 0;
		EDU178::PRGhiBank = 0;
		#pragma endregion

		//Camerica Quattro
		#pragma region mapper232
		CAMQUATTRO::bankBlock = 0;
		CAMQUATTRO::bankPage = 0;
		#pragma endregion

        #pragma region mapper254
		PIKACHUY2K::exReg[0] = 0;
		PIKACHUY2K::exReg[1] = 0;
		#pragma endregion
	}

	void setMapper(u32 mapperid) {
		mapper = mapperid;
	}

	//READ MAPPER
	u8 readbus(u16 address) {

        u8 retval = CPU::openBus;

        switch (mapper) {

            case 0: {
                if (address >= 0x6000 && address <= 0x7fff) {
                    retval = MEM::PRGRAM[address - 0x6000];
			    } break;
            }

            case 1: {
                if (address >= 0x6000 && address <= 0x7fff && MMC1::PRGRAMenable) {
                    retval = MEM::PRGRAM[address - 0x6000];
			    } break;
            }

            case 4: {
                if (address >= 0x6000 && address <= 0x7fff && MMC3::PRGRAMenable) {
                    retval = MEM::PRGRAM[address - 0x6000];
			    } break;
            }

            //Sachen NROM 143
            case 143: {
                if ((address >= 0x4100 && address <= 0x5fff)) {
                    retval = 0x40 | (~address & 0b111111);
                }
                if (address >= 0x6000 && address <= 0x7fff) {
                    retval = MEM::PRGRAM[address & 0x1fff];
			    } break;
            }

			case 228: {

			    if (address >= 0x4020 && address <= 0x5fff) {
                    retval = ACTION52::RAM[address & 0b11];
			    } break;
			}

            case 254: {
                if (address >= 0x6000 && address <= 0x7fff) {
                    retval = MEM::PRGRAM[address - 0x6000] ^ (PIKACHUY2K::exReg[0] ? 0 : PIKACHUY2K::exReg[1]);
			    } break;
            }

			//Nesgaro
            case 4097: {
                if (address >= 0x4020 && address <= 0x4fff) {

                        switch (address & 3) {

                            case 0: { retval = 0xF1; break;}
                            case 1: { retval = 0x9A; break;}
                            case 2: { retval = 0x20; break;}
                            case 3: { retval = 0x5A; break;}

                        }
                }

                if (address >= 0x5000 && address <= 0x5fff) retval = rand();

                break;
            }

        }

        return retval;
	}



	// DEFINICJE DLA MAPPERÓW
	void writebus(u16 address, u8 value) {
		switch (mapper) {

            //NROM
            case 0: {
            	if (address >= 0x6000 && address <= 0x7fff) {
                    MEM::PRGRAM[address & 0x7ff] = value;
			    } break;
            }

			//MMC1
			case 1: {

			    if (address >= 0x6000 && address <= 0x7fff && MMC1::PRGRAMenable) {
                    MEM::PRGRAM[address - 0x6000] = value;
			    }

			    //Rejestry przesuwne MMC1
			    if (address >= 0x8000 && address <= 0xffff) {

                    MMC1::shift = ((value & 0b00001) << 4) | (MMC1::shift >> 1);
                    MMC1::count++;

                    //Reset shiftu gdy bit na MSB
                    if (value & 0b10000000) {
                        MMC1::PRGmode = 3;
                        MMC1::count = 0;
                        MMC1::shift = 0;
                        //MMC1::setPRGBanks();
                        break;
                    }

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
                        MMC1::PRGRAMenable = !(MMC1::shift & 0b10000);
						if (MEM::prgsize > 0) MMC1::setPRGBanks();
					}

					MMC1::shift = 0;
					MMC1::count = 0;
				}
				break;
			}

			//UxROM
			case 2: {
			    if (address & 0x8000) {
                    if (MEM::prgsize > 0) memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x4000 * (value & (MEM::nes2 == 2 ? 0b11111111 : 0b1111))) % MEM::prgsize), 0x4000);
				} break;
			}

			//CNROM
			case 3: {
			    if (address & 0x8000) {
                    if (MEM::chrsize > 0) memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * value) % MEM::chrsize), 0x2000);
				} break;
			}

			//MMC3 & MMC3-like
			case 4: case 254: {

			    if (address >= 0x6000 && address <= 0x7fff && MMC3::PRGRAMenable && !MMC3::PRGRAMprotect) {
                    MEM::PRGRAM[address - 0x6000] = value;
			    }

			    //PIKACHU Y2K
			    if (mapper == 254) {
                    if (address == 0x8000) {PIKACHUY2K::exReg[0] = 0xff;}
                    if (address == 0xa001) {PIKACHUY2K::exReg[1] = value;}
			    }

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
							memcpy(MEM::VRAM			+ 0x1000 * MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * (value & 0b11111110)) % MEM::chrsize), 0x800);
							break;
						}
						case 1: {	//Select 2 KB CHR bank at PPU $0800-$0FFF (or $1800-$1FFF)
							if (MEM::chrsize > 0)
							memcpy(MEM::VRAM + 0x800	+ 0x1000 * MMC3::CHRinversion, MEM::CHRBANKS + 0x000 + ((0x400 * (value & 0b11111110)) % MEM::chrsize), 0x800);
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
                        MMC3::PRGRAMprotect =!!(value & 0b01000000);
                        MMC3::PRGRAMenable = !!(value & 0b10000000);
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
			    if (address & 0x8000) {
                    memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * (value & 0b111)) % MEM::prgsize), 0x8000);
                    PPU::mirroring = MIRR_SINGLE1 + !!(value & 0b10000);
				} break;
			}

			//MMC2
			case 9: {

				//Select 8 KB PRG ROM bank for CPU $8000-$9FFF
				if (address >= 0xa000 && address <= 0xafff) {
					memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x2000 * (value & 0b1111)) % MEM::prgsize), 0x2000);
				}

				//Select 4 KB CHR ROM bank for PPU $0000-$0FFF used when latch 0 = $FD
				if (address >= 0xb000 && address <= 0xbfff) {
					if (MMC2::latch0 == 0xfd) memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (value & 0b11111)) % MEM::chrsize), 0x1000);
				}

				//Select 4 KB CHR ROM bank for PPU $0000-$0FFF used when latch 0 = $FE
				if (address >= 0xc000 && address <= 0xcfff) {
					if (MMC2::latch0 == 0xfe) memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x1000 * (value & 0b11111)) % MEM::chrsize), 0x1000);
				}

				//Select 4 KB CHR ROM bank for PPU $1000-$1FFF used when latch 1 = $FD
				if (address >= 0xd000 && address <= 0xdfff) {
					if (MMC2::latch1 == 0xfd) memcpy(MEM::VRAM + 0x1000, MEM::CHRBANKS + ((0x1000 * (value & 0b11111)) % MEM::chrsize), 0x1000);
				}

				//Select 4 KB CHR ROM bank for PPU $1000-$1FFF used when latch 1 = $FE
				if (address >= 0xe000 && address <= 0xefff) {
					if (MMC2::latch1 == 0xfe) memcpy(MEM::VRAM + 0x1000, MEM::CHRBANKS + ((0x1000 * (value & 0b11111)) % MEM::chrsize), 0x1000);
				}

				//Select 4 KB CHR ROM bank for PPU $1000-$1FFF
				if (address >= 0xf000 && address <= 0xffff) {
					PPU::mirroring = !(value & 1);
				}
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
			    if (address & 0x8000) {
                    if (MEM::prgsize > 0) memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * value) % MEM::prgsize), 0x8000);
				} break;
			}

			//Camerica
			case 71: {

				//Outer banks
				if (address >= 0x8000 && address <= 0xbfff) {
					if (!CAMERICA::bankProtect) CAMERICA::bankBlock = (value & 0b111);
					CAMERICA::bankProtect = !!(value & 0b1000);
					CAMERICA::setPRGbanks();
				}

				//Mirroring
				if (address >= 0x9000 && address <= 0x9fff) {
					PPU::mirroring = !!(value & 0b00010000) + MIRR_SINGLE1;
				}

				//Inner banks
				if (address >= 0xc000 && address <= 0xffff) {
					CAMERICA::bankPage = value & 0b1111;
					CAMERICA::setPRGbanks();
				}

				break;
			}

			case 178: {

                switch(address) {
                    case 0x4800: {
                        PPU::mirroring = !(value & 1);
                        EDU178::bankMode = (value &0b110) > 1;
                        break; }
                    case 0x4801: {

                        break; }
                }

                break;
			}

			//Magic Jewerly 2
			case 216: {
			    if (address & 0x8000) {
                    if (MEM::prgsize > 0) memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x8000 * (address & 1)) % MEM::prgsize), 0x8000);
                    if (MEM::chrsize > 0) memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * (address & 0x0e) >> 1) % MEM::chrsize), 0x2000);
				} break;
			}

			//Action 52 / Cheetahmen II
			case 228: {

                //RAM
			    if (address >= 0x4020 && address < 0x5fff) {

                    ACTION52::RAM[address & 0b11] = value & 0b1111;
			    }

			    //Reszta
			    if (address & 0x8000) {

                    //CHR
                    if (MEM::chrsize > 0) memcpy(MEM::VRAM, MEM::CHRBANKS + ((0x2000 * ( (value & 0b11) | ((address & 0b1111) << 2) )) % MEM::prgsize), 0x2000);

                    //PRG
                    if (MEM::prgsize > 0) {

                        u8 chip;

                        switch((address & 0b0001100000000000) >> 11) {
                            case 1:  { chip = 1; break; }
                            case 3:  { chip = 2; break; }
                            default: { chip = 0; break; }
                        }

                        if (!(address & 0b100000)) {
                            memcpy(MEM::PRGROM         , MEM::PRGBANKS + ((0x80000 * chip + 0x4000 * ((address & 0b0000011110000000) >> 6)) % MEM::prgsize), 0x8000);
                        } else {
                            memcpy(MEM::PRGROM         , MEM::PRGBANKS + ((0x80000 * chip + 0x4000 * ((address & 0b0000011111000000) >> 6)) % MEM::prgsize), 0x4000);
                            memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x80000 * chip + 0x4000 * ((address & 0b0000011111000000) >> 6)) % MEM::prgsize), 0x4000);
                        }

                    }

                    //Mirroring
                    PPU::mirroring = !(address & 0b0010000000000000);
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

            //Nesgaro
            case 4097: {

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

	void CAMERICA::setPRGbanks() {
		memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x40000 * CAMERICA::bankBlock + 0x4000 * CAMERICA::bankPage) % MEM::prgsize), 0x4000);
		memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x40000 * CAMERICA::bankBlock + 0x3c000) % MEM::prgsize), 0x4000);
	}

	void CAMQUATTRO::setPRGbanks() {
		memcpy(MEM::PRGROM, MEM::PRGBANKS + ((0x10000 * CAMQUATTRO::bankBlock + 0x4000 * CAMQUATTRO::bankPage) % MEM::prgsize), 0x4000);
		memcpy(MEM::PRGROM + 0x4000, MEM::PRGBANKS + ((0x10000 * CAMQUATTRO::bankBlock + 0xc000) % MEM::prgsize), 0x4000);
	}
}

#pragma once

namespace PPU {

	void init() {
		dot = 30;
		scanline = 0;
		oddframe = 0;
		frame = 1;

		//Flagi
		spr0 = 0;
		sproverflow = 1;
		vblank = 1;
		vblAfter = 1;

		//Wewn�trzne rejestry PPU
		T = 0;
		V = 0;
		X = 0;
		W = 0;
		OAMV = 0;
		readbuffer = 0;

		NMIsuppresion = 0;
		VBLsuppresion = 0;

		//Bity $2000
		NMIenabled = 0;
		PPUmasterslave = 0;
		SPRsize = 0;
		BGpattern = 0;
		SPRpattern = 0;
		VRAMincrement = 0;
		nametable = 0;

		//Bity $2001
		grayscale = 0;
		BGenable8 = 0;
		SPRenable8 = 0;
		BGenable = 0;
		SPRenable = 0;
		emphasisR = 0;
		emphasisG = 0;
		emphasisB = 0;

		//$2002
		lsbWrite = 0;
	}

	void power() {

		//Bity $2000
		NMIenabled = 0;
		PPUmasterslave = 0;
		SPRsize = 0;
		BGpattern = 0;
		SPRpattern = 0;
		VRAMincrement = 0;
		nametable = 0;

		//Bity $2001
		grayscale = 0;
		BGenable8 = 0;
		SPRenable8 = 0;
		BGenable = 0;
		SPRenable = 0;
		emphasisR = 0;
		emphasisG = 0;
		emphasisB = 0;

		spr0 = 0;
		sproverflow = 1;
		vblank = 1;
        vblAfter = 1;

		NMIsuppresion = 0;
		VBLsuppresion = 0;

		OAMV = 0x00;

		W = 0;
		T = 0;
		V = 0;
		X = 0;

		readbuffer = 0;

		dot = 30;
		scanline = 0;
		oddframe = 0;
		frame = 1;

		lsbWrite = 0;
	}

	void reset() {

		//Bity $2000
		NMIenabled = 0;
		PPUmasterslave = 0;
		SPRsize = 0;
		BGpattern = 0;
		SPRpattern = 0;
		VRAMincrement = 0;
		nametable = 0;

		//Bity $2001
		grayscale = 0;
		BGenable8 = 0;
		SPRenable8 = 0;
		BGenable = 0;
		SPRenable = 0;
		emphasisR = 0;
		emphasisG = 0;
		emphasisB = 0;

		spr0 = 0;
		sproverflow = 1;

		W = 0;
		T = 0;
		readbuffer = 0;
	}

	void step() {

		//Rysowany ekran znajduje si� na koordach od 1 do 256 dot i od 0 do 239 scanline...

		#ifdef DEBUG_MODE
		printf("\nPPU Cycle!");
		#endif

		// === Pre scan (-1) ===
		if (scanline == -1) {

			//Zawsze na docie 1 pre-linii flagi VBlank, SPR0 oraz SPROV s� czyszczone
			if (dot == 1) {
				vblank = 0;
				spr0 = 0;
				sproverflow = 0;

				VBLsuppresion = 0;
				NMIsuppresion = 0;
			}


            if (NMIenabled == 1 && vblank == 1 && NMIsuppresion == 0 && VBLsuppresion == 0) {
				CPU::NMIoccured = 1;
				NMIsuppresion = 1;
				//vblank = 0;
			}

			//Wyczyszczam OAM2
			if (dot == 257) {
				for (int i = 0; i < 256; i++) {
					OAM2[i >> 3] = 0xff;
					OAMIndex[i >> 5] = i;
					OAM2Final[i] = 0;
					OAMIsSpr0[i] = false;
					OAMPriority[i] = false;
				}
			}

			//dot 257: scroll update
			if (dot == 257 && renderingEnabled()) {
				V = (V & 0b111101111100000) | (T & 0b000010000011111);
			}

			//OAMADDR jest r�wne 0 w tym obszarze
			if (dot == 257 && dot < 320) {
				OAMV = 0;
			}

			// dot od 280 do 304: scroll update
			if (dot >= 280 && dot <= 304 && renderingEnabled()) {
				V = (V & 0b000010000011111) | (T & 0b111101111100000);
			}

		}



		// === Widzialne linie (od 0 do 239) ===
		else if (scanline >= 0 && scanline <= 239) {

			//VRAM zwi�kszenie X dla dot od 1 do 256 oraz Y gdy dot = 256
			if ((dot >= 2) && (dot <= 257) && renderingEnabled()) {


				u16 temp = (((V & 0b11111) << 3) + (X + (dot - 1) % 8));
				if (temp >= 256) {
					//V = V & 0b111101111111111 | (((nametable & 0b01) ^ 0b01) << 10);
					if (((V & 0b000010000000000) >> 10) == (nametable & 0b01)) {
						V ^= 0b000010000000000;
					}
				}


				if ((dot - 1) % 8 == 0) {
					u16 tempX = V & 0b11111;
					tempX++;

					if (tempX == 32) {
						tempX = 0;
						if (((V & 0b000010000000000) >> 10) == (nametable & 0b01)) {
							V ^= 0b000010000000000;
						}
					}
					V = V & 0b111111111100000 | tempX;
				}

				if (dot == 257 && renderingEnabled()) {
					u16 tempY = (V & 0b111000000000000) >> 12 | (V & 0b000001111100000) >> 2;
					tempY++;
					if ((tempY) >= 62) {

					}
					if ((tempY >> 3) == 30) {
						tempY = 0;
						V ^= 0b000100000000000;

					}
					V = (V & 0b000110000011111) | ((tempY & 0b00000111) << 12) | ((tempY & 0b11111000) << 2);
				}

				//OAMADDR jest r�wne 0 w tym obszarze
				if (dot == 257 && dot < 320) {
					OAMV = 0;
				}

			}

			//dot 257: scroll update
			if ((dot == 257) && renderingEnabled()) {

				V = (V & 0b111101111100000) | (T & 0b000010000011111);
			}

			//if ((dot == 320 || dot == 328 || dot == 336) && renderingEnabled()) {
            //
			//	V = (V & 0b111111111100000) | ((V+1) & 0b000000000011111);
			//}

			//SPRITE EVALUATION
			if (dot == 257) {

				//Czyszczenie OAM2 i OAM2Final
				for (int i = 0; i < 256; i++) {
					OAM2[i>>3] = 0xff;
					OAMIndex[i>>5] = i;
					OAM2Final[i] = 0;
					OAMIsSpr0[i] = false;
					OAMPriority[i] = false;
				}

				//Wype�niamy OAM2 na podstawie danych zawartych w OAM
				int sprindex = 0;
				for (int i = 0; i < 64; i++) {

					if (MEM::OAM[4 * i] > 0xef) continue;



					//Sprite evaluation
					u8 spry = scanline - MEM::OAM[4 * i];
					if (spry >= 0 && spry < 8 + 8*SPRsize) {

						//Na jednej scanlinii nie mo�e by� wi�cej ni� 8 sprite'�w
						if (sprindex == 8) {
							if (SPRenable || BGenable) sproverflow = 1;
						}
						else if (sprindex < 8) {

							OAM2[4 * sprindex] = spry;
							OAM2[4 * sprindex + 1] = MEM::OAM[4 * i + 1];
							OAM2[4 * sprindex + 2] = MEM::OAM[4 * i + 2];
							OAM2[4 * sprindex + 3] = MEM::OAM[4 * i + 3];

							OAMIndex[sprindex] = i;


						}
						sprindex++;
					}
				}

				//Printowanie sprite'�w na jednej scanlinii
				for (int i = 7; i >= 0; i--) {	//Sprite (s� rysowane od ostatniego do pierwszego)
					for (int j = 0; j < 8; j++) {	//8 pixeli (szeroko�� sprite'u)
						if ( ((OAM2[4 * i + 3] + j) < 256) && (OAM2[4 * i] < (8 + 8*SPRsize)) ) {

							//Scanlinia z gotowymi sprite'ami
							b flipX = (OAM2[4 * i + 2] & 0b01000000) >> 6;
							b flipY = (OAM2[4 * i + 2] & 0b10000000) >> 7;
							u8 sprpxl;

							sprpxl = SPRsize ? (
								4 * (OAM2[4 * i + 2] & 0b11) +
								!!(MEM::VRAM[(flipY ? 8 * (OAM2[4 * i] < 8) : 8 * (OAM2[4 * i] >= 8)) +		0x1000 * (OAM2[4 * i + 1] & 1) + 16 * (OAM2[4 * i + 1] & 0b11111110) + (flipY ? 15 - OAM2[4 * i] : OAM2[4 * i])] & (0b10000000 >> (flipX ? 7 - j : j)))
								+
							2 *	!!(MEM::VRAM[(flipY ? 8 * (OAM2[4 * i] < 8) : 8 * (OAM2[4 * i] >= 8)) + 8 +	0x1000 * (OAM2[4 * i + 1] & 1) + 16 * (OAM2[4 * i + 1] & 0b11111110) + (flipY ? 15 - OAM2[4 * i] : OAM2[4 * i])] & (0b10000000 >> (flipX ? 7 - j : j)))
								):(
								4 * (OAM2[4 * i + 2] & 0b11) +
								!!(MEM::VRAM[		0x1000 * SPRpattern + 16 * OAM2[4 * i + 1] + (flipY ? 7 - OAM2[4 * i] : OAM2[4 * i])] & (0b10000000 >> (flipX ? 7 - j : j)))
								+
							2 *	!!(MEM::VRAM[8 +	0x1000 * SPRpattern + 16 * OAM2[4 * i + 1] + (flipY ? 7 - OAM2[4 * i] : OAM2[4 * i])] & (0b10000000 >> (flipX ? 7 - j : j)))
								);

							if (sprpxl % 4 != 0) {
								OAM2Final[OAM2[4 * i + 3] + j] = sprpxl;

								OAMIsSpr0[OAM2[4 * i + 3] + j] = (OAMIndex[i] == 0);
								OAMPriority[OAM2[4 * i + 3] + j] = (OAM2[4 * i + 2] & 0b00100000) >> 5;
							}
						}
					}
				}

			}

		}



		// === Post scan (od 240 do 260) ===
		else if (scanline >= 240) {

            if (NMIenabled == 0) {
				NMIsuppresion = 0;
			}

			//Pocz�tek VBlank oraz NMI
			if (scanline == 241) {

				if (dot == 1) {
					if (VBLsuppresion == 0) {
						vblank = 1;
					}
				}

			}

			if (scanline >= 241 || scanline == -1) {

				if (((scanline == 241 && dot >= 3) || (scanline > 241) || (scanline == -1 && dot <= 2)) && NMIenabled == 1 && vblank == 1 && NMIsuppresion == 0 && VBLsuppresion == 0) {
					CPU::NMIoccured = 1;
					NMIsuppresion = 1;
					//vblank = 0;
				}

			}

			//dot 257: scroll update
			if (scanline == 240 && dot == 257 && renderingEnabled()) {
				V = (V & 0b111101111100000) | (T & 0b000010000011111);
			}

		}



		//Piksele s� rysowane jedynie na obszarze dla dot od 1 do 256 oraz linii od 0 do 239
		if ( (scanline >= 0 && scanline <= 239) && ( dot >= 1 && dot <= 256)) {
			u8 coordX = (dot - 1) & 0xff;
			u8 coordY = scanline & 0xff;
			u8 pxl = fetchPixel(0);

			scr->put(coordX, coordY, pxl & (grayscale ? 0x0030 : 0xffff));
			if (SPRenable) {

				//Spr0 hit
				if ((OAM2Final[coordX]%4) && isOpaque[coordX][coordY] && OAMIsSpr0[coordX] && BGenable && (BGenable8 && SPRenable8 ? true : dot > 8) && dot < 256) spr0 = 1;

				//Rysowanie sprite'�w na ekranie
				if (OAM2Final[coordX]%4 != 0 && !(!SPRenable8 && coordX < 8)) {
					if (!OAMPriority[coordX] || (OAMPriority[coordX] && !isOpaque[coordX][coordY])) {
						scr->put(coordX, coordY, MEM::VRAM[0x3f10 + OAM2Final[coordX]] & (grayscale ? 0x0030 : 0xffff) );
					}
				}

			}


		}

		//MMC3
		if ((scanline >= -1 && scanline <= 239)) {

			//MMC3
			if (dot == 297) {
				//Reload request
				if (MAPPER::MMC3::IRQreloadRequest == 1) {
					MAPPER::MMC3::IRQreloadRequest = 0;
					MAPPER::MMC3::IRQcounter = MAPPER::MMC3::IRQlatch;
					MAPPER::MMC3::IRQhalt = 0;
				}
			}
			if (dot == 296) {
				//Na ko�cu scanlinii dekrementujemy licznik
				if (MAPPER::MMC3::IRQcounter > 0) {
					--MAPPER::MMC3::IRQcounter;
					if (MAPPER::MMC3::IRQcounter == 0 && MAPPER::MMC3::IRQenable == 1 && MAPPER::MMC3::IRQhalt == 0 && !CPU::getI()) {
						CPU::IRQoccured = 1;
						MAPPER::MMC3::IRQhalt = 1;
					}
				}
			}

		}

		#ifdef DEBUG_MODE
		printf(" Dot=%d Line=%d Odd=%d VBlank=%d NMI=%d BG=%d SPR=%d SPR0=%d SPROV=%d T=%04x V=%04x X=%d W=%d B=%02x", dot, scanline, oddframe, vblank, NMIenabled, BGenable, SPRenable, spr0, sproverflow, T, V, X, W, readbuffer);
		#endif

		//Co drug� klatk� video, prescan jest o 1 dot kr�tszy
        dot++;

		if (dot > 340 - (oddframe && scanline == -1 && renderingEnabled() && (tvregion == NTSC))) {
			dot = 0;
			scanline++;

            if (scanline == scanlines[tvregion] - 1) {
                scanline = -1;
                oddframe = !oddframe;
                frame++;
                //exit(CPU::cycles);
            }
		}

		////
	    vblAfter = vblank;

	}

	b renderingEnabled() {
		return BGenable || SPRenable;
	}

	void setHori(u8 _v) {
        V = (V & 0b111111111100000) | (_v & 0b11111);
	}

    void setVert(u8 _v) {
        V = (V & 0b000110000011111) | ((_v & 0b111) << 12) | ((_v & 0b11111000) << 5);
	}

	u8 getHori() {
        return V & 0b11111;
	}

    u8 getVert() {
        return ((V & 0b111) << 12) | ((V & 0b11111000) << 5);
	}

	u8 fetchPixel(u8 liteColor) {
		fineX = X;
		coarseX = V & 0b11111;
		fineY = (V & 0b111000000000000) >> 12;
		coarseY = (V & 0b000001111100000) >> 5;

		u8 nt = ((V & 0b000110000000000) >> 10);

		u16 mirr = 0x1000;

		if (mirroring == MIRR_HORIZONTAL || (mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4)) {
			mirr = 0x400;
		}
		if (mirroring == MIRR_VERTICAL) {
			mirr = 0x800;
		}

		u8 tempD = (coarseX + ((fineX + (dot - 1) % 8) >> 3)) % 32;

		//u8 pixel = MEM::VRAM[0x1000 * BGpattern + MEM::VRAM[0x2000 + ((coarseX << 3) + dot % 8) + 0x10 * ((coarseY << 3) + fineY) >> 3]];      + 0x800 * ((nt & 0b01) && (mirr == 0x400))
		u8 pixel =		!!(MEM::VRAM[0x1000 * BGpattern     + fineY + 16 * MEM::VRAM[((mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) * (mirroring - 2) * 0x400) + 0x2000 + ((((coarseX + ((fineX + (dot - 1) % 8) >> 3)) % 32) + 32 * coarseY + 0x400 * nt) % mirr) + 0x400/**/ * ((nt & 0b10) && (mirroring == MIRR_HORIZONTAL) && !(mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) )]] & (0b10000000 >> (fineX + (dot - 1)) % 8))
			+
					2 * !!(MEM::VRAM[0x1000 * BGpattern + 8 + fineY + 16 * MEM::VRAM[((mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) * (mirroring - 2) * 0x400) + 0x2000 + ((((coarseX + ((fineX + (dot - 1) % 8) >> 3)) % 32) + 32 * coarseY + 0x400 * nt) % mirr) + 0x400/**/ * ((nt & 0b10) && (mirroring == MIRR_HORIZONTAL) && !(mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) )]] & (0b10000000 >> (fineX + (dot - 1)) % 8))
			;

		u8 attribute = ( MEM::VRAM[((mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) * (mirroring - 2) * 0x400) + 0x23c0 + (((tempD >> 2) + 8 * (coarseY >> 2) + 0x400 * nt) % mirr + 0x400/**/ * ((nt & 0b10) && (mirroring == MIRR_HORIZONTAL) && !(mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) ))] & (0b11 << ((tempD & 0b10) + 2 * (coarseY & 0b10))) ) >> ((tempD & 0b10) + 2 * (coarseY & 0b10)); // & (0b00000011 << (((tempD & 0b10)/2) + (coarseY & 0b10)))

		if (!BGenable8 && (dot >= 1 && dot <= 8)) pixel = 0;

		if (pixel == 0) {
			isOpaque[dot - 1][scanline] = false;
		} else {
			isOpaque[dot - 1][scanline] = true;
		}

		switch (liteColor) {
			case 1: {
				return ((V)+((X + ((dot - 1) % 8)) >> 3));
			}
			case 2: {
				return isOpaque[dot - 1][scanline];
			}
			default: {

				//return (MEM::VRAM[0x3f00 + ((pixel + 4 * attribute) * !!(pixel)) * BGenable]);
				if (renderingEnabled()) {
					if (BGenable) {
						return (MEM::VRAM[0x3f00 + ((pixel + 4 * attribute) * !!(pixel))]);
					} else {
						return MEM::VRAM[0x3f00];
					}
				} else {
					if (V >= 0x3f00 && V <= 0x3fff) {
						return MEM::VRAM[0x3f00 + (((V % 0x20)) & (((!!(V % 4)) << 4) | 0xff0f))];
					} else {
						return MEM::VRAM[0x3f00];
					}
				}

			}
		}

		//return liteColor ? (MEM::VRAM[0x3f00 + ((pixel + 4 * attribute) * !!(pixel)) * BGenable]) : ((V)+((X + ((dot - 1) % 8)) >> 3));
	}

	void loadPalette(const char* filename) {

		#ifdef DEBUG_MODE
		puts(filename);
		#endif

		FILE *f;
		if((f = fopen(filename, "rb")) == NULL) return;

		u8 buff;

		for (int i = 0; i < 64; i++)
		{
			colors[i] = 0x000000ff;

			for (int j = 0; j < 3; j++) {
				fread(&buff, 1, 1, f);
				colors[i] |= buff << (24 - 8 * j);
			}

		}

		fclose(f);
	}

	// ### Szyna danych PPU (odczyt) ###
	u8 readbus(u16 regno) {
		switch (regno) {
			case PPU_STATUS: {	//Read $2002 R

				W = 0;
				u8 tempvblank = vblank;
				vblank = 0;

				if (scanline == 241) {
					//if (dot == 0) {
					//	NMIsuppresion = 1;
					//}
					if (dot == 1) {
						tempvblank = 0;
						VBLsuppresion = 1;
						NMIsuppresion = 1;
					}

					if (dot >= 2 && dot <= 3) {
						NMIsuppresion = 1;
						CPU::NMIoccured = 0;
					}

				}

				return (tempvblank << 7) | (spr0 << 6) | (sproverflow << 5) | (lsbWrite & 0b00011111);
			}
			case OAM_DATA: {	//Read $2004 R W

				//http://wiki.nesdev.com/w/index.php/PPU_sprite_evaluation
				if (scanline >= 0 && scanline <= 239 && renderingEnabled()) {
					if (dot < 64) return 0xff;
					if (dot < 256) return 0x00;
					if (dot < 320) return 0xff;
					return OAM2[0];
				} else {
					return MEM::OAM[OAMV];
				}
			}
			case PPU_DATA: {	//Read $2007 R W

				u8 tempvalue;
				u16 tempv = V;

				//Wst�pny mirroring
				while (tempv >= 0x4000) {
					tempv -= 0x4000;
				}

                //Playfield
				if (tempv < 0x3f00) {

					//Nametable mirroring
					while (tempv >= 0x3000 && tempv < 0x3f00) {
						tempv -= 0x1000;
					}

					//*
					//Horizontal mirroring
					if (mirroring == MIRR_HORIZONTAL) {
						if (tempv >= 0x2400 && tempv < 0x2800) {
							tempv -= 0x0400;
						}
						if (tempv >= 0x2800 && tempv < 0x2c00) {
							tempv -= 0x0400;
						}
						if (tempv >= 0x2c00 && tempv < 0x3000) {
							tempv -= 0x0800;
						}
					}
					//Vertical mirroring
					else if (mirroring == MIRR_VERTICAL) {
						while (tempv >= 0x2800 && tempv < 0x3000) {
							tempv -= 0x0800;
						}
					}
					//Single screen mirroring
					else if (mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) {
						while (tempv >= 0x2400 && tempv < 0x3000) {
							tempv -= 0x0400;
						}
						if (tempv >= 0x2000 && tempv < 0x2400) tempv += (mirroring - MIRR_SINGLE1) * 0x400;
					}

					//*/


					tempvalue = readbuffer;
					readbuffer = MEM::VRAM[tempv];

					//tempvalue = MEM::VRAM[tempv];
				}

				//Paleta kolor�w
				else {

					//mirroring koloru t�a
					//while (tempv >= 0x3f04 && tempv < 0x3f10 && renderingEnabled()) {
					//	tempv -= 0x04;
					//}

					switch (tempv) {
					case 0x3f10:
					case 0x3f14:
					case 0x3f18:
					case 0x3f1c:
						tempv -= 0x10;
					}

					//Mirroring palety kolor�w
					while (tempv >= 0x3f20 && tempv < 0x4000) {
						tempv -= 0x20;
					}

					tempvalue = MEM::VRAM[tempv];
				}

				//https://wiki.nesdev.com/w/index.php/PPU_scrolling#.242007_reads_and_writes
                if (scanline >= -1 && scanline <= 239 && renderingEnabled()) {
                    u8 cX = V & 0b11111;
                    u8 cY = ((V & 0b111000000000000) >> 12) | ((V & 0b1111100000) >> 2);
                    cX++, cY++;
                    V = (V & 0b000110000000000) | cX | ((cY & 0b111) << 12) | ((cY & 0b11111000) << 2);
				}
				else {
                    if (VRAMincrement == 0) {
                        V = (V + 1) & 0x3fff;
                    } else {
                        V = (V + 32) & 0x3fff;
                    }
				}

				return tempvalue;
			}
			default: {
				return 0;
			}
		}
	}

	// ###Szyna danych PPU (zapis) ###
	void writebus(u16 regno, u8 value) {

		lsbWrite = value;

		switch (regno) {
			case PPU_CTRL: {	//Write $2000 W

				T = (T & 0b111001111111111) | ((value & 0b00000011) << 10);

				NMIenabled =		!!(value & 0b10000000);
				PPUmasterslave =	!!(value & 0b01000000);
				SPRsize =			!!(value & 0b00100000);
				BGpattern =			!!(value & 0b00010000);
				SPRpattern =		!!(value & 0b00001000);
				VRAMincrement =		!!(value & 0b00000100);
				nametable =			  (value & 0b00000011);

				break;
			}
			case PPU_MASK: {	//Write $2001 W

				grayscale =			!!(value & 0b00000001);
				BGenable8 =			!!(value & 0b00000010);
				SPRenable8 =		!!(value & 0b00000100);
				BGenable =			!!(value & 0b00001000);
				SPRenable =			!!(value & 0b00010000);
				emphasisR =			!!(value & 0b00100000);
				emphasisG =			!!(value & 0b01000000);
				emphasisB =			!!(value & 0b10000000);

				break;
			}
			case OAM_ADDR: {	//Write $2003 W
				OAMV = value;
				break;
			}
			case OAM_DATA: {	//Write $2004 W R
				if (!(scanline >= -1 && scanline <= 239 && renderingEnabled())){
					MEM::OAM[OAMV++] = value;
				}
				break;
			}
			case PPU_SCROLL: {	//Write $2005 W W

				if (W == 0) {
					T = (T & 0b111111111100000) | ((0xffff & value & 0b11111000) >> 3);
					X = value & 0b00000111;
					W = 1;
				}
				else {
					T = (T & 0b000110000011111) | ((0xffff & value & 0b00000111) << 12) | ((0xffff & value & 0b11111000) << 2);
					W = 0;
				}
				//W = !W;

				break;
			}
			case PPU_ADDR: {	//Write $2006 W W

				if (W == 0) {
					T = (T & 0b100000011111111) | ((0xffff & value & 0b00111111) << 8);
					T &= 0b011111111111111;
					W = 1;
				}
				else {
					T = (T & 0b111111100000000) | value;
					V = T;
					W = 0;
				}
				//W = !W;

				break;
			}
			case PPU_DATA: {	//Write $2007 R W
				u16 tempv = V;

				//Wst�pny mirroring
				while (tempv >= 0x4000) {
					tempv -= 0x4000;
				}

				//mirroring koloru t�a
				//while (tempv >= 0x3f04 && tempv < 0x3f10 && renderingEnabled()) {
				//	tempv -= 0x04;
				//}

				switch (tempv) {
				case 0x3f10:
				case 0x3f14:
				case 0x3f18:
				case 0x3f1c:
					tempv -= 0x10;
				}

				//Mirroring palety kolor�w
				while (tempv >= 0x3f20 && tempv < 0x4000) {
					tempv -= 0x20;
				}

				//Nametable mirroring
				while (tempv >= 0x3000 && tempv < 0x3f00) {
					tempv -= 0x1000;
				}

				//*
				//Horizontal mirroring
				if (mirroring == MIRR_HORIZONTAL) {
					if (tempv >= 0x2400 && tempv < 0x2800) {
						tempv -= 0x0400;
					}
					if (tempv >= 0x2800 && tempv < 0x2c00) {
						tempv -= 0x0400;
					}
					if (tempv >= 0x2c00 && tempv < 0x3000) {
						tempv -= 0x0800;
					}
				}
				//Vertical mirroring
				else if (mirroring == MIRR_VERTICAL) {
					while (tempv >= 0x2800 && tempv < 0x3000) {
						tempv -= 0x0800;
					}
				}
				//Single screen mirroring
				else if (mirroring >= MIRR_SINGLE1 && mirroring <= MIRR_SINGLE4) {
					while (tempv >= 0x2400 && tempv < 0x3000) {
						tempv -= 0x0400;
					}
					if (tempv >= 0x2000 && tempv < 0x2400) tempv += (mirroring - MIRR_SINGLE1) * 0x400;
				}
				//*/

				if (tempv >= 0x2000 * !!(MEM::chrsize) ) { MEM::VRAM[tempv & 0x3fff] = value; }

				//if (VRAMincrement == 0) {
				//	V = (V + 1) & 0x3fff;
				//}
				//else {
				//	V = (V + 32) & 0x3fff;
				//}

				//https://wiki.nesdev.com/w/index.php/PPU_scrolling#.242007_reads_and_writes
                if (scanline >= -1 && scanline <= 239 && renderingEnabled()) {
                    u8 cX = V & 0b11111;
                    u8 cY = ((V & 0b111000000000000) >> 12) | ((V & 0b1111100000) >> 2);
                    cX++, cY++;
                    V = (V & 0b000110000000000) | cX | ((cY & 0b111) << 12) | ((cY & 0b11111000) << 2);
				}
				else {
                    if (VRAMincrement == 0) {
                        V = (V + 1) & 0x3fff;
                    } else {
                        V = (V + 32) & 0x3fff;
                    }
				}

				break;
			}
			default: {
				break;
			}
		}
	}

}

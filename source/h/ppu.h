namespace PPU {

	void init() {
		dot = 340;
		scanline = -1;
		oddframe = 0;

		//Flagi
		spr0 = 0;
		sproverflow = 0;
		vblank = 0;

		//Wewnêtrzne rejestry PPU
		T = 0;
		V = 0;
		X = 0;
		W = 0;
		OAMV = 0;

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
		emphasisR = 0;
		emphasisB = 0;
	}

	void step() {

		//Rysowany ekran znajduje siê na koordach od 1 do 256 dot i od 0 do 239 scanline...

		#ifdef DEBUG_MODE
		printf("\nPPU Cycle!");
		#endif

		dot++;

		if (dot == 341) {
			dot = 0;
			scanline++;
		}
		if (scanline == 261) {
			scanline = -1;
			dot = 1;
			oddframe = !oddframe;

			//std::this_thread::sleep_for(std::chrono::microseconds(5));

		}

		if (scanline == -1) { //Pre scan (-1)

			//Zawsze na docie 1 pre-linii flagi VBlank, SPR0 oraz SPROV s¹ czyszczone
			if (dot == 1) {
				vblank = 0;
				spr0 = 0;
				sproverflow = 0;
			}
			else if (dot >= 280 && dot <= 304) {
				V = V & 0b111101111100000 | T & 0b000010000011111;
			}

		}
		else if (scanline >= 0 && scanline <= 239) {	//Widzialne linie (od 0 do 239)

			if (scanline == 0 && dot == 0 && oddframe && (BGenable || SPRenable)) dot = 1;	//Pierwszy pixel jest pomijany na linii 0 gdy klatka video jest nieparzysta


		}
		else if (scanline >= 240 && scanline <= 260) { //Post scan (od 240 do 260)

			if (scanline == 241 && dot == 1) {
				vblank = 1;
				if (NMIenabled) {
					CPU::NMIoccured = 1;
				}
			}

		}

		#ifdef DEBUG_MODE
		printf(" Dot=%d Line=%d Odd=%d VBlank=%d NMI=%d SPR0=%d SPROV=%d T=%d V=%d X=%d W=%d", dot, scanline, oddframe, vblank, NMIenabled, spr0, sproverflow, T, V, X, W);
		#endif

	}

	//Szyna danych PPU (odczyt)
	u8 readbus(u16 regno) {
		switch (regno) {
			case PPU_CTRL: {	//Read $2000 W
				return 0;
			}
			case PPU_MASK: {	//Read $2001 W
				return 0;
			}
			case PPU_STATUS: {	//Read $2002 R

				W = 0;
				u8 tempvblank = vblank;
				vblank = 0;

				return ((tempvblank << 2) | (spr0 << 1) | (sproverflow)) << 5;
			}
			case OAM_ADDR: {	//Read $2003 W
				return 0;
			}
			case OAM_DATA: {	//Read $2004 R W
				return MEM::OAM[OAMV];
			}
			case PPU_SCROLL: {	//Read $2005 W W
				return 0;
			}
			case PPU_ADDR: {	//Read $2006 W W
				return 0;
			}
			case PPU_DATA: {	//Read $2007 R W
				u8 tempbuff = MEM::VRAM[V];
				if (VRAMincrement == 0) {
					V += 1;
				} else {
					V += 32;
				}
				return tempbuff;
			}
		}
	}

	//Szyna danych PPU (zapis)
	void writebus(u16 regno, u8 value) {
		switch (regno) {
			case PPU_CTRL: {	//Write $2000 W

				T = (T & 0b111001111111111) | ((0xffff & value) & 0b0000000000000011) << 10;
				
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
				emphasisR =			!!(value & 0b01000000);
				emphasisB =			!!(value & 0b10000000);

				break;
			}
			case PPU_STATUS: {	//Write $2002 R
				break;
			}
			case OAM_ADDR: {	//Write $2003 W
				OAMV = value;
			}
			case OAM_DATA: {	//Write $2004 W R

				MEM::OAM[OAMV++] = value;
			}
			case PPU_SCROLL: {	//Write $2005 W W
				break;
			}
			case PPU_ADDR: {	//Write $2006 W W

				if (W == 0) {

					W = 1;
				} else {
					W = 0;
				}

				
				break;
			}
			case PPU_DATA: {	//$2007 R W
				MEM::VRAM[V] = value;
				if (VRAMincrement == 0) {
					V += 1;
				}
				else {
					V += 32;
				}
				break;
			}
		}
	}

}
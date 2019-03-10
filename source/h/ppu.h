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

		//Bity $2000
		NMIenabled = 0;
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
			if (dot == 1) {
				vblank = 0;
			}
		}
		else if (scanline >= 0 && scanline <= 239) {	//Widzialne linie (od 0 do 239)
			if (scanline == 0 && dot == 0 && oddframe) dot = 1;	//Pierwszy pixel jest pomijany na linii 0 gdy klatka video jest nieparzysta


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

	u8 readbus(u16 regno) {
		switch (regno) {
			case 0x2000: {	//$2000
				return 0;
			}
			case 0x2001: {	//$2001
				break;
			}
			case 0x2002: {	//$2002

				W = 0;
				u8 tempvblank = vblank;
				vblank = 0;

				return ((tempvblank << 2) | (spr0 << 1) | (sproverflow)) << 5;
			}
			case 0x2003: {	//$2003
				return 0;
			}
			case 0x2004: {	//$2004
				break;
			}
			case 0x2005: {	//$2005
				break;
			}
			case 0x2006: {	//$2006
				break;
			}
			case 0x2007: {	//$2007
				break;
			}
		}
	}
	void writebus(u16 regno, u8 value) {
		switch (regno) {
			case 0x2000: {	//$2000

				T = (T & 0b111001111111111) | ((0xffff & value) & 0b0000000000000011) << 10;
				NMIenabled = !!(value & 0b10000000);

				break;
			}
			case 0x2001: {	//$2001
				break;
			}
			case 0x2002: {	//$2002
				break;
			}
			case 0x2003: {	//$2003
				break;
			}
			case 0x2004: {	//$2004
				break;
			}
			case 0x2005: {	//$2005
				break;
			}
			case 0x2006: {	//$2006
				break;
			}
			case 0x2007: {	//$2007
				break;
			}
		}
	}

}
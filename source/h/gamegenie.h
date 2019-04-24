namespace GAMEGENIE {

	void init() {
		codeno = 0;
		for (int i = 0; i < 256; i++) {
			address[i] = 0;
			compare[i] = 0;
			replace[i] = 0;
			is8long[i] = 0;
		}
	}

	u8 getLetterValue(char lett) {

		//Litery i odpowiadaj�ce im warto�ci
		switch (lett) {
			case 'A': case 'a': return 0x0;
			case 'P': case 'p': return 0x1;
			case 'Z': case 'z': return 0x2;
			case 'L': case 'l': return 0x3;
			case 'G': case 'g': return 0x4;
			case 'I': case 'i': return 0x5;
			case 'T': case 't': return 0x6;
			case 'Y': case 'y': return 0x7;
			case 'E': case 'e': return 0x8;
			case 'O': case 'o': return 0x9;
			case 'X': case 'x': return 0xa;
			case 'U': case 'u': return 0xb;
			case 'K': case 'k': return 0xc;
			case 'S': case 's': return 0xd;
			case 'V': case 'v': return 0xe;
			case 'N': case 'n': return 0xf;
		}

		//Gdy wykryje liter� inn� ni� na li�cie, zwr�� 0xff jako kod b��du
		return 0xff;
	}

	int addCheatCode(const char* code) {

		//W puli mo�e by� maksymalnie 255 kod�w bo ja tak chc�. Serio, �adna gra nie potrzebuje a� ponad 255 kod�w GG ;)
		if (codeno == 255) return 3;

		//Tryby: Tryb #0 = 6 znak�w, tryb #1 = 8 znak�w, tryb #2 = b��d
		u8 mode = [](const char* _c)->u8
		{
			if (strlen(_c) == 6)	return 0;
			if (strlen(_c) == 8)	return 1;
									return 2;
		}(code);

		u8 codeval[8];

		//Kod musi posiada� albo dok�adnie 6 albo dok�adnie 8 liter, je�li nie, zako�cz:
		if (mode == 2) return 2;
		is8long[codeno] = mode;

		//Sprawdza, czy wszystkie litery s� prawid�owe, je�eli jaka� litera nie nale�y do puli liter Game Genie, zako�cz
		for (int i = 0; i < (mode ? 8 : 6); i++) {
			if (getLetterValue(code[i]) == 0xff) return 1;
			codeval[i] = getLetterValue(code[i]);
		}

		//Dla obydw�ch tryb�w dekodowanie adresu jest identyczne (zer�ni�te z http://tuxnes.sourceforge.net/gamegenie.html)
		address[codeno] = 0x8000 + (
			(	(codeval[3] & 7) << 12	)	|
			(	(codeval[5] & 7) << 8	)	|	(	(codeval[4] & 8) << 8	)	|
			(	(codeval[2] & 7) << 4	)	|	(	(codeval[1] & 8) << 4	)	|
				(codeval[4] & 7)			|		(codeval[3] & 8)		)	;

		//Dekodowanie warto�ci zast�pczej ju� nie
		replace[codeno] = (mode == 0) ?

			//6 znak�w
			(	(codeval[1] & 7) << 4	)	|	(	(codeval[0] & 8) << 4	)	|
				(codeval[0] & 7)			|		(codeval[5] & 8)			:

			//8 znak�w
			(	(codeval[1] & 7) << 4	)	|	(	(codeval[0] & 8) << 4	)	|
				(codeval[0] & 7)			|		(codeval[7] & 8)			;

		//Warto�� komparacyjna
		compare[codeno] =
			(	(codeval[7] & 7) << 4	)	|	(	(codeval[6] & 8) << 4	)	|
				(codeval[6] & 7)			|		(codeval[5] & 8)			;

		//Koniec
		codeno++;
		return 0;
	}

	void purgeCheatCodes() {
		codeno = 0;
	}

	void readFromFile(const char* romfname) {

		char temp[1024] = { 0 };
		char codes[256][9] = { 0 };

		strcpy(temp, romfname);
		int ptr = strlen(temp);
		while (true) {
			if (temp[--ptr] == '.') {
				temp[ptr] = 0;
				strcat(temp, ".gg"); break;
			}
			if (ptr == 0) {
				strcat(temp, ".gg"); break;
			}
		}

		FILE* f;
		int letterno = 0, codeno = 0, chr = 0; f = fopen(temp, "rb");
		if (f == NULL) return;

		while (true) {

			chr = getc(f);

			if (chr == '\n' || chr == EOF) {
				addCheatCode(&codes[codeno++][0]);
				if (chr == EOF) break;
				letterno = 0;
			}
			else if (((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z')) && letterno < 8) codes[codeno][letterno++] = chr;

		}

		fclose(f);
	}
}

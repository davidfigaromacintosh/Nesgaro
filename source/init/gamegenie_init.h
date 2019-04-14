//Przydatne info:
//http://nesdev.com/nesgg.txt
//http://tuxnes.sourceforge.net/gamegenie.html
//https://wiki.nesdev.com/w/index.php/Game_Genie#Registers

namespace GAMEGENIE {

	u8 codeno;
	u16 address[256];
	u8 compare[256];
	u8 replace[256];
	b is8long[256];

	//Zwraca wartoœæ szesnastkow¹ danego znaku
	u8 getLetterValue(char lett);

	//Dodaj kod Game Genie
	int addCheatCode(const char*);

	//Za³aduj listê kodów z pliku tekstowego
	void readFromFile(const char*);

	void init();
}
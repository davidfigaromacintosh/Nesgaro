//G³ówna szyna danych konsoli (zapis, odczyt, itd itp...)
//Typów przetwarzania danych w NESie mamy dwa: zapis i odczyt

namespace MAINBUS {

	u16 readAddr(u16 addr);

	// ### ZAPIS ###
	void write(u16 address, u8 value);

	// ### ODCZYT ###
	u8 read(u16 address);

	//Wepchnij do stosu
	void pushStack(u8 value);

	//Wyjmij ze stosu
	u8 pullStack();
}
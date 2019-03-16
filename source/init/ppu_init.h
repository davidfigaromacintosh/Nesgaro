/*

POTRZEBNE INFORMACJE:
http://nesdev.com/PPU%20addressing.txt									O adresowaniu
https://wiki.nesdev.com/w/images/4/4f/Ppu.svg							Wydarzenia dla odpowiednich punktów na ekranie
https://wiki.nesdev.com/w/index.php/PPU_registers						Rejestry PPU
https://wiki.nesdev.com/w/index.php/PPU_scrolling						Wpisy i odczyty do rejestrów $2005 i $2006
http://nesdev.com/NES%20emulation%20discussion.txt						Ogólny poradnik jak renderowaæ itd
https://wiki.nesdev.com/w/index.php/PPU_power_up_state					Status PPU zaraz po w³¹czeniu konsoli
https://wiki.nesdev.com/w/index.php/PPU_programmer_reference			Wszystko
http://thealmightyguru.com/Games/Hacking/Wiki/index.php/NES_Palette		Paleta kolorów

*/

//Rejestry PPU
#define	PPU_CTRL	0x2000
#define	PPU_MASK	0x2001
#define	PPU_STATUS	0x2002
#define	OAM_ADDR	0x2003
#define OAM_DATA	0x2004
#define PPU_SCROLL	0x2005
#define PPU_ADDR	0x2006
#define PPU_DATA	0x2007
#define OAM_DMA		0x4014

#define PPU_BG_PALETTE	0x3f00
#define PPU_SPR_PALETTE	0x3f10

namespace PPU {

	//Ekran
	u16 dot;		//Okreœla numer piksela od pocz¹tku linii
	s16 scanline;	//Numer linii na ekranie: -1 = prescan, od 0 do 239 = widzialne linie, od 240 do 260 = postscan
	u8 oddframe;	//Okreœla, czy numer klatki video jest parzysty czy nie

	//Flagi
	u8 spr0;			//Flaga okreœla, czy nast¹pi³o zdarzenie Sprite 0 Hit
	u8 sproverflow;	//Czy jest Sprite Overflow
	u8 vblank;		//czy jest VBlank

	//Wewnêtrzne rejestry PPU
	/* Rejestr V to adres VRAM, jego bity odpowiadaj¹ nastêpuj¹cym:
		V: yyy NN YYYYY XXXXX
		   ||| || ||||| +++++-- Przewijanie w X
		   ||| || +++++-------- Przewijanie w Y
		   ||| ++-------------- NameTable No.
		   +++----------------- Przewijanie w Y
	*/

	u16	T;			//Tymczasowy adress VRAM
	u16	V;			//Aktualny adres VRAM
	u8	X;			//Fine X scroll
	u8	W;			//Pierwszy lub drugi odczyt
	u8 OAMV;
	u8 readbuffer;

	// Zwi¹zane z VRAM...
	u8 fineX;
	u8 fineY;
	u16 coarseX;
	u16 coarseY;

	SCREEN::Screen *scr;

	//Bity $2000
	u8 NMIenabled;
	u8 PPUmasterslave;
	u8 SPRsize;
	u8 BGpattern;
	u8 SPRpattern;
	u8 VRAMincrement;
	u8 nametable;

	//Bity $2001
	u8 grayscale;
	u8 BGenable8;
	u8 SPRenable8;
	u8 BGenable;
	u8 SPRenable;
	u8 emphasisR;
	u8 emphasisG;
	u8 emphasisB;

	//Paleta kolorów (TODO)
	u32 colors[64] = {
		0x7C7C7CFF,
		0x0000FCFF,
		0x0000BCFF,
		0x4428BCFF,
		0x940084FF,
		0xA80020FF,
		0xA81000FF,
		0x881400FF,
		0x503000FF,
		0x007800FF,
		0x006800FF,
		0x005800FF,
		0x004058FF,
		0x000000FF,
		0x000000FF,
		0x000000FF,
		0xBCBCBCFF,
		0x0078F8FF,
		0x0058F8FF,
		0x6844FCFF,
		0xD800CCFF,
		0xE40058FF,
		0xF83800FF,
		0xE45C10FF,
		0xAC7C00FF,
		0x00B800FF,
		0x00A800FF,
		0x00A844FF,
		0x008888FF,
		0x000000FF,
		0x000000FF,
		0x000000FF,
		0xF8F8F8FF,
		0x3CBCFCFF,
		0x6888FCFF,
		0x9878F8FF,
		0xF878F8FF,
		0xF85898FF,
		0xF87858FF,
		0xFCA044FF,
		0xF8B800FF,
		0xB8F818FF,
		0x58D854FF,
		0x58F898FF,
		0x00E8D8FF,
		0x787878FF,
		0x000000FF,
		0x000000FF,
		0xFCFCFCFF,
		0xA4E4FCFF,
		0xB8B8F8FF,
		0xD8B8F8FF,
		0xF8B8F8FF,
		0xF8A4C0FF,
		0xF0D0B0FF,
		0xFCE0A8FF,
		0xF8D878FF,
		0xD8F878FF,
		0xB8F8B8FF,
		0xB8F8D8FF,
		0x00FCFCFF,
		0xF8D8F8FF,
		0x000000FF,
		0x000000FF
	};

	void init();
	void step();
	void connectScreen(SCREEN::Screen &_scr) {
		scr = &_scr;
	}
	u8 fetchColor();
	u8 fetchTile(bool liteColor);

	//Szyna danych PPU (zapis)
	void writebus(u16 regno, u8 value);

	//Szyna danych PPU (odczyt)
	u8 readbus(u16 regno);
	b renderingEnabled();
}
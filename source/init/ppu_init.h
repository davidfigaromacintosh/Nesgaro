/*

POTRZEBNE INFORMACJE:
http://nesdev.com/PPU%20addressing.txt									O adresowaniu
https://wiki.nesdev.com/w/index.php/PPU_registers						Rejestry PPU
https://wiki.nesdev.com/w/index.php/PPU_scrolling						Wpisy i odczyty do rejestrów $2005 i $2006
http://nesdev.com/NES%20emulation%20discussion.txt						Ogólny poradnik jak renderowaæ itd
https://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png					Wydarzenia dla odpowiednich punktów na ekranie
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
	u16	T;			//Tymczasowy adress VRAM
	u16	V;			//Aktualny adres VRAM
	u8	X;			//X scroll
	u8	W;			//Pierwszy lub drugi odczyt
	u8 OAMV;
	u8 readbuffer;

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
	u32 colors[] = {
		0x7C7C7C00,
		0x0000FC00,
		0x0000BC00,
		0x4428BC00,
		0x94008400,
		0xA8002000,
		0xA8100000,
		0x88140000,
		0x50300000,
		0x00780000,
		0x00680000,
		0x00580000,
		0x00405800,
		0x00000000,
		0x00000000,
		0x00000000,
		0xBCBCBC00,
		0x0078F800,
		0x0058F800,
		0x6844FC00,
		0xD800CC00,
		0xE4005800,
		0xF8380000,
		0xE45C1000,
		0xAC7C0000,
		0x00B80000,
		0x00A80000,
		0x00A84400,
		0x00888800,
		0x00000000,
		0x00000000,
		0x00000000,
		0xF8F8F800,
		0x3CBCFC00,
		0x6888FC00,
		0x9878F800,
		0xF878F800,
		0xF8589800,
		0xF8785800,
		0xFCA04400,
		0xF8B80000,
		0xB8F81800,
		0x58D85400,
		0x58F89800,
		0x00E8D800,
		0x78787800,
		0x00000000,
		0x00000000,
		0xFCFCFC00,
		0xA4E4FC00,
		0xB8B8F800,
		0xD8B8F800,
		0xF8B8F800,
		0xF8A4C000,
		0xF0D0B000,
		0xFCE0A800,
		0xF8D87800,
		0xD8F87800,
		0xB8F8B800,
		0xB8F8D800,
		0x00FCFC00,
		0xF8D8F800,
		0x00000000,
		0x00000000
	};

	void init();
	void step();

	//Szyna danych PPU (zapis)
	void writebus(u16 regno, u8 value);

	//Szyna danych PPU (odczyt)
	u8 readbus(u16 regno);
}
//W razie jakby pojawił się jakiś błąd!
//#define DEBUG_MODE

#ifndef DEBUG_MODE
#pragma comment(linker, "/subsystem:windows")
#else
#pragma comment(linker, "/subsystem:console")
#endif

#define _CRT_SECURE_NO_WARNINGS
#define MASTER_CLOCK 21477272

//LIBy: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>

#include "types.h"

#include "init/mainbus_init.h"
#include "init/controller_init.h"
#include "init/screen_init.h"
#include "init/ppu_init.h"
#include "init/cpu_init.h"
#include "init/apu_init.h"

#include "h/memory.h"
#include "h/mainbus.h"
#include "h/controller.h"
#include "h/screen.h"
#include "h/ppu.h"
#include "h/cpu.h"
#include "h/apu.h"

static bool vsync = false;
int main(int argc, char **argv) {

	srand(static_cast<unsigned int>(time(NULL)));

	float windowScale = 3;
	bool fullScreen = false;

	SCREEN::Screen screen;
	sf::Event wEvent;
	sf::Image windowIcon;

	sf::Sound snd;
	sf::SoundBuffer sbuff;

	sf::RenderWindow window{ sf::VideoMode{(unsigned int)windowScale * 256, (unsigned int)windowScale * 240}, "NESgaro v0.1 alpha", sf::Style::Close | (sf::Uint32)(sf::Style::Fullscreen * fullScreen) }; //= ⬤ ᆺ ⬤ =
	

	#ifdef DEBUG_MODE
	system("title NESgaro mini debugger");
	//system("color 5f");
	
	puts("Preparing, please wait...");

	for (int i = 0; i < 256; i++) {
		
		printf("Opcode: 0x%02x    Mnemonic: %s    Cycles: %d    Length: %d    Mode: %s\n",
			i, CPU::getOpcodeMnemonic(i), CPU::getOpcodeCycle(i), CPU::getOpcodeLength(i), CPU::getOpcodeAddressingModeName(i) );

	}
	#endif

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	windowIcon.loadFromFile("icon.png");
	window.setIcon(16, 16, windowIcon.getPixelsPtr());

	window.clear(sf::Color(0));
	window.display();


	MEM::init();

	//ROMy do testowania

	if (argc > 1) { if (MEM::loadROM(argv[1]) == 0) { window.setTitle(argv[1]); } }

	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\nespeccy.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Palette-Generator.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\350 in 1.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\54-in-1 (Game Star - GK-54) (Menu) (Unl) [!].nes");
	//MEM::loadROM("D:\\NESASM\\nes_asm6502_test2.nes");
	//MEM::loadROM("D:\\NESASM\\mcpong\\mcpong.nes");
	//MEM::loadROM("D:\\NESASM\\mcpong\\McPong (dev 0.1).nes");
	//MEM::loadROM("D:\\NESASM\\Splitscreens\\dest.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Pac-Man.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Pinball.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Mappy.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\F-1 Race.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\donkey kong.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Donkey Kong Jr. Math (USA, Europe).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Donkey Kong 3 (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Battle City (Japan).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Burger Time (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Challenger (Japan).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Paperboy (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Lunar Pool (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Alter_Ego.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Inversion.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Dr Mario.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Tennis (Japan, USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Super Mario Bros. (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Super Mario Bros. (Pirate).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\smb.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Circus Charlie (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Track & Field.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Devil World.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Sky Destroyer (Japan).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Hudson's Adventure Island (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Hokuto no Ken.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Ice Climber.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Bomberman.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Soccer (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Magic Jewelry.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Tetris (USA) (Unl).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Galaxian.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Galaga (Europe).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Road Fighter (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Spy Hunter (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Legend of Kage, The (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Choujikuu Yousai - Macross (Japan).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Duck Maze (Australia) (Unl).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Mario Bros. (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Excitebike.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Gyromite (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Stack-Up (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Duck Hunt (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Wild Gunman (Japan, USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Hogan's Alley (World).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Balloon Fight (USA).nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Family BASIC (Japan) (v1.0) 2.nes");

	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\testroms\\instr_timing\\2-branch_timing.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\testroms\\ppu_vbl_nmi\\nmi_off_timing.nes");

	//MEM::loadROM("C:\\Users\\David Macintosh\\Desktop\\testroms\\other\\RasterChromaLuma.nes");
	//MEM::loadROM("C:\\Users\\David Macintosh\\Desktop\\Magic Jewelry.nes");

	//MEM::loadROM("C:\\Figorrupter\\temp.rom");

	screen.resize(windowScale);
	PPU::loadPalette("palette.pal");
	PPU::init();
	PPU::connectScreen(screen);
	CPU::init();
	APU::init();
	PAD::init();
	PAD::focus(window);

	sf::Int16 samp[] = {
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		+0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff,
		+0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff,
		+0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff,
		+0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff, +0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
		-0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff, -0x7fff,
	};
	sbuff.loadFromSamples(samp, 8*16, 1, 88200);
	snd.setBuffer(sbuff);
	snd.setLoop(true);
	//snd.play();
	snd.setVolume(50);

	while (1) {

		
		PPU::step();
		CPU::step();
		PPU::step();
		PPU::step();

		//SFML Poll
		if (PPU::vblank && !vsync) {

			vsync = true;
			while (window.pollEvent(wEvent)) {

				switch (wEvent.type) {

					case sf::Event::Closed: {
						window.close();
						return 0xF19A20;
					}

				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
				snd.setPitch(7);
			} else {
				snd.setPitch(1);
			}

			//window.clear(sf::Color(PPU::colors[MEM::VRAM[0x3f00]]));
			window.draw(screen);
			window.display();
		}
		if (!PPU::vblank && vsync) {
			vsync = false;
		}
		
	}

	return 0xF19A20;
}
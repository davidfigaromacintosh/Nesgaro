//W razie jakby pojawi³ siê jakiœ b³¹d!
//#define DEBUG_MODE

#ifndef DEBUG_MODE
#pragma comment(linker, "/subsystem:windows")
#else
#pragma comment(linker, "/subsystem:console")
#endif

#define _CRT_SECURE_NO_WARNINGS
#define MASTER_CLOCK 21477272

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <stdio.h>

#include "types.h"

#include "init/mainbus_init.h"
#include "init/screen_init.h"
#include "init/ppu_init.h"
#include "init/cpu_init.h"

#include "h/memory.h"
#include "h/mainbus.h"
#include "h/screen.h"
#include "h/ppu.h"
#include "h/cpu.h"

static bool vsync = false;
int main(int _argc, char **_argv) {

	sf::Image windowIcon;

	sf::RenderWindow window{ sf::VideoMode{256*3, 240*3}, "NESgaro v0.1 alpha", sf::Style::Close};
	sf::Event wEvent;
	
	#ifdef DEBUG_MODE
	system("title NESgaro mini debugger");
	//system("color 5f");
	
	puts("Preparing, please wait...");

	for (int i = 0; i < 256; i++) {
		
		printf("Opcode: 0x%02x    Mnemonic: %s    Cycles: %d    Length: %d    Mode: %s\n",
			i, CPU::getOpcodeMnemonic(i), CPU::getOpcodeCycle(i), CPU::getOpcodeLength(i), CPU::getOpcodeAddressingModeName(i) );

	}
	#endif

	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);
	window.display();

	windowIcon.loadFromFile("icon.png");
	window.setIcon(16, 16, windowIcon.getPixelsPtr());

	MEM::init();
	//MEM::loadROM("D:\\NESASM\\nes_asm6502_test2.nes");
	//MEM::loadROM("D:\\NESASM\\mcpong\\McPong (dev 0.1).nes");
	MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Pac-Man.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\F-1 Race.nes");
	//MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\Mario Bros. (World).nes");

	PPU::init();
	CPU::init();

	while (1) {

		PPU::step();
		PPU::step();
		PPU::step();
		CPU::step();

		//SFML Poll
		if (PPU::vblank && !vsync) {

			vsync = true;
			window.pollEvent(wEvent);
			if (wEvent.type == sf::Event::Closed) {
				window.close();
				return 0xF19A20;
			}

			window.clear(sf::Color(PPU::colors[MEM::VRAM[0x3f05]]));
			//window.draw(screen);
			window.display();
		}
		if (!PPU::vblank && vsync) {
			vsync = false;
		}
		
	}

	return 0xF19A20;
}
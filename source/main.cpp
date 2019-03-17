//W razie jakby pojawił się jakiś błąd!
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
#include "init/controller_init.h"
#include "init/screen_init.h"
#include "init/ppu_init.h"
#include "init/cpu_init.h"

#include "h/memory.h"
#include "h/mainbus.h"
#include "h/controller.h"
#include "h/screen.h"
#include "h/ppu.h"
#include "h/cpu.h"

static bool vsync = false;
int main(int _argc, char **_argv) {

	srand(static_cast<unsigned int>(time(NULL)));

	float windowScale = 2;

	SCREEN::Screen screen;

	sf::Image windowIcon;

	sf::RenderWindow window{ sf::VideoMode{(unsigned int)windowScale * 256, (unsigned int)windowScale * 240}, "NESgaro v0.1 alpha", sf::Style::Close}; //= ⬤ ᆺ ⬤ =
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

	windowIcon.loadFromFile("icon.png");
	window.setIcon(16, 16, windowIcon.getPixelsPtr());

	window.display();


	MEM::init();

	//ROMy do testowania
	MEM::loadROM("D:\\PENDRIVE BACKUP (G)\\nes\\testroms\\nestest.nes");

	screen.resize(windowScale);
	PPU::init();
	PPU::connectScreen(screen);
	CPU::init();
	PAD::init();

	while (1) {

		PPU::step();
		PPU::step();
		PPU::step();
		CPU::step();

		//SFML Poll
		if (PPU::vblank && !vsync) {

			vsync = true;
			window.pollEvent(wEvent);

			switch (wEvent.type) {

				case sf::Event::Closed: {
					window.close();
					return 0xF19A20;
				}
			
			}

			window.draw(screen);
			window.display();
		}
		if (!PPU::vblank && vsync) {
			vsync = false;
		}
		
	}

	return 0xF19A20;
}
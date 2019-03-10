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

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <chrono>

#include "types.h"

#include "init/mainbus_init.h"
#include "init/ppu_init.h"
#include "init/cpu_init.h"

#include "h/memory.h"
#include "h/mainbus.h"
#include "h/ppu.h"
#include "h/cpu.h"

int main(int _argc, char **_argv) {

	sf::Image windowIcon;

	sf::RenderWindow window{ sf::VideoMode{256 * 3, 240 * 3}, "", sf::Style::Close};
	sf::Event wEvent;

	#ifdef DEBUG_MODE
	SetConsoleTitleA("NESgaro ^-^");
	system("color 5f");
	
	puts("Preparing, please wait...");

	for (int i = 0; i < 256; i++) {
		
		printf("Opcode: 0x%02x    Mnemonic: %s    Cycles: %d    Length: %d    Mode: %s\n",
			i, CPU::getOpcodeMnemonic(i), CPU::getOpcodeCycle(i), CPU::getOpcodeLength(i), CPU::getOpcodeAddressingModeName(i) );

	}
	#endif

	window.display();
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(60);

	windowIcon.loadFromFile("icon.png");
	window.setIcon(16, 16, windowIcon.getPixelsPtr());

	MEM::init();
	MEM::loadROM("D:\\NESASM\\nes_asm6502_test2.nes");
	PPU::init();
	CPU::init();

	while (1) {

		PPU::step();
		PPU::step();
		PPU::step();
		CPU::step();

		//SFML Poll
		if (PPU::dot == 1 && PPU::scanline == -1) {

			window.clear(sf::Color(PPU::colors[0]));

			window.pollEvent(wEvent);
			if (wEvent.type == sf::Event::Closed) {
				window.close();
				return 0xF19A20;
			}

			window.display();
		}
		
	}

	return 0xF19A20;
}
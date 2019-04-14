//W razie jakby pojawił się jakiś błąd!
//#define DEBUG_MODE

#ifndef DEBUG_MODE
#pragma comment(linker, "/subsystem:windows")
#else
#pragma comment(linker, "/subsystem:console")
#endif

//#pragma comment(lib, "ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#define NESGARO_VERSION "v0.42 alpha"

#define NTSC		0
#define PAL			1
#define DENDY		2

static int tvregion = NTSC;

//LIBy: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#ifdef DEBUG_MODE
#include <stdio.h>
#endif
#include <string>
#include <iostream>

#include "include/Nes_Apu.h"
#include "include/Sound_Queue.h"

#include <Windows.h>
#include <winhttp.h>
#include "types.h"

#include "init/mainbus_init.h"
#include "init/mapper_init.h"
#include "init/controller_init.h"
#include "init/screen_init.h"
#include "init/ppu_init.h"
#include "init/cpu_init.h"
#include "init/apu_init.h"
#include "init/gamegenie_init.h"
#include "init/gui_init.h"

#include "h/memory.h"
#include "h/mainbus.h"
#include "h/mapper.h"
#include "h/controller.h"
#include "h/screen.h"
#include "h/ppu.h"
#include "h/cpu.h"
#include "h/apu.h"
#include "h/gamegenie.h"
#include "h/gui.h"

static bool vsync = false;



int _NESGARO(int argc, char **argv) {

	srand(static_cast<unsigned int>(time(NULL)));

	float windowScale = 3;
	bool fullScreen = false;

	unsigned int fps[] = { 60, 50, 50 };

	SCREEN::Screen screen;
	sf::Event wEvent;
	sf::Image windowIcon;

	sf::RenderWindow window{ sf::VideoMode{(unsigned int)windowScale * 256, (unsigned int)windowScale * 224}, GUI::getNesgaroTitle(), sf::Style::Close | (sf::Uint32)(sf::Style::Fullscreen * fullScreen) }; //= ⬤ ᆺ ⬤ =

	#ifdef DEBUG_MODE
	system("title Nesgaro mini debugger");
	//system("color 5f");

	puts("Preparing, please wait...");

	for (int i = 0; i < 256; i++) {

		printf("Opcode: 0x%02x    Mnemonic: %s    Cycles: %d    Length: %d    Mode: %s\n",
			i, CPU::getOpcodeMnemonic(i), CPU::opcodeCycle[i], CPU::getOpcodeLength(i), CPU::getOpcodeAddressingModeName(i));

	}
	#endif

	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(fps[tvregion]);

	if (windowIcon.loadFromFile(GUI::getCurPath("\\resources\\icon.png"))) {
		window.setIcon(16, 16, windowIcon.getPixelsPtr());
	}

	window.clear(sf::Color(0));
	window.display();

	MEM::init();
	MAPPER::init();
	PPU::init();
	CPU::init();
	APU::init();
	GAMEGENIE::init();
	PAD::init();

	screen.resize(windowScale);
	PPU::loadPalette(GUI::getCurPath("\\resources\\palette.pal"));
	PPU::connectScreen(screen);
	APU::setVolume(0.125);
	PAD::focus(window);

	//ROMy do testowania

	if (argc > 1) {
		MEM::loadROM(argv[1]); window.setTitle(GUI::getNesgaroTitle(GUI::getFileName(argv[1])));
	}
	else {
		MEM::loadROM(GUI::getCurPath("\\resources\\hello.nes"));
	}

	//if (MessageBoxA(NULL, "A new version of Nesgaro is available. Would you like to download it now?", "An update is available", MB_YESNO) == IDYES) {
	//	ShellExecuteA(NULL, "open", "https://nes.figaro.ga/download", NULL, NULL, SW_SHOWNORMAL);
	//}


	u64 masterclock = 0;
	bool vsync = false;
	//Klatka video
	while (1) {

		if (tvregion == NTSC || tvregion == DENDY) {

			if (masterclock % 3 == 0)		CPU::step();	//Cykl CPU dla standardu NTSC
			if (masterclock % 1 == 0)		PPU::step();	//Cykl PPU dla standardu NTSC

		}

		if (tvregion == PAL) {

			if (masterclock % 16 == 0)		CPU::step();	//Cykl CPU dla standardu PAL
			if (masterclock % 5 == 0)		PPU::step();	//Cykl PPU dla standardu PAL

		}

		masterclock += 1;

		//SFML Poll
		if (PPU::scanline >= 240 && !vsync) {

			vsync = true;

			APU::run_frame(CPU::APUelapsed);
			CPU::APUelapsed = 0;

			while (window.pollEvent(wEvent)) {
				switch (wEvent.type) {

					case sf::Event::Closed: {
						window.close();
						return 0xF19A20;
					}

					case sf::Event::KeyPressed: {
						if (window.hasFocus()) {

							//Quit
							if (wEvent.key.code == sf::Keyboard::Escape) {
								window.close();
								return 0xF19A20;
							}

							//Hard reset
							if ((wEvent.key.code == sf::Keyboard::T) /*&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)*/) {
								GUI::power();
							}

							//Soft reset
							else if ((wEvent.key.code == sf::Keyboard::R) /*&& sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)*/) {
								GUI::reset();
							}

						}
					}

				}
			}

			//window.clear(sf::Color(PPU::colors[0x0f]));
			window.draw(screen);
			window.display();

		}

		if (PPU::scanline < 240 && vsync) {
			vsync = false;
		}
	}

	return 0xF19A20;
}
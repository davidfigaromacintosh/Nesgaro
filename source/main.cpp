﻿//W razie jakby pojawił się jakiś błąd!
//#define DEBUG_MODE

#ifndef DEBUG_MODE
#pragma comment(linker, "/subsystem:windows")
#else
#pragma comment(linker, "/subsystem:console")
#endif

//#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winhttp.lib")

#define _CRT_SECURE_NO_WARNINGS

#define NESGARO_VERSION "v0.45 alpha"

//LIBy: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#define NTSC		0
#define PAL			1
#define DENDY		2

#define NES_WIDTH	256
#define NES_HEIGHT	224

static int tvregion = NTSC;
static sf::RenderWindow* window;

#ifdef DEBUG_MODE
#include <stdio.h>
#endif

#include <string>
//#include <chrono>
//#include <thread>
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

static SCREEN::Screen* screen;

static bool vsync = false;

int _NESGARO(int argc, char **argv) {

	srand(static_cast<unsigned int>(time(NULL)));

	float windowScale = 3;
	bool fullScreen = false;
	char winTitle[1024] = { 0 };

	unsigned int fps[] = { 60, 50, 50 };

	sf::Event wEvent;
	sf::Image windowIcon;

	strcpy(winTitle, GUI::getNesgaroTitle());
	window = new sf::RenderWindow{ sf::VideoMode{(unsigned int)windowScale * NES_WIDTH, (unsigned int)windowScale * NES_HEIGHT}, "Loading... =^_^=", sf::Style::Default | (sf::Uint32)(sf::Style::Fullscreen * fullScreen) }; //= ⬤ ᆺ ⬤ =
	screen = new SCREEN::Screen();

	#ifdef DEBUG_MODE
	system("title Nesgaro mini debugger");
	//system("color 5f");

	puts("Preparing, please wait...");

	for (int i = 0; i < 256; i++) {

		printf("Opcode: 0x%02x    Mnemonic: %s    Cycles: %d    Length: %d    Mode: %s\n",
			i, CPU::getOpcodeMnemonic(i), CPU::opcodeCycle[i], CPU::getOpcodeLength(i), CPU::getOpcodeAddressingModeName(i));

	}
	#endif

	window->setKeyRepeatEnabled(false);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(fps[tvregion]);

	if (windowIcon.loadFromFile(GUI::getCurPath("\\resources\\icon.png"))) {
		window->setIcon(16, 16, windowIcon.getPixelsPtr());
	}

	window->clear(sf::Color(0));
	window->display();

	MEM::init();
	MAPPER::init();
	PPU::init();
	CPU::init();
	APU::init();
	GAMEGENIE::init();
	PAD::init();
	screen->resize(windowScale);
	PPU::loadPalette(GUI::getCurPath("\\resources\\palette.pal"));
	PPU::connectScreen(screen);
	APU::setVolume(0.25);

	//ROMy do testowania

	if (argc > 1) {
		MEM::loadROM(argv[1]);
		GAMEGENIE::purgeCheatCodes(); GAMEGENIE::readFromFile(argv[1]);
		strcpy(winTitle, GUI::getNesgaroTitle(GUI::getFileName(argv[1], false)));
	}
	else {
		MEM::loadROM(GUI::getCurPath("\\resources\\hello.nes"));
	}

	//Tutaj jest ciekawie, bo emulator wysyła requesta do strony "https://nes.figaro.ga/?ver" requesta i porównuje wersje. Jeśli są różne, wyskoczy komunikat o updacie
	HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL; bool bResults = false; DWORD dwSize = 0, dwDownloaded = 0; char dwVersion[64] = { 0 }, notifyV[256] = { 0 };

	//Tworzymy sesję
	hSession = WinHttpOpen(L"WinHTTP Nesgaro/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	//Gdzie
	if (hSession)
		hConnect = WinHttpConnect(hSession, L"nes.figaro.ga", 443, 0);

	//Tworzymy requesta
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/?ver", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	//Wysyłamy requesta
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

	//Otrzymaj odpowiedź
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	//Jeśli wszystko poszło OK
	if (bResults) {

		if (WinHttpQueryDataAvailable(hRequest, &dwSize) && WinHttpReadData(hRequest, (void*)dwVersion, dwSize, &dwDownloaded) && _stricmp(dwVersion, NESGARO_VERSION)) {

			sprintf(notifyV, "A new version of Nesgaro is available to download: %s.\nWould you like to download it now?", dwVersion);
			if (MessageBoxA(NULL, notifyV, "Update", MB_YESNO) == IDYES) {
				ShellExecuteA(NULL, "open", "https://nes.figaro.ga/", NULL, NULL, SW_SHOWNORMAL);
			}

		}

	}

	//Sprzątamy po sobie
	if (hSession) WinHttpCloseHandle(hSession);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hRequest) WinHttpCloseHandle(hRequest);

	window->setTitle(winTitle);

	//Główna pętla (tutaj odprawia się cała emulacja)
	u64 masterclock = 0;
	bool vsync = false;
	while (window->isOpen()) {

		//NTSC
		if (tvregion == NTSC || tvregion == DENDY) {

			if (masterclock % 3 == 0)		CPU::step();	//Cykl CPU dla standardu NTSC
			if (masterclock % 1 == 0)		PPU::step();	//Cykl PPU dla standardu NTSC

		}

		//PAL
		if (tvregion == PAL) {

			if (masterclock % 16 == 0)		CPU::step();	//Cykl CPU dla standardu PAL
			if (masterclock % 5 == 0)		PPU::step();	//Cykl PPU dla standardu PAL

		} masterclock += 1;

		//SFML Poll
		if (PPU::scanline >= 240 && !vsync) {

			vsync = true;

			APU::run_frame(CPU::APUelapsed);
			CPU::APUelapsed = 0;

			while (window->pollEvent(wEvent)) {
				switch (wEvent.type) {

					case sf::Event::Closed: {
						window->close();
						return 0xF19A20;
					}

					case sf::Event::Resized: {
						window->setSize(sf::Vector2u(
							window->getSize().x < NES_WIDTH ? NES_WIDTH : window->getSize().x,
							window->getSize().y < NES_HEIGHT ? NES_HEIGHT : window->getSize().y
						));
						window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)window->getSize().x, (float)window->getSize().y)));
						screen->resize();
						break;
					}

					case sf::Event::KeyPressed: {

						if (window->hasFocus()) {

							//Quit
							if (wEvent.key.code == sf::Keyboard::Escape) {
								window->close();
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

							//Fullscreen
							if ((wEvent.key.code == sf::Keyboard::F4)) {
								fullScreen = !fullScreen;

								delete window,
								window = new sf::RenderWindow{ sf::VideoMode{(unsigned int)windowScale * NES_WIDTH, (unsigned int)windowScale * NES_HEIGHT}, "Loading... =^_^=", sf::Style::Default | (sf::Uint32)(sf::Style::Fullscreen * fullScreen) }; //= ⬤ ᆺ ⬤ =
								screen->resize();
								window->setTitle(winTitle);
								window->setIcon(16, 16, windowIcon.getPixelsPtr());
								window->requestFocus();
								
							}

						}

						break;
					}

				}
			}

			window->clear(sf::Color(PPU::colors[0x0d]));
			window->draw(*screen);
			window->display();

			
		}

		if (PPU::scanline < 240 && vsync) {
			vsync = false;
		}
	}

	return 0xF19A20;
}
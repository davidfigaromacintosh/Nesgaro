#pragma once

//Joystick

#define JOYPAD1 0x4016
#define JOYPAD2 0x4017

#define BN_A		7
#define BN_B		6

#define BN_SELECT	5
#define BN_START	4

#define BN_UP		3
#define BN_DOWN		2
#define BN_LEFT		1
#define BN_RIGHT	0

namespace PAD {

	sf::Window *win;
	b isStrobing;
	u8 status;

	sf::Keyboard::Key keys[] = {
		sf::Keyboard::Right,
		sf::Keyboard::Left,

		sf::Keyboard::Down,
		sf::Keyboard::Up,

		sf::Keyboard::Space,
		sf::Keyboard::Enter,
		sf::Keyboard::Z,
		sf::Keyboard::X
	};
	
	void init();

	void focus(sf::Window &wind);
	void strobe(u8 value);
	u8 read();
}
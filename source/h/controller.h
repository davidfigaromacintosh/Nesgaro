#pragma once

namespace PAD {
	
	void init() {
		isStrobing = false;
	}

	void strobe(u8 value) {

		isStrobing = value & 0b00000001;
		if (isStrobing) {
			for (int i = 0; i < 8; i++) {
				bool butt = sf::Keyboard::isKeyPressed(keys[i]);
				if (i == BN_LEFT	&& sf::Keyboard::isKeyPressed(keys[BN_RIGHT]))	butt = false;
				if (i == BN_RIGHT	&& sf::Keyboard::isKeyPressed(keys[BN_LEFT]))	butt = false;
				if (i == BN_UP		&& sf::Keyboard::isKeyPressed(keys[BN_DOWN]))	butt = false;
				if (i == BN_DOWN	&& sf::Keyboard::isKeyPressed(keys[BN_UP]))		butt = false;
				status = status << 1;
				status = status | (butt && window->hasFocus());
			}
		}
	}

	u8 read() {
		u8 retvalue = status & 0b00000001;
		status = status >> 1;
		return retvalue | 0x40;
	}

}
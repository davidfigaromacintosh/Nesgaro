#pragma once

namespace PAD {
	
	void init() {
		isStrobing = false;
	}

	void strobe(u8 value) {

		isStrobing = value & 0b00000001;
		if (isStrobing) {
			for (int i = 0; i < 8; i++) {
				status = status << 1;
				status = status | sf::Keyboard::isKeyPressed(keys[i]);
			}
		}
	}

	u8 read() {
		u8 retvalue = status & 0b00000001;
		status = status >> 1;
		return retvalue;
	}

}
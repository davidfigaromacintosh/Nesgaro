#pragma once

namespace SCREEN {

	Screen::Screen() {
		scale = 2.0;
		pixel.resize(256 * 240 * 6);
		pixel.setPrimitiveType(sf::Triangles);

		for (int j = 0; j < 240; j++) {
			for (int i = 0; i < 256; i++) {

				int index = 6 * (i + 256 * j);
				sf::Vector2f origin(scale * i, scale * j);

				//Jeden piksel jest kwadratem sk³adaj¹cym siê z dwóch trójk¹tów

				pixel[index].color		= sf::Color(PPU::colors[0]);
				pixel[index+1].color	= sf::Color(PPU::colors[0]);
				pixel[index+2].color	= sf::Color(PPU::colors[0]);

				pixel[index+3].color	= sf::Color(PPU::colors[0]);
				pixel[index+4].color	= sf::Color(PPU::colors[0]);
				pixel[index+5].color	= sf::Color(PPU::colors[0]);
			}
		}
	}

	void Screen::rescale() {

		for (int j = 0; j < 240; j++) {
			for (int i = 0; i < 256; i++) {

				int index = 6 * (i + 256 * j);

				int offx = (int)((-scale / 2.0) * NES_WIDTH + (window->getSize().x / 2));

				int offy = (int)((-scale / 2.0) * NES_HEIGHT + (window->getSize().y / 2));

				sf::Vector2f *origin;
                if ( (i >= ((256 - NES_WIDTH) / 2)) && (i < (256 - (256 - NES_WIDTH) / 2)) && (j >= ((240 - NES_HEIGHT) / 2)) && (j < (240 - (240 - NES_HEIGHT) / 2)) )
				origin = new sf::Vector2f(scale * (i - (256 - NES_WIDTH) / 2) + offx, scale * (j - (240 - NES_HEIGHT) / 2) + offy);
                else
                origin = new sf::Vector2f(-scale, -scale);

				//Jeden piksel jest kwadratem sk³adaj¹cym siê z dwóch trójk¹tów

				pixel[index].position		= *origin;
				pixel[index].color			= sf::Color(PPU::colors[0]);
				pixel[index + 1].position	= *origin + sf::Vector2f(scale, 0);
				pixel[index + 1].color		= sf::Color(PPU::colors[0]);
				pixel[index + 2].position	= *origin + sf::Vector2f(scale, scale);
				pixel[index + 2].color		= sf::Color(PPU::colors[0]);

				pixel[index + 3].position	= *origin + sf::Vector2f(scale, scale);
				pixel[index + 3].color		= sf::Color(PPU::colors[0]);
				pixel[index + 4].position	= *origin + sf::Vector2f(0, scale);
				pixel[index + 4].color		= sf::Color(PPU::colors[0]);
				pixel[index + 5].position	= *origin;
				pixel[index + 5].color		= sf::Color(PPU::colors[0]);

				delete origin;
			}
		}

	}

	void Screen::resize(float _scale = ((float)std::max(1, (int)std::min(window->getSize().x / NES_WIDTH, window->getSize().y / NES_HEIGHT)))) {
		scale = _scale;
		rescale();

	}

	void Screen::put(u8 x, u8 y, u8 color) {

		int index = 6 * (x + 256 * y);
		sf::Vector2f origin(scale * x, scale * y);

		//Jeden piksel jest kwadratem sk³adaj¹cym siê z dwóch trójk¹tów

		pixel[index].color		= sf::Color(PPU::colors[color & 0x3f]);
		pixel[index + 1].color	= sf::Color(PPU::colors[color & 0x3f]);
		pixel[index + 2].color	= sf::Color(PPU::colors[color & 0x3f]);

		pixel[index + 3].color	= sf::Color(PPU::colors[color & 0x3f]);
		pixel[index + 4].color	= sf::Color(PPU::colors[color & 0x3f]);
		pixel[index + 5].color	= sf::Color(PPU::colors[color & 0x3f]);
	}

	void Screen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(pixel, states);
	}

}

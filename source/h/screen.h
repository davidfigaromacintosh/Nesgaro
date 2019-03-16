namespace SCREEN {

	Screen::Screen() {
		pixel.resize(256 * 240 * 6);
		pixel.setPrimitiveType(sf::Triangles);

		for (int j = 0; j < 240; j++) {
			for (int i = 0; i < 256; i++) {

				int index = 6 * (i + 256 * j);
				sf::Vector2f origin(scale * i, scale * j);

				//Jeden piksel jest kwadratem sk�adaj�cym si� z dw�ch tr�jk�t�w

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
				sf::Vector2f origin(scale * i, scale * j);

				//Jeden piksel jest kwadratem sk�adaj�cym si� z dw�ch tr�jk�t�w

				pixel[index].position		= origin;
				pixel[index].color			= sf::Color(PPU::colors[0]);
				pixel[index + 1].position	= origin + sf::Vector2f(scale, 0);
				pixel[index + 1].color		= sf::Color(PPU::colors[0]);
				pixel[index + 2].position	= origin + sf::Vector2f(scale, scale);
				pixel[index + 2].color		= sf::Color(PPU::colors[0]);

				pixel[index + 3].position	= origin + sf::Vector2f(scale, scale);
				pixel[index + 3].color		= sf::Color(PPU::colors[0]);
				pixel[index + 4].position	= origin + sf::Vector2f(0, scale);
				pixel[index + 4].color		= sf::Color(PPU::colors[0]);
				pixel[index + 5].position	= origin;
				pixel[index + 5].color		= sf::Color(PPU::colors[0]);
			}
		}

	}

	void Screen::resize(float _scale) {
		scale = _scale;
		rescale();

	}

	void Screen::put(u8 x, u8 y, u8 color) {

		int index = 6 * (x + 256 * y);
		sf::Vector2f origin(scale * x, scale * y);

		//Jeden piksel jest kwadratem sk�adaj�cym si� z dw�ch tr�jk�t�w

		pixel[index].color		= sf::Color(PPU::colors[color % 64]);
		pixel[index + 1].color	= sf::Color(PPU::colors[color % 64]);
		pixel[index + 2].color	= sf::Color(PPU::colors[color % 64]);

		pixel[index + 3].color	= sf::Color(PPU::colors[color % 64]);
		pixel[index + 4].color	= sf::Color(PPU::colors[color % 64]);
		pixel[index + 5].color	= sf::Color(PPU::colors[color % 64]);
	}

	void Screen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(pixel, states);
	}

}
#pragma once

namespace SCREEN {

	class Screen : public sf::Drawable {

		public:

			Screen();

			void put(u8 x, u8 y, u8 color);

			void resize(float scale);

		private:

			void rescale();

			sf::VertexArray pixel;

			float scale;

			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	};

}
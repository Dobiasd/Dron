/*
 * Dron (Dobi's Tron/Snake game)
 * Copyright (C) 2012 Tobias Hermann

 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DRON_PLASMA_H_
#define DRON_PLASMA_H_

#include <SFML/Graphics.hpp>

#include <random>
#include <array>

namespace Dron
{

/*
 * A simple plasma effect generator
 * Multiple sine functions are overlayed for every color channel.
 *
 * The factors are initialized with random values to provide some variety.
 */
class Plasma
{
public:
	Plasma(int width = 160, int height = 100);

	// Calculate next frame
	bool Update(float elapsedTimeSum);

	// Display last calculated frame
	bool Display(sf::RenderTarget& renderTarget) const;

private:
	typedef std::array<double, 1024> SinusTable;
	SinusTable sinusTable_;

	// 3 Channels, 4 overlays per channel and 3 values per channel overlay
	typedef std::array<double, 3 * 3 * 4> PlasmaFactors;
	PlasmaFactors plasmaFactors_;

	// Helper structure for easier pixel access.
	struct RGBA
	{
		RGBA(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a = 255) :
				r_(r), g_(g), b_(b), a_(a)
		{
		}
		sf::Uint8 r_, g_, b_, a_;
	};

	// For initializing the factors
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;

	// The current frame
	std::vector<RGBA> pixels_;
	sf::Image image_;

	// The size
	int width_;
	int height_;
};

} /* namespace Dron */

#endif /* DRON_PLASMA_H_ */

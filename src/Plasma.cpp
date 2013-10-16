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

#include "Plasma.h"

#include "Pi.h"

namespace Dron
{
Plasma::Plasma(int width, int height) :
		randomGenerator_(randomDevice_()), width_(width), height_(height)
{
	std::uniform_real_distribution<> randomDoubleDistributionPlasmaFactors(-8., 8.);

	// Precalculate sine values into a LUT to increase performance.
	for (SinusTable::size_type i(0); i < 1024; ++i)
	{
		sinusTable_[i] = static_cast<double>(std::sin(i * pi / 512.));
	}

	// Random initialisation of the factors
	for (PlasmaFactors::size_type i(0); i < 3 * 3 * 4; ++i)
	{
		plasmaFactors_[i] = static_cast<double>(randomDoubleDistributionPlasmaFactors(randomGenerator_));
	}
}

bool Plasma::Update(float elapsedTimeSum)
{
	pixels_ = std::vector<RGBA>(width_ * height_, RGBA(0, 0, 0));
	for (int y(0); y < height_; ++y)
	{
		for (int x(0); x < width_; ++x)
		{
			std::array<double, 3> color;
			for (PlasmaFactors::size_type c(0); c < 3; ++c)
			{
				color[c] = 0.;
				for (PlasmaFactors::size_type f(0); f < 4; ++f)
				{
					color[c] += sinusTable_[static_cast<int>(std::abs(
							plasmaFactors_[3 * 4 * c + 4 * f + 0] * 3. * static_cast<double>(y)
									+ plasmaFactors_[3 * 4 * c + 4 * f + 1] * 3 * static_cast<double>(x)
									+ plasmaFactors_[3 * 4 * c + 4 * f + 2] * 100.
											* static_cast<double>(elapsedTimeSum))) % 1024];
				}
			}

			pixels_[y * width_ + x] = RGBA(static_cast<sf::Uint8>((color[0] + 4.) * 63. / 8.),
					static_cast<sf::Uint8>((color[1] + 4.) * 15. / 8.),
					static_cast<sf::Uint8>((color[2] + 4.) * 31. / 8.));
		}
	}
	image_ = sf::Image(width_, height_, &pixels_[0].r_);
	return true;
}

bool Plasma::Display(sf::RenderTarget& renderTarget) const
{
	sf::Sprite sprite_(image_);
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	sprite_.Resize(width, height);
	renderTarget.Draw(sprite_);
	return true;
}

} /* namespace Dron */

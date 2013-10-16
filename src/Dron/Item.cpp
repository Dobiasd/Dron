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

#include "Item.h"

#include "GameStates/PlayView.h"

#include "../Synthesizer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace Dron
{

Item::Item(const Position& position, std::size_t remainingSteps) :
		position_(position), remainingSteps_(remainingSteps)
{
	Synthesizer::PlaySound("NewItem");
}

void Item::DrawRect(const Rect& rect, sf::RenderTarget& renderTarget, const sf::Color& color)
{
	PlayView::DrawRect(rect, renderTarget, color);
}

void Item::Decay()
{
	if (remainingSteps_)
	{
		--remainingSteps_;
		if (!remainingSteps_)
			Synthesizer::PlaySound("ItemDecayed");
	}
}

bool Item::IsDecayed()
{
	return !remainingSteps_;
}

} /* namespace Dron */

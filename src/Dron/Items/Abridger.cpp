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

#include "Abridger.h"

#include "../World.h"
#include "../Player.h"
#include "../Animations/CollectAnimation.h"

#include <iostream>

namespace Dron
{

Abridger::Abridger(const Position& position, std::size_t remainingSteps) :
		Item(position, remainingSteps)
{
}

void Abridger::Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
{
	Rect itemRect(rect.Left + 1, rect.Top + 1, rect.Right - 1, rect.Bottom - 1);
	Item::DrawRect(itemRect, renderTarget, sf::Color(127, 255, 0));
}

// The player shrinks at contact.
bool Abridger::GetUsedImmediately(Player& player, World& world)
{
	std::cout << player.GetName() << " shrunk." << std::endl;
	player.ShrinkToMinLength();
	world.AddAnimationPtr(
			AnimationPtr(
					new CollectAnimation(sf::Color(127, 255, 0), position_,
							player.GetName() + " used an " + GetName() + ".")));
	return true;
}

std::string Abridger::GetName() const
{
	return "Abridger";
}

} /* namespace Dron */

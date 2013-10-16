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

#include "BatteringRam.h"
#include "../Player.h"
#include "../World.h"
#include "../Animations/BatteringRamAnimation.h"
#include "../Animations/CollectAnimation.h"
#include "../../Synthesizer.h"
#include "../GameStates/PlayView.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <iostream>
#include <memory>

namespace Dron
{

BatteringRam::BatteringRam(const Position& position, std::size_t remainingSteps) :
		Item(position, remainingSteps)
{
}

void BatteringRam::Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
{
	Rect itemRect(rect.Left + 1, rect.Top + 1, rect.Right - 1, rect.Bottom - 1);
	Item::DrawRect(itemRect, renderTarget, sf::Color(255, 127, 0));
}

bool BatteringRam::HitWall(const Position& pos, Player& player, World& world)
{
	world.RemoveWallPosition(pos);
	std::cout << player.GetName() << " used a Battering Ram while hitting a wall" << std::endl;
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(PlayView::GetWallColor(), pos)));
	return true;
}

bool BatteringRam::HitSelf(const Position& pos, Player& player, World& world)
{
	player.RemovePosition(pos, world);
	std::cout << player.GetName() << " used a Battering Ram while hitting himself" << std::endl;
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(player.GetColor(), pos)));
	return true;
}

bool BatteringRam::HitOtherPlayer(const Position& pos, Player& player, Player& other, World& world)
{
	std::cout << player.GetName() << " used a Battering Ram while hitting " << other.GetName() << std::endl;
	other.RemovePosition(pos, world);
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(other.GetColor(), pos)));
	return true;
}

bool BatteringRam::GetCollected(Player& player, World& world)
{
	world.AddAnimationPtr(
			AnimationPtr(
					new CollectAnimation(sf::Color(255, 127, 0), position_,
							player.GetName() + " collected a " + GetName() + ".")));
	return true;
}

std::string BatteringRam::GetName() const
{
	return "Battering Ram";
}

} /* namespace Dron */

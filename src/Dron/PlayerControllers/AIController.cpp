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

#include "AIController.h"

#include "../Player.h"
#include "../GameStates/Play.h"

#include <algorithm>

namespace Dron
{

AIController::Directions InitPossibleDirections()
{
	AIController::Directions result;
	result.push_back(AIController::Vector(0, 1));
	result.push_back(AIController::Vector(0, -1));
	result.push_back(AIController::Vector(1, 0));
	result.push_back(AIController::Vector(-1, 0));
	return result;
}

AIController::AIController(const std::string& name, double randomness) :
		PlayerController(name), randomGenerator_(randomDevice_()), randomDoubleDistribution_(0., 1.), possibleDirections_(
				InitPossibleDirections()), randomness_(randomness)
{
}

void AIController::CalculateNextDirection(const World& world, const Player& player, ConstPlayerPtrs otherPlayerPtrs)
{
	ConstPlayerPtrs playerPtrs(otherPlayerPtrs);
	World::Positions occupiedPositions(world.GetOccupiedPositions(player, playerPtrs));

	// Shuffle to prepare eventual random chance in direction.
	std::random_shuffle(std::begin(possibleDirections_), std::end(possibleDirections_));
	Directions directions;

	// The last used direction is the default.
	if (player.GetLastDirection() != Vector(0, 0))
		directions.push_back(player.GetLastDirection());

	// Attach possible directions to the last one.
	directions.insert(std::end(directions), std::begin(possibleDirections_), std::end(possibleDirections_));

	// If this step has to be random, shuffle the 5 possible directions,
	// so that any of if can end up at the front of the list.
	if (randomDoubleDistribution_(randomGenerator_) < randomness_)
		std::random_shuffle(std::begin(directions), std::end(directions));

	// Use the first direction in the list that will not result in a crash.
	for (auto it(std::begin(directions)); it != std::end(directions); ++it)
	{
		if (std::find(std::begin(occupiedPositions), std::end(occupiedPositions),
				world.NextPosition(player.GetFrontPosition(), *it)) == std::end(occupiedPositions))
		{
			nextDirection_ = *it;
			break;
		}
	}

	// If an item is next to the head, prefer that direction, no matter what else happens.
	const ItemPtrs& itemPtrs(world.GetItemPtrs());
	for (auto it(std::begin(directions)); it != std::end(directions); ++it)
	{
		if (std::find_if(std::begin(itemPtrs), std::end(itemPtrs), [&](const ItemPtr itemPtr)
		{
			return itemPtr->GetPosition() == world.NextPosition(player.GetFrontPosition(), *it);
		}) != std::end(itemPtrs))
		{
			nextDirection_ = *it;
			break;
		}
	}
}

} /* namespace Dron */

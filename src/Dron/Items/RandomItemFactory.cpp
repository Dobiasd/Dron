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

#include "RandomItemFactory.h"
#include "BatteringRam.h"
#include "Abridger.h"
#include "Fragmenter.h"

#include "../GameStates/PlayModel.h"

namespace Dron
{
RandomItemFactory::RandomItemFactory() :
		randomGenerator_(randomDevice_()), randomIntDistributionType_(0, 3)
{
}

RandomItemFactory::ItemPtr RandomItemFactory::Create(const World& world, ConstPlayerPtrs playerPtrs) const
{
	World::Positions freePositions(world.GetFreePositions(playerPtrs));

	if (freePositions.empty())
		return ItemPtr();

	std::uniform_int_distribution<> randomIntDistributionPos(0, freePositions.size() - 1);
	World::Position pos(freePositions[randomIntDistributionPos(randomGenerator_)]);

	// Battering Rams are two times more likely than Abridgers.
	int randomNumber(randomIntDistributionType_(randomGenerator_));
	if (randomNumber == 0)
		return ItemPtr(new Abridger(pos, world.GetWidth() + world.GetHeight()));
	if (randomNumber == 1)
		return ItemPtr(new Fragmenter(pos, world.GetWidth() + world.GetHeight()));
	return ItemPtr(new BatteringRam(pos, world.GetWidth() + world.GetHeight()));
}

} /* namespace Dron */

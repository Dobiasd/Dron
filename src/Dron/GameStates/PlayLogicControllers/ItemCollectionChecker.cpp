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

#include "ItemCollectionChecker.h"

namespace Dron
{

void ItemCollectionChecker::Control(PlayModel& model, Play&) const
{
	PlayerPtrs alivePlayers(model.GetAlivePlayers());
	ItemPtrs& itemPtrs(model.world_.GetItemPtrs());
	std::for_each(std::begin(alivePlayers), std::end(alivePlayers), [&](PlayerPtr playerPtr)
	{
		auto itItemPtr(std::begin(itemPtrs));
		const World::Position& nextPos(playerPtr->NextPosition(model.world_));
		while (itItemPtr != std::end(itemPtrs))
		{
			if (nextPos == (*itItemPtr)->GetPosition() && playerPtr->HitItem(nextPos, *itItemPtr, model.world_))
			{
				itItemPtr = itemPtrs.erase(itItemPtr);
				continue;
			}
			if (itItemPtr != std::end(itemPtrs))
			++itItemPtr;
		}
	});
}

} /* namespace Dron */

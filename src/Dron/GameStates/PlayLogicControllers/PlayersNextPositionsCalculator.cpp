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

#include "PlayersNextPositionsCalculator.h"

#include <iterator>

namespace Dron
{

void PlayersNextPositionsCalculator::Control(PlayModel& model, Play&) const
{
	// Helper function: Return a copy of a list of players with one particular player removed.
	auto FilterOtherPlayers = [](PlayerPtr playerPtr, PlayerPtrs playerPtrs) -> PlayerPtrs
	{
		PlayerPtrs otherPlayers;
		std::remove_copy_if(std::begin(playerPtrs),
				std::end(playerPtrs),
				std::back_inserter(otherPlayers),
				[&](ConstPlayerPtr otherPlayerPtr)
				{
					return otherPlayerPtr == playerPtr;
				}
		);
		return otherPlayers;
	};

	PlayerPtrs alivePlayers(model.GetAlivePlayers());
	std::for_each(std::begin(alivePlayers), std::end(alivePlayers),
			[&](PlayerPtr playerPtr)
			{
				PlayerPtrs otherPlayerPtrs(FilterOtherPlayers(playerPtr, model.playerPtrs_));
				playerPtr->CalculateNextStep(model.world_, ConstPlayerPtrs(std::begin(otherPlayerPtrs), std::end(otherPlayerPtrs)));
			});
}

} /* namespace Dron */

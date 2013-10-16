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

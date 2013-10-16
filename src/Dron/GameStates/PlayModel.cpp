#include "PlayModel.h"
#include "Play.h"

#include "../Player.h"

#include <iostream>

namespace Dron
{

PlayModel::PlayModel(const World& world, PlayerPtrs playerPtrs, float stepsPerSecond, double newItemProbability) :
		world_(world), playerPtrs_(playerPtrs)
{
}

PlayerPtrs PlayModel::GetAlivePlayers() const
{
	PlayerPtrs alivePlayers;
	for (auto it(std::begin(playerPtrs_)); it != std::end(playerPtrs_); ++it)
		if ((*it)->IsAlive())
			alivePlayers.push_back(*it);
	return alivePlayers;
}

} /* namespace Dron */

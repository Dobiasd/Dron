#ifndef DRON_PLAYMODEL_H_
#define DRON_PLAYMODEL_H_

#include "../World.h"
#include "../Player.h"

namespace Dron
{

class Play;

/*
 * Implements the in game logic.
 * Updates the world, items and players of the model with every time step,
 * and thus handles collisions and decides who dies and wins.
 */
class PlayModel
{
public:
	PlayModel(const World& world, PlayerPtrs playerPtrs, float stepsPerSecond, double newItemProbability);
	bool Update(float elapsedTime, Play& play);
	PlayerPtrs GetAlivePlayers() const;
	World world_;
	PlayerPtrs playerPtrs_;
};

} /* namespace Dron */

#endif /* DRON_PLAYMODEL_H_ */

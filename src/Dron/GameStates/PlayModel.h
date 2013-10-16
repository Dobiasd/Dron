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

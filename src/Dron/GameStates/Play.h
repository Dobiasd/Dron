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

#ifndef PLAY_H_
#define PLAY_H_

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayInputController.h"
#include "PlayLogicController.h"

#include "../../GameState.h"

namespace Dron
{

class Player;

/*
 * The in-game state. Calls are delegated to the individual MVC components.
 * The controller changes the model and the view displays it.
 */
class Play: public GameState
{
public:
	Play(const World& world, PlayerPtrs playerPtrs, float stepsPerSecond, double newItemProbability,
			int blurAmount = 7);
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
	float stepsPerSecond_;
protected:
	typedef Vector2D<int> Vector;
	typedef Vector Position;
	typedef std::vector<Position> Positions;
	PlayModel model_;
	PlayView view_;
	PlayInputController inputController_;
	PlayLogicControllerPtrs logicControllerPtrs_;
	bool paused_;
	float elapsedTimeSinceLastStep_;
	std::size_t stepNum_;
};

} /* namespace Dron */

#endif /* PLAY_H_ */

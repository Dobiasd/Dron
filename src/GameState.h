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

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

class GameState;

typedef std::shared_ptr<GameState> GameStatePtr;
typedef std::shared_ptr<const GameState> ConstGameStatePtr;

/*
 * Abstract base class for game states
 * They are implemented as a finite state machine.
 * The Model-View-Controller model is supported.
 */
class GameState
{
public:
	GameState() :
			quit_(false)
	{
	}
	virtual ~GameState()
	{
	}

	// Get inputs for controller.
	virtual bool ProcessEvent(const sf::Event& event) = 0;

	// Update model.
	virtual bool Update(float elapsedTime) = 0;

	// Show the model using the view.
	virtual bool Display(sf::RenderTarget& renderTarget) const = 0;

	// A state can give the word if another state shall take over.
	void SetNextState(const GameStatePtr nextState)
	{
		nextState_ = nextState;
	}

	// Is a next state set?
	bool IsDone()
	{
		return nextState_ != nullptr;
	}

	// What is the next state?
	GameStatePtr GetNextState() const
	{
		return nextState_;
	}

	// Close application?
	bool GameQuitted() const
	{
		return quit_;
	}

protected:
	bool quit_;

private:
	GameStatePtr nextState_;
};

#endif /* GAMESTATE_H_ */

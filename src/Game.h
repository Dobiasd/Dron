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

#ifndef GAME_H_
#define GAME_H_

#include "GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <memory>

/*
 * Abstract base class for a game using SMFL
 *
 * It Provides InitSounds() for later use (supposedly in some kind of splash screen).
 * A double click into the window switched back and forth
 * between windowed mode and fullscreen.
 */
class Game
{
public:
	virtual ~Game()
	{
	}

	// Start the game.
	virtual bool Run();

	virtual void InitSounds() = 0;

	virtual sf::Image CaptureScreen() const;

protected:
	// Every game has to have a name.
	virtual std::string GetName() = 0;
	virtual bool Init() = 0;
	typedef std::unique_ptr<sf::RenderWindow> WindowPtr;
	WindowPtr windowPtr_;
	GameStatePtr gameStatePtr_;
	sf::View view_;
	bool fullScreen_;
};

#endif /* GAME_H_ */

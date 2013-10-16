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

#ifndef DRON_PLAYERCONTROLLER_H_
#define DRON_PLAYERCONTROLLER_H_

#include "../Vector2D.h"
#include "World.h"

#include <SFML/Window/Event.hpp>

#include <string>
#include <memory>
#include <vector>

namespace Dron
{

class Player;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<const Player> ConstPlayerPtr;
typedef std::vector<PlayerPtr> PlayerPtrs;
typedef std::vector<ConstPlayerPtr> ConstPlayerPtrs;

/*
 * Abstract base class for controlling tron players
 */
class PlayerController
{
public:
	typedef Vector2D<int> Vector;

	PlayerController(const std::string& name);

	virtual ~PlayerController()
	{
	}

	// Handle keyboard inputs
	virtual void PushKeyInput(const sf::Key::Code&)
	{
	}

	// Handle joypad inputs
	virtual void PushJoyInput(const sf::Event::JoyMoveEvent&)
	{
	}

	// Derived controllers calculate the next move of its player.
	virtual void CalculateNextDirection(const World&, const Player&, ConstPlayerPtrs) = 0;
	virtual Vector GetNextDirection() const
	{
		return nextDirection_;
	}
	const std::string& GetName() const
	{
		return name_;
	}
protected:
	std::string name_;
	Vector nextDirection_;
};

typedef std::shared_ptr<PlayerController> PlayerControllerPtr;
typedef std::vector<PlayerControllerPtr> PlayerControllerPtrs;
typedef std::shared_ptr<const PlayerController> ConstPlayerControllerPtr;
typedef std::vector<ConstPlayerControllerPtr> ConstPlayerControllerPtrs;

} /* namespace Dron */

#endif /* DRON_PLAYERCONTROLLER_H_ */

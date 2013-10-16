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

#ifndef DRON_JOYCONTROLLER_H_
#define DRON_JOYCONTROLLER_H_

#include "../PlayerController.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <queue>
#include <memory>

namespace Dron
{

/*
 * Simple joypad controller for a tron player
 * Inputs are stacked to make the timing for quick turns easier to get.
 */
class JoyController: public PlayerController
{
public:
	JoyController(const std::string& name, unsigned int joyId);
	virtual void PushJoyInput(const sf::Event::JoyMoveEvent& joyMoveEvent)
	override;
	virtual void CalculateNextDirection(const World& world, const Player&, ConstPlayerPtrs otherPlayerPtrs)
	override;
protected:
	void PushDirectionIfNew(const Vector& direction);
	typedef std::queue<Vector> DirectionsQueue;
	DirectionsQueue inputDirections_;
	unsigned int joyId_;
};

typedef std::shared_ptr<JoyController> JoyControllerPtr;
typedef std::shared_ptr<const JoyController> ConstJoyControllerPtr;

} /* namespace Dron */

#endif /* DRON_JOYCONTROLLER_H_ */

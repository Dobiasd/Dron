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

#include "JoyController.h"

#include "../Player.h"

#include <algorithm>

namespace Dron
{

JoyController::JoyController(const std::string& name, unsigned int joyId) :
		PlayerController(name), joyId_(joyId)
{
}

void JoyController::PushDirectionIfNew(const Vector& direction)
{
	if (!inputDirections_.empty() && inputDirections_.front() == direction)
		return;
	inputDirections_.push(direction);
}

void JoyController::PushJoyInput(const sf::Event::JoyMoveEvent& joyMoveEvent)
{
	if (joyMoveEvent.JoystickId != joyId_)
		return;
	if (joyMoveEvent.Axis == sf::Joy::AxisX && joyMoveEvent.Position < 0.f)
		PushDirectionIfNew(Vector(-1, 0));
	if (joyMoveEvent.Axis == sf::Joy::AxisX && joyMoveEvent.Position > 0.f)
		PushDirectionIfNew(Vector(1, 0));
	if (joyMoveEvent.Axis == sf::Joy::AxisY && joyMoveEvent.Position < 0.f)
		PushDirectionIfNew(Vector(0, -1));
	if (joyMoveEvent.Axis == sf::Joy::AxisY && joyMoveEvent.Position > 0.f)
		PushDirectionIfNew(Vector(0, 1));
}

void JoyController::CalculateNextDirection(const World&, const Player& player, ConstPlayerPtrs)
{
	if (inputDirections_.empty())
		inputDirections_.push(player.GetLastDirection());
	else if (inputDirections_.front() + player.GetLastDirection() == Vector())
		nextDirection_ = player.GetLastDirection();
	else
		nextDirection_ = inputDirections_.front();
	inputDirections_.pop();
}

} /* namespace Dron */

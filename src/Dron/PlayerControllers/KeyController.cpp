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

#include "KeyController.h"

#include "../Player.h"

#include <algorithm>

namespace Dron
{

KeyController::KeyController(const std::string& name) :
		PlayerController(name)
{
}

void KeyController::SetDirectionKey(const Vector& direction, sf::Key::Code keyCode)
{
	keysToDirections_.insert(KeysToDirections::value_type(keyCode, direction));
}

void KeyController::PushKeyInput(const sf::Key::Code& keyCode)
{
	auto it(keysToDirections_.find(keyCode));
	if (it == std::end(keysToDirections_))
		return;
	if (!inputDirections_.empty() && inputDirections_.back() == it->second)
		return;
	inputDirections_.push(it->second);
}

void KeyController::CalculateNextDirection(const World&, const Player& player, ConstPlayerPtrs)
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

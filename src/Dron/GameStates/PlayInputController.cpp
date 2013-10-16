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

#include "PlayInputController.h"
#include "Play.h"

#include "../Player.h"

#include <SFML/Window/Event.hpp>

namespace Dron
{

PlayInputController::PlayInputController(PlayModel& model) :
		model_(model)
{
}

// Forward keyboard inputs to an arbitrary range of players.
template<class InputIterator>
void DispatchKeyInputToPlayerPtrs(InputIterator first, InputIterator last, const sf::Key::Code& keyCode)
{
	while (first != last)
	{
		if ((*first)->IsAlive())
			(*(first))->PushKeyInput(keyCode);
		++first;
	}
}

// Forward keyboard inputs to an arbitrary range of players.
template<class InputIterator>
void DispatchJoyInputToPlayerPtrs(InputIterator first, InputIterator last, const sf::Event::JoyMoveEvent& joyMoveEvent)
{
	while (first != last)
	{
		if ((*first)->IsAlive())
			(*(first))->PushJoyInput(joyMoveEvent);
		++first;
	}
}

bool PlayInputController::ProcessEvent(const sf::Event& event, Play& play)
{
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Add))
		play.stepsPerSecond_ *= 4.f / 3.f;
	else if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Subtract))
		play.stepsPerSecond_ = std::max(1.f, play.stepsPerSecond_ / (4.f / 3.f));
	else if (event.Type == sf::Event::KeyPressed)
		DispatchKeyInputToPlayerPtrs(std::begin(model_.playerPtrs_), std::end(model_.playerPtrs_), event.Key.Code);
	else if (event.Type == sf::Event::JoyMoved)
		DispatchJoyInputToPlayerPtrs(std::begin(model_.playerPtrs_), std::end(model_.playerPtrs_), event.JoyMove);
	return true;
}

} /* namespace Dron */

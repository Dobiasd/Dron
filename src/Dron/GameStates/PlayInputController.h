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

#ifndef DRON_PLAYINPUTCONTROLLER_H_
#define DRON_PLAYINPUTCONTROLLER_H_

#include "PlayModel.h"

namespace sf
{
class Event;
}

namespace Dron
{

class Play;

/*
 * Forwards input events to the individual controllers of the players in the model.
 */
class PlayInputController
{
public:
	PlayInputController(PlayModel& model);
	bool ProcessEvent(const sf::Event& event, Play& play);
private:
	PlayModel& model_;
};

} /* namespace Dron */

#endif /* DRON_PLAYINPUTCONTROLLER_H_ */

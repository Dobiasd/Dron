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

#ifndef DRON_PLAYLOGICCONTROLLER_H_
#define DRON_PLAYLOGICCONTROLLER_H_

#include "PlayModel.h"

#include <memory>
#include <vector>

namespace sf
{
class Event;
}

namespace Dron
{

/*
 * Abstract base class for implementing different aspects of the game logic
 */
class PlayLogicController
{
public:
	virtual ~PlayLogicController()
	{
	}
	virtual void Control(PlayModel& model, Play& play) const = 0;
};

typedef std::shared_ptr<PlayLogicController> PlayLogicControllerPtr;
typedef std::vector<PlayLogicControllerPtr> PlayLogicControllerPtrs;

} /* namespace Dron */

#endif /* DRON_PLAYLOGICCONTROLLER_H_ */

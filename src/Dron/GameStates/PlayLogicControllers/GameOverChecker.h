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

#ifndef GAMEOVERCHECKER_H_
#define GAMEOVERCHECKER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Did somebody win or was there even a draw?
 */
class GameOverChecker: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* GAMEOVERCHECKER_H_ */
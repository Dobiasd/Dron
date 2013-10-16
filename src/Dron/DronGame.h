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

#ifndef DRON_DRONGAME_H_
#define DRON_DRONGAME_H_

#include "../Singleton.h"
#include "../Game.h"

#include <vector>

namespace Dron
{

/*
 * Initializes the window and game specific sounds.
 */
class DronGame: public Game, public Singleton<DronGame>
{
public:
	DronGame();
	virtual std::string GetName()
	override;
	virtual void InitSounds()
	override;
	virtual bool SoundsInitialized() const
	{
		return soundsInitialized_;
	}
protected:
	virtual bool Init()
	override;
	bool soundsInitialized_;
};

} /* namespace Dron */

#endif /* DRON_DRONGAME_H_ */

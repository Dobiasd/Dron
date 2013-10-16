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

#include "ItemDacayer.h"

namespace Dron
{

void ItemDacayer::Control(PlayModel& model, Play&) const
{
	ItemPtrs& itemPtrs(model.world_.GetItemPtrs());
	for (auto it(std::begin(itemPtrs)); it != std::end(itemPtrs);)
	{
		(*it)->Decay();
		if ((*it)->IsDecayed())
			it = itemPtrs.erase(it);
		else
			++it;
	}
}

} /* namespace Dron */

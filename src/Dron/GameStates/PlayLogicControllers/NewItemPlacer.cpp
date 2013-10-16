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

#include "NewItemPlacer.h"

#include "../../Items/RandomItemFactory.h"

namespace Dron
{

NewItemPlacer::NewItemPlacer(double newItemProbability) :
		newItemProbability_(newItemProbability), randomGenerator_(randomDevice_()), randomDoubleDistribution_(0., 1.)
{
}

void NewItemPlacer::Control(PlayModel& model, Play&) const
{
	if (randomDoubleDistribution_(randomGenerator_) < newItemProbability_)
	{
		ItemPtr newItemPtr(
				RandomItemFactory::Instance().Create(model.world_,
						ConstPlayerPtrs(std::begin(model.playerPtrs_), std::end(model.playerPtrs_))));
		if (newItemPtr)
			model.world_.InsertItem(newItemPtr);
	}
}

} /* namespace Dron */

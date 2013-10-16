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

#ifndef NEWITEMPLACER_H_
#define NEWITEMPLACER_H_

#include "../PlayLogicController.h"

#include <random>

namespace Dron
{

/*
 * Randomly places new items.
 */
class NewItemPlacer: public Dron::PlayLogicController
{
public:
	NewItemPlacer(double newItemProbability);
	virtual void Control(PlayModel& model, Play& play) const
	override;
private:
	double newItemProbability_;
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_real_distribution<> randomDoubleDistribution_;
};

} /* namespace Dron */

#endif /* NEWITEMPLACER_H_ */

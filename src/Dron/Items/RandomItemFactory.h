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

#ifndef DRON_RANDOMITEMFACTORY_H_
#define DRON_RANDOMITEMFACTORY_H_

#include "../Item.h"
#include "../Player.h"
#include "../../Singleton.h"

#include <memory>
#include <random>

namespace Dron
{

class World;

/*
 * Spits out one random item to a free place in the tron world.
 */
class RandomItemFactory: public Singleton<RandomItemFactory>
{
public:
	RandomItemFactory();

	typedef std::unique_ptr<Item> ItemPtr;
	ItemPtr Create(const World& world, ConstPlayerPtrs playerPtrs) const;
protected:
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_int_distribution<> randomIntDistributionType_;
};

} /* namespace Dron */

#endif /* DRON_RANDOMITEMFACTORY_H_ */

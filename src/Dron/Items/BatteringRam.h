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

#ifndef DRON_BATTERINGRAM_H_
#define DRON_BATTERINGRAM_H_

#include "../Item.h"

namespace Dron
{

/*
 * A BatteringRam can be collected and used one single time to eliminate a wall or enemy field.
 */
class BatteringRam: public Item
{
public:
	BatteringRam(const Position& position, std::size_t remainingSteps);
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
	override;
	virtual std::string GetName() const
	override;

	// Everything that stands in the way will be nuked.
	virtual bool HitWall(const Position& pos, Player& player, World& world)
	override;
	virtual bool HitSelf(const Position& pos, Player& player, World& world)
	override;
	virtual bool HitOtherPlayer(const Position& pos, Player& player, Player& other, World& world)
	override;
	virtual bool GetCollected(Player& player, World& world)
	override;
};

} /* namespace Dron */
#endif /* DRON_BATTERINGRAM_H_ */

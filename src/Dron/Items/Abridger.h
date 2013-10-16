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

#ifndef DRON_ABRIDGER_H_
#define DRON_ABRIDGER_H_

#include "../Item.h"

namespace Dron
{

/*
 * The Abridger will shorten the collecting player immediately to its minimum length.
 */
class Abridger: public Item
{
public:
	Abridger(const Position& position, std::size_t remainingSteps);
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
	override;
	virtual std::string GetName() const
	override;
	virtual bool GetUsedImmediately(Player&, World& world)
	override;
};

} /* namespace Dron */
#endif /* DRON_ABRIDGER_H_ */

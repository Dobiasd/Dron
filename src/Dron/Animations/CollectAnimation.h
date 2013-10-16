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

#ifndef DRON_COLLECTANIMATION_H_
#define DRON_COLLECTANIMATION_H_

#include "../Animation.h"

namespace Dron
{

/*
 * An floating Text that is presented when an item is collected or used immediately by a player.
 */
class CollectAnimation: public Animation
{
public:
	CollectAnimation(const sf::Color& color, const World::Position& position, const std::string& text);
	virtual void Update(float elapsedTime)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const World& world) const
	override;
protected:
	typedef Vector2D<float> Vector;
	sf::Color color_;
	World::Position position_;
	float elapsedTimeSum_;
	std::string text_;
};

} /* namespace Dron */

#endif /* DRON_COLLECTANIMATION_H_ */

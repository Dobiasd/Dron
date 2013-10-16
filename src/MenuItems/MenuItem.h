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

#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "../Vector2D.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>

/*
 * Abstract base class for menu items.
 */
class MenuItem
{
public:
	typedef Vector2D<int> Position;

	// Every Item has to process keyboard inputs in some way.
	virtual void ProcessKey(const sf::Key::Code& keyCode) = 0;

	// Show the item a a given position.
	virtual void Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
			float height) const = 0;
};

typedef std::shared_ptr<MenuItem> MenuItemPtr;

#endif /* MENUITEM_H_ */

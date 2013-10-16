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

#ifndef MENU_H_
#define MENU_H_

#include "MenuItems/MenuItem.h"

#include <memory>
#include <vector>

/*
 * A basic menu operated with the arrow keys (or wasd) and enter.
 * The following keys are also supported: home, end, page up, page down
 */
class Menu
{
public:
	virtual void ProcessKeyCode(const sf::Key::Code&);
	virtual void Display(sf::RenderTarget& renderTarget) const;
	void AddMenuItem(const MenuItemPtr ptr)
	{
		menuItemsPtrs_.push_back(ptr);
		itMenu = std::begin(menuItemsPtrs_);
	}

private:
	typedef std::vector<MenuItemPtr> MenuItemPtrs;
	MenuItemPtrs menuItemsPtrs_;
	MenuItemPtrs::const_iterator itMenu;
};

#endif /* MENU_H_ */

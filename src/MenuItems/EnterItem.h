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

#ifndef ENTERITEM_H_
#define ENTERITEM_H_

#include "MenuItem.h"

#include <functional>

/*
 * An item in a menu whose callback function can be invoked with the enter key
 */
class EnterItem: public MenuItem
{
public:
	typedef std::function<void(void)> Callback;
	EnterItem(const std::string& label, const Callback& callback);
	virtual void ProcessKey(const sf::Key::Code& keyCode)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
			float height) const
	override;
protected:
	std::string label_;
	Callback callback_;
};

#endif /* ENTERITEM_H_ */

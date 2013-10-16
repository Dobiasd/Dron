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

#include "EnterItem.h"

#include <SFML/Graphics/String.hpp>

EnterItem::EnterItem(const std::string& label, const Callback& callback) :
		label_(label), callback_(callback)
{
}

void EnterItem::Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color, float height) const
{
	sf::String sfText(label_);
	sfText.SetSize(height);
	sfText.SetColor(color);
	sfText.Move(static_cast<float>(pos.x_), static_cast<float>(pos.y_));
	renderTarget.Draw(sfText);
}

void EnterItem::ProcessKey(const sf::Key::Code& keyCode)
{
	if (keyCode == sf::Key::Return || keyCode == sf::Key::Space)
		callback_();
}

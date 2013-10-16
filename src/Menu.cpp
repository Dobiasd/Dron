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

#include "Menu.h"

#include "Synthesizer.h"

#include <iostream>

void Menu::Display(sf::RenderTarget& renderTarget) const
{
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	int itemStep(static_cast<int>(height) / (menuItemsPtrs_.size() + 2));
	float itemHeight(.8f * static_cast<float>(itemStep));
	MenuItem::Position tl(static_cast<int>(.1f * width), itemStep);
	for (auto it(std::begin(menuItemsPtrs_)); it != std::end(menuItemsPtrs_); ++it)
	{
		(*it)->Display(renderTarget,
				MenuItem::Position(tl.x_, tl.y_ + itemStep * std::distance(std::begin(menuItemsPtrs_), it)),
				it == itMenu ? sf::Color(255, 127, 0) : sf::Color(127, 63, 0), itemHeight);
	}
}

void Menu::ProcessKeyCode(const sf::Key::Code& keyCode)
{
	if (keyCode == sf::Key::Up || keyCode == sf::Key::W)
	{
		if (itMenu != std::begin(menuItemsPtrs_))
		{
			--itMenu;
			Synthesizer::PlaySound("MenuVertical");
		}
		else
			Synthesizer::PlaySound("MenuVerticalBump");
	}
	else if (keyCode == sf::Key::Down || keyCode == sf::Key::S)
	{
		if (itMenu != std::end(menuItemsPtrs_) - 1)
		{
			++itMenu;
			Synthesizer::PlaySound("MenuVertical");
		}
		else
			Synthesizer::PlaySound("MenuVerticalBump");
	}
	else if (keyCode == sf::Key::Home || keyCode == sf::Key::PageUp)
	{
		if (itMenu != std::begin(menuItemsPtrs_))
		{
			itMenu = std::begin(menuItemsPtrs_);
			Synthesizer::PlaySound("MenuVertical");
		}
		else
			Synthesizer::PlaySound("MenuVerticalBump");
	}
	else if (keyCode == sf::Key::End || keyCode == sf::Key::PageDown)
	{
		if (itMenu != std::end(menuItemsPtrs_) - 1)
		{
			itMenu = std::end(menuItemsPtrs_) - 1;
			Synthesizer::PlaySound("MenuVertical");
		}
		else
			Synthesizer::PlaySound("MenuVerticalBump");
	}
	else
		(*itMenu)->ProcessKey(keyCode);
}

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

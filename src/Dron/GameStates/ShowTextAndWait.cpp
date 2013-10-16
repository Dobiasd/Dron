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

#include "ShowTextAndWait.h"

#include "../DronGame.h"

#include <SFML/Graphics.hpp>

namespace Dron
{

ShowTextAndWait::ShowTextAndWait(const std::string& text, const sf::Color& color, const GameStatePtr nextStatePtr,
		float waitTime, const sf::Image& backgroundImage) :
		text_(text), color_(color), nextStatePtr_(nextStatePtr), elapsedTimeSum_(0.f), waitTime_(waitTime), backgroundImage_(
				backgroundImage)
{
}

bool ShowTextAndWait::ProcessEvent(const sf::Event& event)
{
	if (elapsedTimeSum_ > waitTime_)
	{
		if (event.Type == sf::Event::KeyPressed)
			SetNextState(nextStatePtr_);
	}
	return true;
}

bool ShowTextAndWait::Update(float elapsedTime)
{
	elapsedTimeSum_ += elapsedTime;
	return true;
}

bool ShowTextAndWait::Display(sf::RenderTarget& renderTarget) const
{
	renderTarget.Clear(sf::Color(0, 0, 0));
	if (backgroundImage_.GetWidth() && backgroundImage_.GetHeight())
	{
		sf::Sprite backgroundSprite(backgroundImage_);
		renderTarget.Draw(backgroundSprite);
	}
	// Adjust the text size to the window
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	sf::String sfText(text_);
	float sfTextScale((.7f * width) / sfText.GetRect().GetWidth());
	sfText.Scale(sfTextScale, sfTextScale);
	sfText.SetColor(color_);
	sfText.Move(.1f * width, (height - sfText.GetRect().GetHeight()) / 2.f);
	renderTarget.Draw(sfText);
	if (elapsedTimeSum_ > waitTime_)
	{
		sf::String sfTextPressKey("Press any key to continue.");
		float sfKeyTextScale((.7f * width) / sfTextPressKey.GetRect().GetWidth());
		sfTextPressKey.Scale(sfKeyTextScale / 2.f, sfKeyTextScale / 2.f);
		sfTextPressKey.SetColor(sf::Color(127, 63, 0));
		sfTextPressKey.Move(.1f * width, .8f * height);
		renderTarget.Draw(sfTextPressKey);
	}
	return true;
}

} /* namespace Dron */

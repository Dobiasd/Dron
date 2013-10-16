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

#include "SplashScreen.h"

#include "MainMenu.h"

#include "../DronGame.h"

#include <vector>
#include <random>

namespace Dron
{

SplashScreen::SplashScreen(const std::string& title) :
		title_(title), firstFrame_(true)
{
	typedef std::vector<std::string> Tips;
	Tips tips;
	tips.push_back("You can toggle between windowd and fullscreen mode\nby double clicking into the window.");
	tips.push_back(
			"The Dron world is topologically designed as a torus.\nYou can wrap around (exit on the left, come back in on the right etc.).");
	tips.push_back(
			"By collecting battering rams (Inventars are shown at the bottom.)\nyou can make yourself immune to certain trapping situations.");
	tips.push_back(
			"If the game runs too slow despite of you having set a high speed\ntry reducing the level for GPU based special effects (blur).");
	tips.push_back("If you want to change the game speed during play\nyou can do so by using the plus and minus keys.");

	std::random_device randomDevice;
	std::mt19937 randomGenerator(randomDevice());
	std::uniform_int_distribution<> randomIntDistributionTip(0, tips.size() - 1);
	tip_ = std::string("Did you know?\n") + tips.at(randomIntDistributionTip(randomGenerator));
}

bool SplashScreen::ProcessEvent(const sf::Event& event)
{
	if (event.Type == sf::Event::KeyPressed)
		SetNextState(GameStatePtr(new MainMenu()));
	return true;
}

bool SplashScreen::Update(float)
{
	if (!firstFrame_ && !DronGame::Instance().SoundsInitialized())
		DronGame::Instance().InitSounds();
	firstFrame_ = false;
	return true;
}

bool SplashScreen::Display(sf::RenderTarget& renderTarget) const
{
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	renderTarget.Clear(sf::Color(0, 0, 0));
	sf::String sfText(title_);
	float sfTextScale((.7f * width) / sfText.GetRect().GetWidth());
	sfText.Scale(sfTextScale, sfTextScale);
	sfText.SetColor(sf::Color(255, 127, 0));
	sfText.Move(.1f * width, .4f * height);
	renderTarget.Draw(sfText);

	sf::String sfTextURL("http://www.daiw.de");
	sfTextURL.Scale(sfTextScale / 2.4f, sfTextScale / 2.4f);
	sfTextURL.SetColor(sf::Color(63, 31, 0));
	sfTextURL.Move(.1f * width, .5f * height);
	renderTarget.Draw(sfTextURL);

	sf::String sfTextTip(tip_);
	sfTextTip.Scale(sfTextScale / 2.6f, sfTextScale / 2.7f);
	sfTextTip.SetColor(sf::Color(31, 31, 191));
	sfTextTip.Move(.95f * width - sfTextTip.GetRect().GetWidth(), .2f * height);
	renderTarget.Draw(sfTextTip);

	sf::String sfTextPressKey("Press any key to continue.");
	if (!DronGame::Instance().SoundsInitialized())
		sfTextPressKey = sf::String("Initializing ...");
	sfTextPressKey.Scale(sfTextScale / 2.f, sfTextScale / 2.f);
	sfTextPressKey.SetColor(sf::Color(127, 63, 0));
	sfTextPressKey.Move(.1f * width, .8f * height);
	renderTarget.Draw(sfTextPressKey);
	return true;
}

} /* namespace Dron */

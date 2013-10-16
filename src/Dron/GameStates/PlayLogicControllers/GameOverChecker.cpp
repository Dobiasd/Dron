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

#include "GameOverChecker.h"

#include "../Play.h"
#include "../ShowTextAndWait.h"
#include "../MainMenu.h"

#include "../../DronGame.h"

#include "../../../Synthesizer.h"

#include <iostream>

namespace Dron
{

void GameOverChecker::Control(PlayModel& model, Play& play) const
{
	PlayerPtrs alivePlayers(model.GetAlivePlayers());
	switch (alivePlayers.size())
	{
	case 0:
		std::cout << "Draw." << std::endl;
		Synthesizer::PlaySound("Draw");
		play.SetNextState(
				GameStatePtr(
						new ShowTextAndWait("Draw.", sf::Color(255, 255, 255), GameStatePtr(new MainMenu()), 1.f,
								DronGame::Instance().CaptureScreen())));
		break;
	case 1:
		std::string text(alivePlayers.front()->GetName() + " won.");
		Synthesizer::PlaySound("Win");
		std::cout << text << std::endl;
		play.SetNextState(
				GameStatePtr(
						new ShowTextAndWait(text, alivePlayers.front()->GetColor(), GameStatePtr(new MainMenu()), 1.f,
								DronGame::Instance().CaptureScreen())));
		break;
	}
}

} /* namespace Dron */

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

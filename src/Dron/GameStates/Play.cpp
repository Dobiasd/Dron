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

#include "PlayLogicControllers/PlayersNextPositionsCalculator.h"
#include "PlayLogicControllers/PlayersCollisionChecker.h"
#include "PlayLogicControllers/ItemCollectionChecker.h"
#include "PlayLogicControllers/ItemDacayer.h"
#include "PlayLogicControllers/PlayerMover.h"
#include "PlayLogicControllers/NewItemPlacer.h"
#include "PlayLogicControllers/GameOverChecker.h"

#include "Play.h"
#include "Quit.h"
#include "MainMenu.h"

#include "../Player.h"
#include "../PlayerController.h"

#include "../../Synthesizer.h"

#include <iostream>
#include <algorithm>

namespace Dron
{

Play::Play(const World& world, PlayerPtrs playerPtrs, float stepsPerSecond, double newItemProbability, int blurAmount) :
		model_(world, playerPtrs, stepsPerSecond, newItemProbability), view_(model_, blurAmount), inputController_(
				model_), paused_(true), stepsPerSecond_(stepsPerSecond), elapsedTimeSinceLastStep_(0.f), stepNum_(0)
{
	logicControllerPtrs_.push_back(std::make_shared<PlayersNextPositionsCalculator>());
	logicControllerPtrs_.push_back(std::make_shared<PlayersCollisionChecker>());
	logicControllerPtrs_.push_back(std::make_shared<ItemCollectionChecker>());
	logicControllerPtrs_.push_back(std::make_shared<ItemDacayer>());
	logicControllerPtrs_.push_back(std::make_shared<PlayerMover>());
	logicControllerPtrs_.push_back(std::make_shared < NewItemPlacer > (newItemProbability));
	logicControllerPtrs_.push_back(std::make_shared<GameOverChecker>());
}

bool Play::ProcessEvent(const sf::Event& event)
{
	if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
		SetNextState(GameStatePtr(new MainMenu()));
	else if (event.Type == sf::Event::Closed)
		SetNextState(GameStatePtr(new Quit()));
	else if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
	{
		paused_ = !paused_;
		std::cout << (paused_ ? "Game paused." : "Game continued.") << std::endl;
		Synthesizer::PlaySound("Pause");
	}
	else
		return inputController_.ProcessEvent(event, *this);
	return true;
}

bool Play::Update(float elapsedTime)
{
	if (paused_)
		return true;

	elapsedTimeSinceLastStep_ += elapsedTime;

	// The Animations can have higher update frequency than the world itself.
	model_.world_.UpdateAnimations(elapsedTime);

	// Do nothing before it's time for the next step.
	if (elapsedTimeSinceLastStep_ < 1.f / stepsPerSecond_)
		return true;

	// Move the game one step forward in time.
	++stepNum_;
	typedef std::vector<Position> Positions;

	// Let all the logic controllers do their jobs.
	std::for_each(std::begin(logicControllerPtrs_), std::end(logicControllerPtrs_),
			[&](PlayLogicControllerPtr logicControllerPtr)
			{
				logicControllerPtr->Control(model_, *this);
			});

	// Reset the next step waiting time.
	elapsedTimeSinceLastStep_ = 0.f;
	return true;
}

bool Play::Display(sf::RenderTarget& renderTarget) const
{
	if (!view_.Display(renderTarget))
		return false;
	if (paused_)
	{
		float width(renderTarget.GetView().GetRect().GetWidth());
		float height(renderTarget.GetView().GetRect().GetHeight());
		sf::String sfTextPressKey("Game paused - press space bar.");
		float sfKeyTextScale(.7f * width / sfTextPressKey.GetRect().GetWidth());
		sfTextPressKey.Scale(sfKeyTextScale, sfKeyTextScale);
		sfTextPressKey.SetColor(sf::Color(127, 63, 0));
		sfTextPressKey.Move(.1f * width, .8f * height);
		renderTarget.Draw(sfTextPressKey);

		sf::String sfTextInputs("Inputs will already be accepted.");
		float sfTextInputsScale((.6f * width) / sfTextInputs.GetRect().GetWidth());
		sfTextInputs.Scale(sfTextInputsScale / 2.f, sfTextInputsScale / 2.f);
		sfTextInputs.SetColor(sf::Color(127, 0, 63));
		sfTextInputs.Move(.1f * width, .98f * height - sfTextInputs.GetRect().GetHeight());
		renderTarget.Draw(sfTextInputs);
	}
	return true;
}

} /* namespace Dron */

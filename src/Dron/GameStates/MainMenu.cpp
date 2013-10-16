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

#include "MainMenu.h"
#include "Quit.h"
#include "Play.h"
#include "ShowTextAndWait.h"

#include "../Player.h"
#include "../PlayerControllers/KeyController.h"
#include "../PlayerControllers/JoyController.h"
#include "../PlayerControllers/AIController.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <cmath>

namespace Dron
{

MainMenu::MainMenu() :
		randomGenerator_(randomDevice_()), settingsFileName_("Dron.cfg")
{
	Sizes worldSizes;
	Probabilities wallProbabilities;
	Probabilities obstacleProbabilities;
	ObstacleGrowAmounts obstacleGrowAmounts;
	Probabilities itemProbabilities;
	Floats speeds;
	Strings soundSettings;
	Ints blurAmounts;

	// The player's names and the corresponding color values.
	namedColors_.push_back(std::make_pair("Red", sf::Color(255, 0, 0)));
	namedColors_.push_back(std::make_pair("Green", sf::Color(0, 255, 0)));
	namedColors_.push_back(std::make_pair("Blue", sf::Color(0, 0, 255)));
	namedColors_.push_back(std::make_pair("Cyan", sf::Color(0, 255, 255)));
	namedColors_.push_back(std::make_pair("Magenta", sf::Color(255, 0, 255)));
	namedColors_.push_back(std::make_pair("Yellow", sf::Color(255, 255, 0)));

	// Set arrow keys
	KeyControllerPtr arrowsControllerPtr(new KeyController("Human: arrow keys"));
	arrowsControllerPtr->SetDirectionKey(Player::Vector(0, -1), sf::Key::Up);
	arrowsControllerPtr->SetDirectionKey(Player::Vector(-1, 0), sf::Key::Left);
	arrowsControllerPtr->SetDirectionKey(Player::Vector(0, 1), sf::Key::Down);
	arrowsControllerPtr->SetDirectionKey(Player::Vector(1, 0), sf::Key::Right);

	// Set w, a, s and d
	KeyControllerPtr wasdControllerPtr(new KeyController("Human: w,a,s,d"));
	wasdControllerPtr->SetDirectionKey(Player::Vector(0, -1), sf::Key::W);
	wasdControllerPtr->SetDirectionKey(Player::Vector(-1, 0), sf::Key::A);
	wasdControllerPtr->SetDirectionKey(Player::Vector(0, 1), sf::Key::S);
	wasdControllerPtr->SetDirectionKey(Player::Vector(1, 0), sf::Key::D);

	// Set the joypads
	JoyControllerPtr joy1ControllerPtr(new JoyController("Human: Joypad 1", 0));
	JoyControllerPtr joy2ControllerPtr(new JoyController("Human: Joypad 2", 1));

	// The following world sizes are possible.
	worldSizes.push_back(Size(32, 16));
	worldSizes.push_back(Size(64, 32));
	worldSizes.push_back(Size(128, 64));

	// Closeness of the surrounding wall
	wallProbabilities.push_back(.0);
	wallProbabilities.push_back(.3);
	wallProbabilities.push_back(.7);
	wallProbabilities.push_back(.9);
	wallProbabilities.push_back(.99);
	wallProbabilities.push_back(1.);

	// Something in the way?
	obstacleProbabilities.push_back(.0);
	obstacleProbabilities.push_back(.01);
	obstacleProbabilities.push_back(.02);
	obstacleProbabilities.push_back(.04);
	obstacleProbabilities.push_back(.1);

	// How much bling bling?
	itemProbabilities.push_back(.0);
	itemProbabilities.push_back(.02);
	itemProbabilities.push_back(.04);
	itemProbabilities.push_back(.08);
	itemProbabilities.push_back(.16);
	itemProbabilities.push_back(.32);
	itemProbabilities.push_back(.64);
	itemProbabilities.push_back(1.);

	// Playable speeds
	speeds.push_back(1.);
	speeds.push_back(2.);
	speeds.push_back(4.);
	speeds.push_back(8.);
	speeds.push_back(16.);
	speeds.push_back(24.);
	speeds.push_back(32.);
	speeds.push_back(48.);
	speeds.push_back(64.);

	// Choosable GPU load
	blurAmounts.push_back(0);
	blurAmounts.push_back(1);
	blurAmounts.push_back(2);

	// Still not annoyed? ;)
	soundSettings.push_back("On");
	soundSettings.push_back("Off");

	menu_.AddMenuItem(
			std::make_shared < EnterItem > ("Start", EnterItem::Callback(std::bind(&MainMenu::StartGame, this))));

	std::vector<PlayerControllerPtrs::size_type> defaultPlayers;
	defaultPlayers.push_back(0); // Arrow keys
	defaultPlayers.push_back(4); // AI 1
	defaultPlayers.push_back(5); // AI 2
	defaultPlayers.push_back(6); // AI 2
	defaultPlayers.push_back(9); // None
	defaultPlayers.push_back(9); // None
	for (auto it(std::begin(namedColors_)); it != std::end(namedColors_); ++it)
	{
		PlayerControllerPtrs controllerPtrs;
		controllerPtrs.push_back(arrowsControllerPtr);
		controllerPtrs.push_back(wasdControllerPtr);
		controllerPtrs.push_back(joy1ControllerPtr);
		controllerPtrs.push_back(joy2ControllerPtr);
		controllerPtrs.push_back(AIControllerPtr(std::make_shared < AIController > ("AI: Passive Pauline", 0.)));
		controllerPtrs.push_back(AIControllerPtr(std::make_shared < AIController > ("AI: Timid Tamara", .1)));
		controllerPtrs.push_back(AIControllerPtr(std::make_shared < AIController > ("AI: Adorable Anna", .2)));
		controllerPtrs.push_back(AIControllerPtr(std::make_shared < AIController > ("AI: Silly Sarah", .3)));
		controllerPtrs.push_back(AIControllerPtr(std::make_shared < AIController > ("AI: Random Rachel", .4)));
		controllerPtrs.push_back(nullptr); // No player
		playerControllerPtrsMenuItemPtrs_.push_back(
				std::make_shared < SelectItem<PlayerControllerPtrs>
						> (it->first, controllerPtrs, defaultPlayers[std::distance(std::begin(namedColors_), it)]));
		menu_.AddMenuItem(playerControllerPtrsMenuItemPtrs_.back());
	}

	worldSizeMenuItemPtr_ = std::make_shared < SelectItem < Sizes >> ("WorldSize", worldSizes, 1);
	wallProbabilityMenuItemPtr_ = std::make_shared < SelectItem
			< Probabilities >> ("WallProbability", wallProbabilities, 4);
	obstacleProbabilityMenuItemPtr_ = std::make_shared < SelectItem
			< Probabilities >> ("ObstacleProbability", obstacleProbabilities, 0);

	itemProbabilityMenuItemPtr_ = std::make_shared < SelectItem
			< Probabilities >> ("ItemProbability", itemProbabilities, 2);
	speedMenuItemPtr_ = std::make_shared < SelectItem < Floats >> ("Speed", speeds, 4);
	soundMenuItemPtr_ = std::make_shared < SelectItem
			< Strings
					>> ("Sound", soundSettings, 0, SelectItem<Strings>::Callback(
							std::bind(&MainMenu::SoundSettingsChanged, this)));
	blurAmountMenuItemPtr_ = std::make_shared < SelectItem < Ints >> ("Blur", blurAmounts, 1);

	// Stuff all options together into the menu.
	menu_.AddMenuItem(worldSizeMenuItemPtr_);
	menu_.AddMenuItem(wallProbabilityMenuItemPtr_);
	menu_.AddMenuItem(obstacleProbabilityMenuItemPtr_);
	menu_.AddMenuItem(itemProbabilityMenuItemPtr_);
	menu_.AddMenuItem(speedMenuItemPtr_);
	menu_.AddMenuItem(soundMenuItemPtr_);
	menu_.AddMenuItem(blurAmountMenuItemPtr_);
	menu_.AddMenuItem(std::make_shared < EnterItem > ("About", EnterItem::Callback(std::bind(&MainMenu::About, this))));
	menu_.AddMenuItem(
			std::make_shared < EnterItem > ("Quit", EnterItem::Callback(std::bind(&MainMenu::QuitGame, this))));

	LoadSettings();
	SoundSettingsChanged();
}

void MainMenu::StartGame()
{
	World world(worldSizeMenuItemPtr_->Get(), wallProbabilityMenuItemPtr_->Get(),
			obstacleProbabilityMenuItemPtr_->Get());
	std::cout << "New game" << std::endl;
	PlayerPtrs playerPtrs;
	for (auto it(std::begin(playerControllerPtrsMenuItemPtrs_)); it != std::end(playerControllerPtrsMenuItemPtrs_);
			++it)
	{
		if (!(*it)->Get())
			continue;
		World::Positions freePositions(
				world.GetFreePositions(ConstPlayerPtrs(std::begin(playerPtrs), std::end(playerPtrs))));

		if (freePositions.empty())
		{
			std::cerr << "Not enough free positions to place all Players." << std::endl;
			return;
		}

		std::uniform_int_distribution<> randomIntDistributionPos(0, freePositions.size() - 1);
		World::Position pos(freePositions[randomIntDistributionPos(randomGenerator_)]);

		auto itNamedColor(
				std::find_if(std::begin(namedColors_), std::end(namedColors_), [it](const NamedColor& namedColor)
				{
					return namedColor.first == (*it)->GetLabel();
				}));

		if (itNamedColor == std::end(namedColors_))
			continue;
		playerPtrs.push_back(
				std::make_shared < Player
						> (itNamedColor->first, pos, itNamedColor->second, (*it)->Get(), world.GetWidth() - 2));
	}
	SetNextState(
			GameStatePtr(
					new Play(world, playerPtrs, speedMenuItemPtr_->Get(), itemProbabilityMenuItemPtr_->Get(),
							blurAmountMenuItemPtr_->Get())));
	SaveSettings();
}

void MainMenu::About()
{
	std::string aboutText;
	aboutText += "Dron (Dobi's Tron/Snake game)\n";
	aboutText += "Copyright (C) 2012 Tobias Hermann\n";
	aboutText += "\n";
	aboutText += "This program is free software: you can redistribute it and/or modify it\n";
	aboutText += "under the terms of the GNU General Public License as published by the\n";
	aboutText += "Free Software Foundation, either version 3 of the License, or\n";
	aboutText += "(at your option) any later version.\n";
	aboutText += "\n";
	aboutText += "This program is distributed in the hope that it will be useful, but\n";
	aboutText += "WITHOUT ANY WARRANTY; without even the implied warranty of\n";
	aboutText += "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
	aboutText += "See the GNU General Public License for more details.\n";
	aboutText += "\n";
	aboutText += "You should have received a copy of the GNU General Public License along\n";
	aboutText += "with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
	SaveSettings();
	SetNextState(
			GameStatePtr(new ShowTextAndWait(aboutText, sf::Color(255, 255, 255), GameStatePtr(new MainMenu()), 0.f)));
}

void MainMenu::QuitGame()
{
	SaveSettings();
	SetNextState(GameStatePtr(new Quit()));
}

void MainMenu::SoundSettingsChanged()
{
	Synthesizer::Mute(soundMenuItemPtr_->Get() == "Off");
}

bool MainMenu::ProcessEvent(const sf::Event& event)
{
	if (event.Type == sf::Event::KeyPressed)
	{
		if (event.Key.Code == sf::Key::Escape)
			QuitGame();
		else
			menu_.ProcessKeyCode(event.Key.Code);
	}
	return true;
}

bool MainMenu::Update(float elapsedTime)
{
	elapsedTimeSum_ += elapsedTime;
	plasma_.Update(elapsedTimeSum_);
	return true;
}

bool MainMenu::Display(sf::RenderTarget& renderTarget) const
{
	plasma_.Display(renderTarget);
	menu_.Display(renderTarget);
	return true;
}

// Plain text file saving
void MainMenu::SaveSettings() const
{
	std::ofstream file(settingsFileName_);
	std::for_each(std::begin(playerControllerPtrsMenuItemPtrs_), std::end(playerControllerPtrsMenuItemPtrs_),
			[&file] (const std::shared_ptr<SelectItem<PlayerControllerPtrs>>& ptr)
			{
				file << ptr->GetPos() << std::endl;
			});
	file << worldSizeMenuItemPtr_->GetPos() << std::endl;
	file << wallProbabilityMenuItemPtr_->GetPos() << std::endl;
	file << obstacleProbabilityMenuItemPtr_->GetPos() << std::endl;
	file << itemProbabilityMenuItemPtr_->GetPos() << std::endl;
	file << speedMenuItemPtr_->GetPos() << std::endl;
	file << soundMenuItemPtr_->GetPos() << std::endl;
	file << blurAmountMenuItemPtr_->GetPos() << std::endl;

	std::cout << "Configuration saved to " << settingsFileName_ << std::endl;
}

// Plain text file loading
void MainMenu::LoadSettings()
{
	std::ifstream file(settingsFileName_);
	if (!file)
		return;

	std::for_each(std::begin(playerControllerPtrsMenuItemPtrs_), std::end(playerControllerPtrsMenuItemPtrs_),
			[&file] (const std::shared_ptr<SelectItem<PlayerControllerPtrs>>& ptr)
			{
				SelectItem<PlayerControllerPtrs>::size_type index(0);
				file >> index;
				ptr->SetPos(index);
			});

	SelectItem<Sizes>::size_type worldSizeIndex(0);
	SelectItem<Probabilities>::size_type wallProbabilityIndex(0);
	SelectItem<Probabilities>::size_type obstacleProbabilityIndex(0);
	SelectItem<Probabilities>::size_type itemProbabilityIndex(0);
	SelectItem<Floats>::size_type speedIndex(0);
	SelectItem<Floats>::size_type soundIndex(0);
	SelectItem<Floats>::size_type blurIndex(0);

	file >> worldSizeIndex;
	file >> wallProbabilityIndex;
	file >> obstacleProbabilityIndex;
	file >> itemProbabilityIndex;
	file >> speedIndex;
	file >> soundIndex;
	file >> blurIndex;
	if (file.fail())
	{
		std::cerr << "Unable to load configuration (" << settingsFileName_ << ") - Using default settings."
				<< std::endl;
		return;
	}

	// Forward the loaded selections to the menu items.
	worldSizeMenuItemPtr_->SetPos(worldSizeIndex);
	wallProbabilityMenuItemPtr_->SetPos(wallProbabilityIndex);
	obstacleProbabilityMenuItemPtr_->SetPos(obstacleProbabilityIndex);
	itemProbabilityMenuItemPtr_->SetPos(itemProbabilityIndex);
	speedMenuItemPtr_->SetPos(speedIndex);
	soundMenuItemPtr_->SetPos(soundIndex);
	blurAmountMenuItemPtr_->SetPos(blurIndex);

	std::cout << "Configuration loaded from " << settingsFileName_ << std::endl;
}

} /* namespace Dron */

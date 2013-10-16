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

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "../PlayerController.h"

#include "../../Plasma.h"

#include "../../GameState.h"
#include "../../Menu.h"
#include "../../Vector2D.h"
#include "../../MenuItems/EnterItem.h"
#include "../../MenuItems/SelectItem.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>
#include <random>
#include <memory>

namespace Dron
{

/*
 * The main menu of the game which includes the setup.
 * 
 * Settings will be loaded and saved.
 */
class MainMenu: public GameState
{
public:
	MainMenu();
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
protected:
	void StartGame();
	void QuitGame();
	void About();
	void SoundSettingsChanged();

	typedef std::vector<double> Doubles;
	typedef std::vector<float> Floats;
	typedef std::vector<int> Ints;
	typedef std::vector<std::string> Strings;
	typedef Doubles Probabilities;
	typedef std::vector<int> ObstacleGrowAmounts;
	typedef Vector2D<int> Size;
	typedef std::vector<Size> Sizes;
	typedef std::pair<std::string, sf::Color> NamedColor;
	typedef std::vector<NamedColor> NamedColors;

	// Color names for the players.
	NamedColors namedColors_;

	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;

	std::vector<std::shared_ptr<SelectItem<PlayerControllerPtrs>>>playerControllerPtrsMenuItemPtrs_;
	std::shared_ptr<SelectItem<Sizes>> worldSizeMenuItemPtr_;
	std::shared_ptr<SelectItem<Probabilities>> wallProbabilityMenuItemPtr_;
	std::shared_ptr<SelectItem<Probabilities>> obstacleProbabilityMenuItemPtr_;
	std::shared_ptr<SelectItem<Probabilities>> itemProbabilityMenuItemPtr_;
	std::shared_ptr<SelectItem<Floats>> speedMenuItemPtr_;
	std::shared_ptr<SelectItem<Strings>> soundMenuItemPtr_;
	std::shared_ptr<SelectItem<Ints>> blurAmountMenuItemPtr_;

	std::string settingsFileName_;

	void LoadSettings();
	void SaveSettings() const;

	float elapsedTimeSum_;

	// The actual menu
	Menu menu_;

	// Make the whole thing a bit less boring.
	Plasma plasma_;
};

typedef std::shared_ptr<PlayerController> PlayerControllerPtr;

} /* namespace Dron */

#endif /* MAINMENU_H_ */

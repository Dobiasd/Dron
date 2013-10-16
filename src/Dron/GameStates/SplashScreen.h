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

#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_

#include "../../GameState.h"

#include <string>

namespace Dron
{

/*
 * Generates the in game sounds and gives a random tip while showing.
 *
 * Model, View and Controller are joined because of their simplicity.
 */
class SplashScreen: public GameState
{
public:
	SplashScreen(const std::string& title);
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
private:
	std::string title_;
	bool firstFrame_;
	std::string tip_;
};

} /* namespace Dron */

#endif /* SPLASHSCREEN_H_ */

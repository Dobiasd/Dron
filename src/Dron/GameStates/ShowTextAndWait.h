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

#ifndef SHOWTEXTANDWAIT_H_
#define SHOWTEXTANDWAIT_H_

#include "../../GameState.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Dron
{

/*
 * Shows some text on the screen and waits for keyboard input.
 *
 * Model, View and Controller are joined because of their simplicity.
 */
class ShowTextAndWait: public GameState
{
public:
	ShowTextAndWait(const std::string& text, const sf::Color& color, const GameStatePtr nextStatePtr, float waitTime =
			1.f, const sf::Image& backgroundImage = sf::Image());
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
private:
	std::string text_;
	sf::Color color_;
	GameStatePtr nextStatePtr_;
	float elapsedTimeSum_;
	float waitTime_;
	sf::Image backgroundImage_;
};

} /* namespace Dron */

#endif /* SHOWTEXTANDWAIT_H_ */

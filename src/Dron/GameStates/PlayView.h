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

#ifndef DRON_PLAYVIEW_H_
#define DRON_PLAYVIEW_H_

#include "PlayModel.h"

#include "../../BlurPostEffect.h"

namespace sf
{
class Window;
class RenderTarget;
}

namespace Dron
{

/*
 * Displays the model (world, players, items, inventars)
 * based on a simple two-dimensional grid using rectangles.
 *
 * Scales with the Window.
 */
class PlayView
{
public:
	PlayView(const PlayModel& model, int blurAmount);

	typedef Vector2D<int> Vector;
	typedef sf::Rect<int> Rect;
	typedef Vector2D<float> FloatVector;

	// Display the referenced PlayModel.
	bool Display(sf::RenderTarget& renderTarget) const;

	// Some static helper functions for drawing.
	static void DrawRect(const Rect& rect, sf::RenderTarget& renderTarget, const sf::Color& color);
	static Rect PositionToRect(const World::Position& pos, const sf::RenderTarget& renderTarget, const World& world,
			const Vector& grow = Vector(0, 0));
	static FloatVector FloatPositionWindowCoordinate(const FloatVector& pos, const sf::RenderTarget& renderTarget,
			const World& world);
	static Vector GetStep(const sf::RenderTarget& renderTarget, const World& world);
	static sf::Color GetWallColor()
	{
		return sf::Color(96, 32, 16);
	}

private:
	typedef Vector Size;

	// More static helper functions for drawing.
	static void DrawGrid(const World& world, sf::RenderTarget& renderTarget, const Vector& tl,
			const World::Vector& step, const sf::Color& color);
	static void DrawLine(const Vector& from, const Vector& to, sf::RenderTarget& renderTarget, const sf::Color& color);
	static sf::Color Average(const sf::Color& lhs, const sf::Color& rhs, float weight1 = .5f);
	static Vector Center(const Rect& rect);
	static Vector GetDisplayTL(const sf::RenderTarget& renderTarget, const World& world);

	// Calculate the rectangle in the window representing a world's position.
	Rect PositionsToRect(const World::Positions& positions, const sf::RenderTarget& renderTarget, const Vector& grow =
			Vector(0, 0)) const;

	// All these things will be displayed.
	void DisplayItems(sf::RenderTarget& renderTarget) const;
	void DisplayWalls(sf::RenderTarget& renderTarget) const;
	void DisplayPlayers(sf::RenderTarget& renderTarget) const;
	void DisplayInventories(sf::RenderTarget& renderTarget) const;
	void DisplayAnimations(sf::RenderTarget& renderTarget) const;
	void DisplayBackgroundLines(sf::RenderTarget& renderTarget) const;

	// The model we are displaying here.
	const PlayModel& model_;

	int blurAmount_;

	// Don't let the GPU get bored. ;)
	BlurPostEffect blurPostEffect_;
};

} /* namespace Dron */

#endif /* DRON_PLAYVIEW_H_ */

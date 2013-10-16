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

#include "../World.h"
#include "CollectAnimation.h"

#include "../GameStates/PlayView.h"

namespace Dron
{

CollectAnimation::CollectAnimation(const sf::Color& color, const World::Position& position, const std::string& text) :
		color_(color), position_(position), elapsedTimeSum_(0.f), text_(text)
{
}

void CollectAnimation::Update(float elapsedTime)
{
	elapsedTimeSum_ += elapsedTime;
	if (elapsedTimeSum_ > 1.f)
		SetDone();
}

void CollectAnimation::Display(sf::RenderTarget& renderTarget, const World& world) const
{
	sf::String sfText(text_);

	// Adjust the text's scale to the display size.
	float sfTextScale(.3f * renderTarget.GetView().GetRect().GetWidth() / sfText.GetRect().GetWidth());
	sfText.Scale(sfTextScale, sfTextScale);

	// Increase the transparency gradually with time.
	sf::Color color(color_);
	color.a = static_cast<sf::Uint8>(255.f - 255.f * elapsedTimeSum_ / 1.f);
	sfText.SetColor(color);

	// Float away to the top right.
	Vector step(PlayView::GetStep(renderTarget, world));
	Vector floatingDirection(step.x_, -step.y_);
	Vector screenPos(
			PlayView::FloatPositionWindowCoordinate(position_, renderTarget, world)
					+ floatingDirection * 1.2f * elapsedTimeSum_);
	sfText.Move(screenPos.x_ - sfText.GetRect().GetWidth() / 2, screenPos.y_ - sfText.GetRect().GetHeight());

	renderTarget.Draw(sfText);
}

} /* namespace Dron */

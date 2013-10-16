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

#include "PlayView.h"

#include "../Player.h"
#include "../Animation.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <cassert>
#include <numeric>

namespace Dron
{

PlayView::PlayView(const PlayModel& model, int blurAmount) :
		model_(model), blurAmount_(blurAmount)
{
}

sf::Color PlayView::Average(const sf::Color& lhs, const sf::Color& rhs, float weight1)
{
	float weight2(1.f - weight1);
	return sf::Color(static_cast<sf::Uint8>(weight1 * lhs.r + weight2 * rhs.r),
			static_cast<sf::Uint8>(weight1 * lhs.g + weight2 * rhs.g),
			static_cast<sf::Uint8>(weight1 * lhs.b + weight2 * rhs.b));
}

PlayView::Rect PlayView::PositionsToRect(const World::Positions& positions, const sf::RenderTarget& renderTarget,
		const Vector& grow) const
{
	assert(!positions.empty());
	World::Position initPos(positions.front());
	// Return a Rect enclosing all position's Rects.
	return std::accumulate(std::begin(positions) + 1, std::end(positions),
			PositionToRect(initPos, renderTarget, model_.world_, grow),
			[&](const Rect& rect, const World::Position& pos) -> PlayView::Rect
			{
				Rect newRect(PositionToRect(pos, renderTarget, model_.world_, grow));
				// Create the Rect enclosing the one for the new position
				// and the already accumulated.
				return PlayView::Rect(std::min(rect.Left, newRect.Left),
						std::min(rect.Top, newRect.Top),
						std::max(rect.Right, newRect.Right),
						std::max(rect.Bottom, newRect.Bottom));
			});
}

void PlayView::DisplayPlayers(sf::RenderTarget& renderTarget) const
{
	std::for_each(std::begin(model_.playerPtrs_), std::end(model_.playerPtrs_),
			[&](ConstPlayerPtr playerPtr)
			{
				sf::Color color = playerPtr->GetColor();
				float whiteFraction = .7f;
				sf::Color bloomColor( Average( sf::Color::White, color, whiteFraction));
				Vector bloomShrink(-4, -4);
				const Player::Positions& positions(playerPtr->GetPositions());
				std::for_each(std::begin(positions), std::end(positions), [&](const Player::Position& pos)
						{
							PlayView::DrawRect(PositionToRect(pos, renderTarget, model_.world_), renderTarget, color);
							PlayView::DrawRect(PositionToRect(pos, renderTarget, model_.world_, bloomShrink), renderTarget, bloomColor);
						});
				// Draw the shiny part of the bodies' elements.
				// Elements of contiguous positions are merged.
				// Blurring in the post effect will let it bloom.
				for (auto it(std::begin(positions)); it != std::end(positions); ++it)
				{
					const Player::Position& pos(*it);

					// Do we have a predecessor and is it directly adjacent?
					if (it != std::begin(positions))
					{
						auto itLast(it);
						std::advance(itLast, -1);
						if (ManhattanDistance(*itLast, pos) == 1)
						{
							World::Positions adjacentPositions(1, *itLast);
							adjacentPositions.push_back(pos);
							DrawRect(PositionsToRect(adjacentPositions, renderTarget, bloomShrink), renderTarget, bloomColor);
						}
					}
					auto itNext(it);
					std::advance(itNext, 1);
					// Do we have a successor and is it directly adjacent?
					if (itNext != std::end(positions) && (ManhattanDistance(pos, *itNext) == 1))
					{
						World::Positions adjacentPositions(1, pos);
						adjacentPositions.push_back(*itNext);
						DrawRect(PositionsToRect(adjacentPositions, renderTarget, bloomShrink), renderTarget, bloomColor);
					}
				}

				// Accentuate the head's shininess.
				if (!positions.empty())
				{
					DrawRect(PositionToRect(positions.front(), renderTarget, model_.world_, bloomShrink), renderTarget, sf::Color::White);
				}
			});
}

PlayView::Vector PlayView::Center(const Rect& rect)
{
	return Vector((rect.Left + rect.Right) / 2, (rect.Top + rect.Bottom) / 2);
}

// Connect the fronts and back of all living players.
void PlayView::DisplayBackgroundLines(sf::RenderTarget& renderTarget) const
{
	float lineWidth(static_cast<float>(GetStep(renderTarget, model_.world_).x_) / 3.f);
	PlayerPtrs alivePlayers(model_.GetAlivePlayers());
	std::for_each(std::begin(alivePlayers), std::end(alivePlayers),
			[&](ConstPlayerPtr playerPtr1)
			{
				sf::Color lineColor(playerPtr1->GetColor());
				lineColor.a = 8;
				FloatVector player1Pos(Center(PositionToRect(playerPtr1->GetFrontPosition(), renderTarget, model_.world_)));
				std::for_each(std::begin(alivePlayers), std::end(alivePlayers), [&](ConstPlayerPtr playerPtr2)
						{
							PlayView::FloatVector player2Pos(Center(PositionToRect(playerPtr2->GetBackPosition(), renderTarget, model_.world_)));
							PlayView::FloatVector diff(player2Pos - player1Pos);
							PlayView::FloatVector p1(player1Pos-diff);
							PlayView::FloatVector p2(player2Pos+diff);
							renderTarget.Draw(sf::Shape::Line(p1.x_, p1.y_, p2.x_, p2.y_, lineWidth, lineColor));
						});
			});
}

void PlayView::DisplayInventories(sf::RenderTarget& renderTarget) const
{
	PlayerPtrs::size_type playerNum(0);
	std::for_each(std::begin(model_.playerPtrs_), std::end(model_.playerPtrs_), [&](ConstPlayerPtr playerPtr)
	{
		const ItemPtrs& itemPtrs(playerPtr->GetItemPtrs());
		World::Position pos(0, model_.world_.GetHeight() + 2 + playerNum);
		if (playerPtr->IsAlive())
		{
			DrawRect(PositionToRect(pos, renderTarget, model_.world_), renderTarget, playerPtr->GetColor());
			ItemPtrs::size_type itemNum(0);
			std::for_each(std::begin(itemPtrs), std::end(itemPtrs), [&](const ItemPtr itemPtr)
					{
						World::Position itemPos(pos + World::Position(2 + itemNum, 0));
						PlayView::Rect rect(PositionToRect(itemPos, renderTarget, model_.world_));
						itemPtr->Draw(rect, renderTarget);
						++itemNum;
					});
		}
		++playerNum;
	});
}

void PlayView::DrawGrid(const World& world, sf::RenderTarget& renderTarget, const Vector& tl, const Vector& step,
		const sf::Color& color)
{
	Vector br(tl + world.GetSize() * step);
	Size size(world.GetSize());
	for (int y(0); y <= size.y_; ++y)
	{
		int yPos(tl.y_ + y * step.y_);
		DrawLine(Vector(tl.x_, yPos), Vector(br.x_, yPos), renderTarget, color);
	}
	for (int x(0); x <= size.x_; ++x)
	{
		int xPos(tl.x_ + x * step.x_);
		DrawLine(Vector(xPos, tl.y_), Vector(xPos, br.y_), renderTarget, color);
	}
}

PlayView::Vector PlayView::GetDisplayTL(const sf::RenderTarget& renderTarget, const World& world)
{
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	Size windowSize(static_cast<int>(width), static_cast<int>(height));
	Vector showSize((Vector(2, 2 + 7) + world.GetSize()) * GetStep(renderTarget, world));
	return (windowSize - showSize) / 2;
}

PlayView::Vector PlayView::GetStep(const sf::RenderTarget& renderTarget, const World& world)
{
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	Size windowSize(static_cast<int>(width), static_cast<int>(height));
	Vector step((windowSize - Vector(1, 1)) / (world.GetSize() + Vector(2, 2 + 7)));
	int stepLength(std::min(step.x_, step.y_));
	return Vector(stepLength, stepLength);
}

PlayView::Rect PlayView::PositionToRect(const World::Position& pos, const sf::RenderTarget& renderTarget,
		const World& world, const Vector& grow)
{
	Vector step(GetStep(renderTarget, world));
	Vector tl(GetDisplayTL(renderTarget, world));
	Vector posTL(tl + pos * step - grow);
	Vector posBR(tl + (pos + Vector(1, 1)) * step + grow);
	posBR -= Vector(1, 1);
	posTL += Vector(1, 1);
	return Rect(posTL.x_, posTL.y_, posBR.x_, posBR.y_);
}

PlayView::FloatVector PlayView::FloatPositionWindowCoordinate(const FloatVector& pos,
		const sf::RenderTarget& renderTarget, const World& world)
{
	Vector step(GetStep(renderTarget, world));
	Vector tl(GetDisplayTL(renderTarget, world));
	FloatVector floatStep(step);
	return FloatVector(FloatVector(tl) + pos * floatStep + floatStep / 2.f);
}

void PlayView::DrawRect(const Rect& rect, sf::RenderTarget& renderTarget, const sf::Color& color)
{
	renderTarget.Draw(
			sf::Shape::Rectangle(static_cast<float>(rect.Left), static_cast<float>(rect.Top),
					static_cast<float>(rect.Right), static_cast<float>(rect.Bottom), color));
}

void PlayView::DrawLine(const Vector& from, const Vector& to, sf::RenderTarget& renderTarget, const sf::Color& color)
{
	renderTarget.Draw(
			sf::Shape::Line(static_cast<float>(from.x_), static_cast<float>(from.y_), static_cast<float>(to.x_),
					static_cast<float>(to.y_), 1, color));
}

void PlayView::DisplayWalls(sf::RenderTarget& renderTarget) const
{
	std::for_each(std::begin(model_.world_.wallPositions_), std::end(model_.world_.wallPositions_),
			[&](const World::Position& pos)
			{
				DrawRect(PositionToRect(pos, renderTarget, model_.world_), renderTarget, GetWallColor());
			});
}
void PlayView::DisplayItems(sf::RenderTarget& renderTarget) const
{
	std::for_each(std::begin(model_.world_.itemPtrs_), std::end(model_.world_.itemPtrs_), [&](const ItemPtr itemPtr)
	{
		itemPtr->Draw(PositionToRect(itemPtr->GetPosition(), renderTarget, model_.world_), renderTarget);
	});
}

void PlayView::DisplayAnimations(sf::RenderTarget& renderTarget) const
{
	std::for_each(std::begin(model_.world_.animationPtrs_), std::end(model_.world_.animationPtrs_),
			[&](const AnimationPtr & animationPtr)
			{
				animationPtr->Display(renderTarget, model_.world_);
			});
}

bool PlayView::Display(sf::RenderTarget& renderTarget) const
{
	// Instead of clearing the screen it is wiped carefully
	// to preserve the colors of the last frame so that
	// the vanishing elements have some afterglow.
	float width(renderTarget.GetView().GetRect().GetWidth());
	float height(renderTarget.GetView().GetRect().GetHeight());
	renderTarget.Draw(sf::Shape::Rectangle(0.f, 0.f, width, height, sf::Color(0, 0, 0, 64)));

	DisplayBackgroundLines(renderTarget);
	DisplayPlayers(renderTarget);

	// Blur the players a lot.
	// This effect could also probably be achieved with less overall calculations
	// by preblurring images of elements and use the results as sprites to assemble the in game graphics.
	blurPostEffect_.AdjustToWindowSize(renderTarget);
	for (int i = 0; i < blurAmount_; ++i)
		blurPostEffect_.Apply(renderTarget);

	DisplayItems(renderTarget);
	DisplayWalls(renderTarget);
	DisplayInventories(renderTarget);
	DisplayAnimations(renderTarget);
	DrawGrid(model_.world_, renderTarget, GetDisplayTL(renderTarget, model_.world_),
			GetStep(renderTarget, model_.world_), sf::Color(127, 127, 127));

	return true;
}

} /* namespace Dron */

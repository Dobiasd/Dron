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

#ifndef DRON_WORLD_H_
#define DRON_WORLD_H_

#include "Animation.h"
#include "Item.h"

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <list>
#include <vector>
#include <memory>

namespace Dron
{

class Player;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<const Player> ConstPlayerPtr;
typedef std::vector<PlayerPtr> PlayerPtrs;
typedef std::vector<ConstPlayerPtr> ConstPlayerPtrs;

/*
 * Model of a tron world with walls (including obstacles) and items
 *
 * Empty fields are not represented explicitly but calculated on the fly.
 */
class World
{
public:
	typedef Vector2D<int> Vector;
	typedef Vector Size;
	typedef Vector Position;
	typedef std::vector<Position> Positions;

	// Amounts are values in [0,1] defining the probability of a field to initially be of the corresponding type.
	World(const Size& size, double wallAmount, double obstacleAmount);

	// Calculate the next position based on a current.
	// Includes wrapping; our world is topologically a torus.
	Position NextPosition(const Position& position, const Vector& direction) const;

	// Returns true if the position was actually occupied by a wall.
	bool RemoveWallPosition(const Position& pos);

	// Returns true if the position was actually occupied by an item.
	bool RemoveItemPosition(const Position& pos);

	// All non-free positions. Positions can be occupied by walls, items or players.
	Positions GetOccupiedPositions(const Player& player, ConstPlayerPtrs otherPlayerPtrs) const;
	static Positions ConcatPlayersPositions(ConstPlayerPtrs playerPtrs);
	static Positions ConcatItemPositions(const ItemPtrs& itemPtrs);
	Positions GetCornerPositions() const;
	Positions GetFreePositions(ConstPlayerPtrs playerPtrs) const;

	const Positions& GetWallPositions() const
	{
		return wallPositions_;
	}

	int GetWidth() const
	{
		return size_.x_;
	}
	int GetHeight() const
	{
		return size_.y_;
	}
	void InsertItem(const ItemPtr itemPtr);
	ItemPtrs& GetItemPtrs()
	{
		return itemPtrs_;
	}
	const ItemPtrs& GetItemPtrs() const
	{
		return itemPtrs_;
	}
	const Size& GetSize() const
	{
		return size_;
	}
	void AddAnimationPtr(const AnimationPtr ptr)
	{
		animationPtrs_.push_back(ptr);
	}
	void AddAnimationPtrs(const AnimationPtrs& ptrs)
	{
		animationPtrs_.insert(std::end(animationPtrs_), std::begin(ptrs), std::end(ptrs));
	}
	void UpdateAnimations(float elapsedTime);

protected:
	friend class PlayModel;
	friend class PlayView;
	ItemPtrs itemPtrs_;
	Size size_;
	Positions wallPositions_;
	AnimationPtrs animationPtrs_;
};

} /* namespace Dron */

#endif /* DRON_WORLD_H_ */

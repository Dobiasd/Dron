#include "World.h"

#include "Player.h"
#include "Animation.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <numeric>
#include <iterator>

namespace Dron
{

World::World(const Size& size, double wallAmount, double obstacleAmount) :
		size_(size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	// Generate surrounding walls.
	// Holes are distributed symmetrically to make wrapping possible without the use of battering rams.

	// Start with the walls on the top and the bottom.
	for (int x(1); x < size_.x_ - 1; ++x)
	{
		if (dis(gen) < wallAmount)
		{
			wallPositions_.push_back(Vector(x, 0));
			wallPositions_.push_back(Vector(x, size_.y_ - 1));
		}
	}

	// Continue with the walls on the left and the right.
	for (int y(1); y < size_.y_ - 1; ++y)
	{
		if (dis(gen) < wallAmount)
		{
			wallPositions_.push_back(Vector(0, y));
			wallPositions_.push_back(Vector(size_.x_ - 1, y));
		}
	}

	// Generate obstacles
	for (int y(1); y < size.y_ - 1; ++y)
	{
		for (int x(1); x < size.x_ - 1; ++x)
		{
			if (dis(gen) < obstacleAmount)
			{
				wallPositions_.push_back(Vector(x, y));
			}
		}
	}
}

void World::InsertItem(const ItemPtr& itemPtr)
{
	itemPtrs_.push_back(itemPtr);
}

World::Position World::NextPosition(const Position& position, const Vector& direction) const
{
	Position nextPosition(position + direction);

	// Torus wapping.
	if (nextPosition.x_ < 0)
		nextPosition.x_ = size_.x_ - 1;
	if (nextPosition.y_ < 0)
		nextPosition.y_ = size_.y_ - 1;
	if (nextPosition.x_ >= size_.x_)
		nextPosition.x_ = 0;
	if (nextPosition.y_ >= size_.y_)
		nextPosition.y_ = 0;
	return nextPosition;
}

bool World::RemoveWallPosition(const Position& pos)
{
	Positions::size_type oldSize(wallPositions_.size());
	wallPositions_.erase(std::remove(std::begin(wallPositions_), std::end(wallPositions_), pos),
			std::end(wallPositions_));
	return oldSize != wallPositions_.size();
}

bool World::RemoveItemPosition(const Position& pos)
{
	Positions::size_type oldSize(itemPtrs_.size());
	itemPtrs_.remove_if([&](const ItemPtr itemPtr)
	{
		return itemPtr->GetPosition() == pos;
	});
	return oldSize != itemPtrs_.size();
}

// If profiling will reveal one of the following functions to be a performance bottle neck
// because of repetitive calling, the results could be precalculated with every time step.
// For now time spend in these functions is not significant.
World::Positions World::ConcatPlayersPositions(ConstPlayerPtrs playerPtrs)
{
	return std::accumulate(std::begin(playerPtrs), std::end(playerPtrs), World::Positions(),
			[](World::Positions& positions, ConstPlayerPtr playerPtr) -> World::Positions
			{
				const Player::Positions& playerPositions(playerPtr->GetPositions());
				positions.insert(std::end(positions), std::begin(playerPositions), std::end(playerPositions));
				return positions;
			});
}

World::Positions World::ConcatItemPositions(const ItemPtrs& itemPtrs)
{
	return std::accumulate(std::begin(itemPtrs), std::end(itemPtrs), Positions(),
			[](Positions& positions, const ItemPtr itemPtr) -> World::Positions
			{
				positions.push_back(itemPtr->GetPosition());
				return positions;
			});
}

World::Positions World::GetCornerPositions() const
{
	Positions cornerPositions;
	cornerPositions.push_back(Position(0, 0));
	cornerPositions.push_back(Position(GetWidth() - 1, 0));
	cornerPositions.push_back(Position(0, GetHeight() - 1));
	cornerPositions.push_back(Position(GetWidth() - 1, GetHeight() - 1));
	return cornerPositions;
}

World::Positions World::GetOccupiedPositions(const Player& player, ConstPlayerPtrs otherPlayerPtrs) const
{
	// Get positions of other players.
	Positions occupiedPositions(ConcatPlayersPositions(otherPlayerPtrs));

	// Append positions of the one player.
	const Player::Positions& playerPositionsSource(player.GetPositions());
	Positions playerPositions(std::begin(playerPositionsSource), std::end(playerPositionsSource));
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(playerPositions), std::end(playerPositions));

	// Append wall positions.
	Positions wallPositions(GetWallPositions());
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(wallPositions), std::end(wallPositions));

	// Append positions of Items.
	Positions itemPositions(ConcatItemPositions(itemPtrs_));
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(itemPositions), std::end(itemPositions));

	// Append the 4 corner positions.
	// They always count as occupied because no player wants to start here,
	// nor shall items be positioned here.
	Positions cornerPositions(GetCornerPositions());
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(cornerPositions), std::end(cornerPositions));

	return occupiedPositions;
}

World::Positions World::GetFreePositions(ConstPlayerPtrs playerPtrs) const
{
	// Get all possible positions.
	Positions allPositions;
	for (int y(0); y < GetHeight(); ++y)
		for (int x(0); x < GetWidth(); ++x)
			allPositions.push_back(Position(x, y));
	auto PositionLess = [&] (const Position& lhs, const Position& rhs)
	{
		return lhs.y_*GetWidth()+lhs.x_ < rhs.y_*GetWidth()+rhs.x_;
	};

	// Fetch occupied positions of players.
	Positions occupiedPositions(ConcatPlayersPositions(playerPtrs));

	// Append corners.
	Positions cornerPositions(GetCornerPositions());
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(cornerPositions), std::end(cornerPositions));

	// Append wall positions.
	World::Positions wallPositions(GetWallPositions());
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(wallPositions), std::end(wallPositions));

	// Append positions of Items.
	Positions itemPositions(ConcatItemPositions(itemPtrs_));
	occupiedPositions.insert(std::end(occupiedPositions), std::begin(itemPositions), std::end(itemPositions));

	// Sort positions by index (y*width+x).
	std::sort(std::begin(allPositions), std::end(allPositions), PositionLess);
	std::sort(std::begin(occupiedPositions), std::end(occupiedPositions), PositionLess);

	// Make occupied positions unique.
	occupiedPositions.erase(std::unique(std::begin(occupiedPositions), std::end(occupiedPositions)),
			std::end(occupiedPositions));

	// freePositions = allPositions - occupiedPositions
	Positions freePositions;
	std::set_difference(std::begin(allPositions), std::end(allPositions), std::begin(occupiedPositions),
			std::end(occupiedPositions), std::back_inserter(freePositions), PositionLess);

	return freePositions;
}

void World::UpdateAnimations(float elapsedTime)
{
	std::for_each(std::begin(animationPtrs_), std::end(animationPtrs_), [&elapsedTime](AnimationPtr animationPtr)
	{
		animationPtr->Update(elapsedTime);
	});

	// Remove animations that have ended.
	animationPtrs_.erase(
			std::remove_if(std::begin(animationPtrs_), std::end(animationPtrs_), [](AnimationPtr animationPtr) -> bool
			{
				return animationPtr->IsDone();
			}), std::end(animationPtrs_));
}

} /* namespace Dron */

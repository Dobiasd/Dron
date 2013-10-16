#ifndef DRON_ITEM_H_
#define DRON_ITEM_H_

#include "../Vector2D.h"

#include "Animation.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <string>
#include <memory>
#include <list>

namespace sf
{
class RenderTarget;
}

namespace Dron
{

class Player;
class World;

/*
 * Abstract base class for items in the tron world.
 * Depending on the derived class Items can be used either at time of collection
 * or end up in the players inventory.
 * They decay after a given amount of time steps while located in the world
 * and last forever inside a players inventory.
 */
class Item
{
public:
	typedef sf::Rect<int> Rect;
	typedef Vector2D<int> Position;

	// Create at a specific positions and with a time to live
	Item(const Position& position, std::size_t remainingSteps);

	virtual ~Item()
	{
	}

	const Position& GetPosition() const
	{
		return position_;
	}

	// Derived items have to implement how they will be drawn.
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const = 0;

	// What happens when the owning player hits a wall? Is it handled?
	virtual bool HitWall(const Position&, Player&, World&)
	{
		return false;
	}

	// What happens when the owning player hits another player? Is it handled?
	// The First player it the hitter/owner; the second player is the hittee.
	virtual bool HitOtherPlayer(const Position&, Player&, Player&, World&)
	{
		return false;
	}

	// What happens when the owning player hits himself? Is it handled?
	virtual bool HitSelf(const Position&, Player&, World&)
	{
		return false;
	}

	// What happens when the owning players tail shrinks? Can the item intervene?
	virtual bool ShrinkTail(Player&)
	{
		return false;
	}

	// Decay one time step
	virtual void Decay();

	// Is the item decayed and should be removed from the world?
	virtual bool IsDecayed();

	// Is the derived item used immediately at contact? 
	virtual bool GetUsedImmediately(Player&, World&)
	{
		return false;
	}

	// Can the derived item be collected?
	virtual bool GetCollected(Player&, World&)
	{
		return false;
	}

	// How is the derived item called?
	virtual std::string GetName() const = 0;

protected:
	static void DrawRect(const Rect& rect, sf::RenderTarget& renderTarget, const sf::Color& color);
	Position position_;
	std::size_t remainingSteps_;
};

typedef std::shared_ptr<Item> ItemPtr;
typedef std::shared_ptr<const Item> ConstItemPtr;
typedef std::list<ItemPtr> ItemPtrs;

} /* namespace Dron */

#endif /* DRON_ITEM_H_ */

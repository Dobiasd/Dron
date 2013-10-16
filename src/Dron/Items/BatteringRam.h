#ifndef DRON_BATTERINGRAM_H_
#define DRON_BATTERINGRAM_H_

#include "../Item.h"

namespace Dron
{

/*
 * A BatteringRam can be collected and used one single time to eliminate a wall or enemy field.
 */
class BatteringRam: public Item
{
public:
	BatteringRam(const Position& position, std::size_t remainingSteps);
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
	override;
	virtual std::string GetName() const
	override;

	// Everything that stands in the way will be nuked.
	virtual bool HitWall(const Position& pos, Player& player, World& world)
	override;
	virtual bool HitSelf(const Position& pos, Player& player, World& world)
	override;
	virtual bool HitOtherPlayer(const Position& pos, Player& player, Player& other, World& world)
	override;
	virtual bool GetCollected(Player& player, World& world)
	override;
};

} /* namespace Dron */
#endif /* DRON_BATTERINGRAM_H_ */

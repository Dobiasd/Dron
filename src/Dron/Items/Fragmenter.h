#ifndef DRON_Fragmenter_H_
#define DRON_Fragmenter_H_

#include "../Item.h"

namespace Dron
{

/*
 * A Fragmenter will disintegrate the players tail into pieces.
 */
class Fragmenter: public Item
{
public:
	Fragmenter(const Position& position, std::size_t remainingSteps);
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
	override;
	virtual std::string GetName() const
	override;
	virtual bool GetUsedImmediately(Player& player, World& world)
	override;
};

} /* namespace Dron */

#endif /* DRON_Fragmenter_H_ */

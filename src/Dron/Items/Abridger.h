#ifndef DRON_ABRIDGER_H_
#define DRON_ABRIDGER_H_

#include "../Item.h"

namespace Dron
{

/*
 * The Abridger will shorten the collecting player immediately to its minimum length.
 */
class Abridger: public Item
{
public:
	Abridger(const Position& position, std::size_t remainingSteps);
	virtual void Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
	override;
	virtual std::string GetName() const
	override;
	virtual bool GetUsedImmediately(Player&, World& world)
	override;
};

} /* namespace Dron */
#endif /* DRON_ABRIDGER_H_ */

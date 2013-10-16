#ifndef DRON_COLLECTANIMATION_H_
#define DRON_COLLECTANIMATION_H_

#include "../Animation.h"

namespace Dron
{

/*
 * An floating Text that is presented when an item is collected or used immediately by a player.
 */
class CollectAnimation: public Animation
{
public:
	CollectAnimation(const sf::Color& color, const World::Position& position, const std::string& text);
	virtual void Update(float elapsedTime)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const World& world) const
	override;
protected:
	typedef Vector2D<float> Vector;
	sf::Color color_;
	World::Position position_;
	float elapsedTimeSum_;
	std::string text_;
};

} /* namespace Dron */

#endif /* DRON_COLLECTANIMATION_H_ */

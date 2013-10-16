#ifndef DRON_BATTERINGRAMANIMATION_H_
#define DRON_BATTERINGRAMANIMATION_H_

#include "../Animation.h"
#include "../../Vector2D.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <random>

namespace Dron
{

/*
 * An Animation that mimics the process of broken bits flapping away.
 */
class BatteringRamAnimation: public Animation
{
public:
	BatteringRamAnimation(const sf::Color& color, const World::Position& position, std::size_t parts = 16,
			float duration = .7f);
	virtual void Update(float elapsedTime)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const World& world) const
	override;
protected:
	sf::Color color_;
	World::Position position_;
	float elapsedTimeSum_;
	float duration_;
	typedef Vector2D<float> Vector;

	/*
	 * Helper structure for storing the flying bits.
	 */
	struct Element
	{
		Element(const Vector& pos, const Vector& size, const Vector& speed, float rotationSpeed, float angle = 0.f) :
				pos_(pos), size_(size), speed_(speed), rotationSpeed_(rotationSpeed), angle_(angle)
		{
		}
		void Update()
		{
			pos_ += speed_;
			angle_ += rotationSpeed_;
		}
		Vector pos_;
		Vector size_;
		Vector speed_;
		float rotationSpeed_;
		float angle_;
	};
	typedef std::vector<Element> Elements;
	Elements elements_;

	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_real_distribution<> randomDoubleDistributionSpeed_;
	mutable std::uniform_real_distribution<> randomDoubleDistributionSize_;
	mutable std::uniform_real_distribution<> randomDoubleDistributionRotSpeed_;
};

} /* namespace Dron */

#endif /* DRON_BATTERINGRAMANIMATION_H_ */

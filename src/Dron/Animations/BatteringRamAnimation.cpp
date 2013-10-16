#include "../World.h"
#include "BatteringRamAnimation.h"

#include "../GameStates/PlayView.h"

namespace Dron
{

BatteringRamAnimation::BatteringRamAnimation(const sf::Color& color, const World::Position& position, std::size_t parts,
		float duration) :
		color_(color), position_(position), elapsedTimeSum_(0.f), duration_(duration), randomGenerator_(
				randomDevice_()), randomDoubleDistributionSpeed_(-.06f, .06f), randomDoubleDistributionSize_(0.3f,
				0.7f), randomDoubleDistributionRotSpeed_(-4.f, 4.f)
{
	// Initialize the elements with random values.
	for (std::size_t i(0); i < parts; ++i)
	{
		Vector speed(static_cast<float>(randomDoubleDistributionSpeed_(randomGenerator_)),
				static_cast<float>(randomDoubleDistributionSpeed_(randomGenerator_)));
		Vector floatPosition(position);
		float rotationSpeed(static_cast<float>(randomDoubleDistributionRotSpeed_(randomGenerator_)));
		Vector size(static_cast<float>(randomDoubleDistributionSize_(randomGenerator_)),
				static_cast<float>(randomDoubleDistributionSize_(randomGenerator_)));
		elements_.push_back(Element(floatPosition, size, speed, rotationSpeed));
	}
}

void BatteringRamAnimation::Update(float elapsedTime)
{
	// Update the position of all the elements.
	std::for_each(std::begin(elements_), std::end(elements_), [&](Element& element)
	{
		element.Update();
		element = element;
	});

	elapsedTimeSum_ += elapsedTime;

	// Is it enough?
	if (elapsedTimeSum_ > duration_)
		SetDone();
}

void BatteringRamAnimation::Display(sf::RenderTarget& renderTarget, const World& world) const
{
	std::for_each(std::begin(elements_), std::end(elements_), [&](const Element& element)
	{
		// Calculate the size of the element on the screen.
			BatteringRamAnimation::Vector screenRectSizeTL(PlayView::FloatPositionWindowCoordinate(
							BatteringRamAnimation::Vector(0.f, 0.f), renderTarget, world));
			BatteringRamAnimation::Vector screenRectSizeBR(PlayView::FloatPositionWindowCoordinate(element.size_, renderTarget, world));
			BatteringRamAnimation::Vector screenRectSize(screenRectSizeBR - screenRectSizeTL);

			// Calculate the position of the element on the screen.
			BatteringRamAnimation::Vector screenPos(PlayView::FloatPositionWindowCoordinate(element.pos_, renderTarget, world));

			// Draw the outline half transparent.
			sf::Color outlineColor(color_);
			outlineColor.a = 127;

			sf::Shape rect(sf::Shape::Rectangle(0.f, 0.f, screenRectSize.x_, screenRectSize.y_, color_, 1.f, outlineColor));
			rect.SetPosition(screenPos.x_, screenPos.y_);

			// Rotate around the elements center.
			rect.SetCenter(screenRectSize.x_/ 2.f, screenRectSize.y_ / 2.f);
			rect.Rotate(element.angle_);

			renderTarget.Draw(rect);
		});
}

} /* namespace Dron */

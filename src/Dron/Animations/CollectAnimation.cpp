#include "../World.h"
#include "CollectAnimation.h"

#include "../GameStates/PlayView.h"

namespace Dron
{

CollectAnimation::CollectAnimation(const sf::Color& color, const World::Position& position, const std::string& text) :
		color_(color), position_(position), elapsedTimeSum_(0.f), text_(text)
{
}

void CollectAnimation::Update(float elapsedTime)
{
	elapsedTimeSum_ += elapsedTime;
	if (elapsedTimeSum_ > 1.f)
		SetDone();
}

void CollectAnimation::Display(sf::RenderTarget& renderTarget, const World& world) const
{
	sf::String sfText(text_);

	// Adjust the text's scale to the display size.
	float sfTextScale(.3f * renderTarget.GetView().GetRect().GetWidth() / sfText.GetRect().GetWidth());
	sfText.Scale(sfTextScale, sfTextScale);

	// Increase the transparency gradually with time.
	sf::Color color(color_);
	color.a = static_cast<sf::Uint8>(255.f - 255.f * elapsedTimeSum_ / 1.f);
	sfText.SetColor(color);

	// Float away to the top right.
	Vector step(PlayView::GetStep(renderTarget, world));
	Vector floatingDirection(step.x_, -step.y_);
	Vector screenPos(
			PlayView::FloatPositionWindowCoordinate(position_, renderTarget, world)
					+ floatingDirection * 1.2f * elapsedTimeSum_);
	sfText.Move(screenPos.x_ - sfText.GetRect().GetWidth() / 2, screenPos.y_ - sfText.GetRect().GetHeight());

	renderTarget.Draw(sfText);
}

} /* namespace Dron */

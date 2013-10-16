#include "Item.h"

#include "GameStates/PlayView.h"

#include "../Synthesizer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace Dron
{

Item::Item(const Position& position, std::size_t remainingSteps) :
		position_(position), remainingSteps_(remainingSteps)
{
	Synthesizer::PlaySound("NewItem");
}

void Item::DrawRect(const Rect& rect, sf::RenderTarget& renderTarget, const sf::Color& color)
{
	PlayView::DrawRect(rect, renderTarget, color);
}

void Item::Decay()
{
	if (remainingSteps_)
	{
		--remainingSteps_;
		if (!remainingSteps_)
			Synthesizer::PlaySound("ItemDecayed");
	}
}

bool Item::IsDecayed()
{
	return !remainingSteps_;
}

} /* namespace Dron */

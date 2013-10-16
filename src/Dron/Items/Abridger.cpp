#include "Abridger.h"

#include "../World.h"
#include "../Player.h"
#include "../Animations/CollectAnimation.h"

#include <iostream>

namespace Dron
{

Abridger::Abridger(const Position& position, std::size_t remainingSteps) :
		Item(position, remainingSteps)
{
}

void Abridger::Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
{
	Rect itemRect(rect.Left + 1, rect.Top + 1, rect.Right - 1, rect.Bottom - 1);
	Item::DrawRect(itemRect, renderTarget, sf::Color(127, 255, 0));
}

// The player shrinks at contact.
bool Abridger::GetUsedImmediately(Player& player, World& world)
{
	std::cout << player.GetName() << " shrunk." << std::endl;
	player.ShrinkToMinLength();
	world.AddAnimationPtr(
			AnimationPtr(
					new CollectAnimation(sf::Color(127, 255, 0), position_,
							player.GetName() + " used an " + GetName() + ".")));
	return true;
}

std::string Abridger::GetName() const
{
	return "Abridger";
}

} /* namespace Dron */

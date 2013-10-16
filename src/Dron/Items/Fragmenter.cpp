#include "Fragmenter.h"

#include "../World.h"
#include "../Player.h"
#include "../Animations/CollectAnimation.h"

#include <iostream>

namespace Dron
{

Fragmenter::Fragmenter(const Position& position, std::size_t remainingSteps) :
		Item(position, remainingSteps)
{
}

void Fragmenter::Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
{
	Rect itemRect(rect.Left + 1, rect.Top + 1, rect.Right - 1, rect.Bottom - 1);
	Item::DrawRect(itemRect, renderTarget, sf::Color(127, 0, 255));
}

bool Fragmenter::GetUsedImmediately(Player& player, World& world)
{
	std::cout << player.GetName() << " disintegrated." << std::endl;
	Player::Positions positions(player.GetPositions());
	if (positions.size() < 3)
		return true;

	// Iterate from the back of the player to its front
	// and remove every send element.
	auto itFront(player.GetPositions().rend());
	std::advance(itFront, -1);
	auto it(player.GetPositions().rbegin());
	while (positions.size() > 3 && it != itFront && it != player.GetPositions().rend())
	{
		positions.remove(*it);
		std::advance(it, 2);
	}
	player.SetPositions(positions);

	world.AddAnimationPtr(
			AnimationPtr(
					new CollectAnimation(sf::Color(127, 0, 255), position_,
							player.GetName() + " used a " + GetName() + ".")));
	return true;
}

std::string Fragmenter::GetName() const
{
	return "Fragmenter";
}

} /* namespace Dron */

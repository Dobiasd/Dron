#include "BatteringRam.h"
#include "../Player.h"
#include "../World.h"
#include "../Animations/BatteringRamAnimation.h"
#include "../Animations/CollectAnimation.h"
#include "../../Synthesizer.h"
#include "../GameStates/PlayView.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <iostream>
#include <memory>

namespace Dron
{

BatteringRam::BatteringRam(const Position& position, std::size_t remainingSteps) :
		Item(position, remainingSteps)
{
}

void BatteringRam::Draw(const Rect& rect, sf::RenderTarget& renderTarget) const
{
	Rect itemRect(rect.Left + 1, rect.Top + 1, rect.Right - 1, rect.Bottom - 1);
	Item::DrawRect(itemRect, renderTarget, sf::Color(255, 127, 0));
}

bool BatteringRam::HitWall(const Position& pos, Player& player, World& world)
{
	world.RemoveWallPosition(pos);
	std::cout << player.GetName() << " used a Battering Ram while hitting a wall" << std::endl;
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(PlayView::GetWallColor(), pos)));
	return true;
}

bool BatteringRam::HitSelf(const Position& pos, Player& player, World& world)
{
	player.RemovePosition(pos, world);
	std::cout << player.GetName() << " used a Battering Ram while hitting himself" << std::endl;
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(player.GetColor(), pos)));
	return true;
}

bool BatteringRam::HitOtherPlayer(const Position& pos, Player& player, Player& other, World& world)
{
	std::cout << player.GetName() << " used a Battering Ram while hitting " << other.GetName() << std::endl;
	other.RemovePosition(pos, world);
	Synthesizer::PlaySound("BatteringRam");
	world.AddAnimationPtr(AnimationPtr(new BatteringRamAnimation(other.GetColor(), pos)));
	return true;
}

bool BatteringRam::GetCollected(Player& player, World& world)
{
	world.AddAnimationPtr(
			AnimationPtr(
					new CollectAnimation(sf::Color(255, 127, 0), position_,
							player.GetName() + " collected a " + GetName() + ".")));
	return true;
}

std::string BatteringRam::GetName() const
{
	return "Battering Ram";
}

} /* namespace Dron */

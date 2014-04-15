#include "Player.h"

#include "../Synthesizer.h"
#include "PlayerController.h"
#include "Animations/BatteringRamAnimation.h"

#include <iostream>
#include <cassert>

namespace Dron
{

Player::Player(const std::string& name, const Position& initialPosition, const sf::Color& color,
		const PlayerControllerPtr& controllerPtr, ItemPtrs::size_type maxItems, Positions::size_type minLength) :
		name_(name), positions_(1, initialPosition), color_(color), controllerPtr_(controllerPtr), alive_(true), maxItems_(
				maxItems), minLength_(minLength), shrinkTailStepNum_(0)
{
}

void Player::PushKeyInput(const sf::Key::Code& keyCode)
{
	controllerPtr_->PushKeyInput(keyCode);
}

void Player::PushJoyInput(const sf::Event::JoyMoveEvent& jobMoveEvent)
{
	controllerPtr_->PushJoyInput(jobMoveEvent);
}

const Player::Position& Player::GetFrontPosition() const
{
	assert(!positions_.empty());
	return positions_.front();
}

const Player::Position& Player::GetBackPosition() const
{
	assert(!positions_.empty());
	return positions_.back();
}

void Player::CalculateNextStep(const World& world, ConstPlayerPtrs otherPlayerPtrs)
{
	controllerPtr_->CalculateNextDirection(world, *this, otherPlayerPtrs);
}

void Player::ExecuteNextStep(const World& world)
{
	if (!alive_)
		return;
	Vector nextDirection(controllerPtr_->GetNextDirection());
	World::Position nextPosition(world.NextPosition(GetFrontPosition(), nextDirection));
	if (!positions_.empty() && positions_.front() != nextPosition)
		positions_.push_front(nextPosition);
	lastDirection_ = nextDirection;
	ShrinkTail();
}

const Player::Vector Player::NextPosition(const World& world) const
{
	return world.NextPosition(GetFrontPosition(), controllerPtr_->GetNextDirection());
}

bool Player::RemovePosition(const Position& pos, World& world)
{
	Positions::size_type oldSize(positions_.size());
	positions_.erase(std::remove(std::begin(positions_), std::end(positions_), pos), std::end(positions_));
	if (positions_.empty() && controllerPtr_->GetNextDirection() == Vector())
		Die(pos, world);
	return oldSize != positions_.size();
}

void Player::Die(const Position&, World&)
{
	std::cout << name_ << " died." << std::endl;
	alive_ = false;
	lastDirection_ = Vector();
	itemPtrs_.clear();
	Synthesizer::PlaySound("Die");
}

bool Player::HitItem(const Position&, ItemPtr itemPtr, World& world)
{
	std::cout << name_ << " collected a(n) " << itemPtr->GetName() << "." << std::endl;

	AnimationPtrs newAnimations;
	if (itemPtr->GetUsedImmediately(*this, world))
	{
		world.AddAnimationPtrs(newAnimations);
		Synthesizer::PlaySound("UsedImmediately");
		return true;
	}

	if (itemPtr->GetCollected(*this, world))
		if (itemPtrs_.size() < maxItems_)
			itemPtrs_.push_back(itemPtr);
		else
			std::cout << name_ << " can not hold more Items." << std::endl;
	else
		return false;
	Synthesizer::PlaySound("Collect");
	return true;
}

void Player::HitWall(const Position& pos, World& world)
{
	for (auto it(std::begin(itemPtrs_)); it != std::end(itemPtrs_); ++it)
	{
		if ((*it)->HitWall(pos, *this, world))
		{
			it = itemPtrs_.erase(it);
			return;
		}
	}

	std::cout << name_ << " crashed into a wall." << std::endl;
	Die(pos, world);
}

void Player::HitSelf(const Position& pos, World& world)
{
	for (auto it(std::begin(itemPtrs_)); it != std::end(itemPtrs_); ++it)
	{
		if ((*it)->HitSelf(pos, *this, world))
		{
			it = itemPtrs_.erase(it);
			return;
		}
	}
	std::cout << name_ << " crashed into himself." << std::endl;
	Die(pos, world);
}

void Player::HitOtherPlayer(const Position& pos, Player& other, World& world)
{
	for (auto it(std::begin(itemPtrs_)); it != std::end(itemPtrs_); ++it)
	{
		if ((*it)->HitOtherPlayer(pos, *this, other, world))
		{
			it = itemPtrs_.erase(it);
			return;
		}
	}
	std::cout << name_ << " crashed into " << other.GetName() << "." << std::endl;
	Die(pos, world);
	if (other.GetPositions().size() == 1)
		other.Die(pos, world);
}

void Player::ShrinkTail(std::size_t n)
{
	++shrinkTailStepNum_;
	if (positions_.size() > minLength_ && shrinkTailStepNum_ % n == 0)
		positions_.pop_back();
}

void Player::ShrinkToMinLength()
{
	while (positions_.size() > minLength_)
		positions_.pop_back();
}

} /* namespace Dron */

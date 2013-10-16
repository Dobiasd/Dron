#include "KeyController.h"

#include "../Player.h"

#include <algorithm>

namespace Dron
{

KeyController::KeyController(const std::string& name) :
		PlayerController(name)
{
}

void KeyController::SetDirectionKey(const Vector& direction, sf::Key::Code keyCode)
{
	keysToDirections_.insert(KeysToDirections::value_type(keyCode, direction));
}

void KeyController::PushKeyInput(const sf::Key::Code& keyCode)
{
	auto it(keysToDirections_.find(keyCode));
	if (it == std::end(keysToDirections_))
		return;
	if (!inputDirections_.empty() && inputDirections_.back() == it->second)
		return;
	inputDirections_.push(it->second);
}

void KeyController::CalculateNextDirection(const World&, const Player& player, ConstPlayerPtrs)
{
	if (inputDirections_.empty())
		inputDirections_.push(player.GetLastDirection());
	else if (inputDirections_.front() + player.GetLastDirection() == Vector())
		nextDirection_ = player.GetLastDirection();
	else
		nextDirection_ = inputDirections_.front();
	inputDirections_.pop();
}

} /* namespace Dron */

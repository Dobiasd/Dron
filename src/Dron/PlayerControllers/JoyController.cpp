#include "JoyController.h"

#include "../Player.h"

#include <algorithm>

namespace Dron
{

JoyController::JoyController(const std::string& name, unsigned int joyId) :
		PlayerController(name), joyId_(joyId)
{
}

void JoyController::PushDirectionIfNew(const Vector& direction)
{
	if (!inputDirections_.empty() && inputDirections_.front() == direction)
		return;
	inputDirections_.push(direction);
}

void JoyController::PushJoyInput(const sf::Event::JoyMoveEvent& joyMoveEvent)
{
	if (joyMoveEvent.JoystickId != joyId_)
		return;
	if (joyMoveEvent.Axis == sf::Joy::AxisX && joyMoveEvent.Position < 0.f)
		PushDirectionIfNew(Vector(-1, 0));
	if (joyMoveEvent.Axis == sf::Joy::AxisX && joyMoveEvent.Position > 0.f)
		PushDirectionIfNew(Vector(1, 0));
	if (joyMoveEvent.Axis == sf::Joy::AxisY && joyMoveEvent.Position < 0.f)
		PushDirectionIfNew(Vector(0, -1));
	if (joyMoveEvent.Axis == sf::Joy::AxisY && joyMoveEvent.Position > 0.f)
		PushDirectionIfNew(Vector(0, 1));
}

void JoyController::CalculateNextDirection(const World&, const Player& player, ConstPlayerPtrs)
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

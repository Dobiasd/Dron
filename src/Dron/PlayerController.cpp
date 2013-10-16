#include "PlayerController.h"

namespace Dron
{

// Initialize nextDirection_ to make sure nobody just stands around after the game starts.
PlayerController::PlayerController(const std::string& name) :
		name_(name), nextDirection_(0, 1)
{
}

} /* namespace Dron */

#include "PlayerMover.h"

namespace Dron
{

void PlayerMover::Control(PlayModel& model, Play&) const
{
	PlayerPtrs alivePlayers(model.GetAlivePlayers());
	std::for_each(std::begin(alivePlayers), std::end(alivePlayers), [&](PlayerPtr playerPtr)
	{
		playerPtr->ExecuteNextStep(model.world_);
	});
}

} /* namespace Dron */

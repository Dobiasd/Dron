#include "PlayersCollisionChecker.h"

namespace Dron
{

void PlayersCollisionChecker::Control(PlayModel& model, Play&) const
{
	// Helper function: Checks if one player will hit another.
	auto CheckForPlayerHit = [&](PlayerPtr hitterPtr, PlayerPtr hitteePtr)
	{
		// Will the heads of both players be at the same spot after this step?
			if (hitterPtr != hitteePtr && hitterPtr->IsAlive() && hitteePtr->IsAlive() &&
					hitterPtr->NextPosition(model.world_) == hitteePtr->NextPosition(model.world_))
			{
				hitterPtr->HitOtherPlayer(hitterPtr->NextPosition(model.world_), *hitteePtr, model.world_);
				hitteePtr->HitOtherPlayer(hitteePtr->NextPosition(model.world_), *hitterPtr, model.world_);
				return;
			}
			// Does the possible hitter crash into already existing elements of the potential hittee?
			const Player::Positions& positions(hitteePtr->GetPositions());
			for (auto posIt(std::begin(positions)); posIt != std::end(positions); ++posIt)
			{
				if (hitterPtr->NextPosition(model.world_) != hitterPtr->GetFrontPosition() &&
						hitterPtr->NextPosition(model.world_) == *posIt)
				{
					if (hitterPtr == hitteePtr)
					{
						hitterPtr->HitSelf(hitterPtr->NextPosition(model.world_), model.world_);
						break;
					}
					hitterPtr->HitOtherPlayer(hitterPtr->NextPosition(model.world_), *hitteePtr, model.world_);
					break;
				}
			}
		};

	std::for_each(std::begin(model.playerPtrs_), std::end(model.playerPtrs_), [&](PlayerPtr playerPtr)
	{
		if (playerPtr->IsAlive())
		{
			const World::Position& nextPos(playerPtr->NextPosition(model.world_));
			World::Positions wallPositions(model.world_.GetWallPositions());
			if (std::find(std::begin(wallPositions), std::end(wallPositions), nextPos) != std::end(wallPositions))
			playerPtr->HitWall(nextPos, model.world_);
			std::for_each(std::begin(model.playerPtrs_), std::end(model.playerPtrs_),
					[&](PlayerPtr otherPlayerPtr)
					{
						CheckForPlayerHit(playerPtr, otherPlayerPtr);
					}
			);
		}
	});
}

} /* namespace Dron */

#include "ItemCollectionChecker.h"

namespace Dron
{

void ItemCollectionChecker::Control(PlayModel& model, Play&) const
{
	PlayerPtrs alivePlayers(model.GetAlivePlayers());
	ItemPtrs& itemPtrs(model.world_.GetItemPtrs());
	std::for_each(std::begin(alivePlayers), std::end(alivePlayers), [&](PlayerPtr playerPtr)
	{
		auto itItemPtr(std::begin(itemPtrs));
		const World::Position& nextPos(playerPtr->NextPosition(model.world_));
		while (itItemPtr != std::end(itemPtrs))
		{
			if (nextPos == (*itItemPtr)->GetPosition() && playerPtr->HitItem(nextPos, *itItemPtr, model.world_))
			{
				itItemPtr = itemPtrs.erase(itItemPtr);
				continue;
			}
			if (itItemPtr != std::end(itemPtrs))
			++itItemPtr;
		}
	});
}

} /* namespace Dron */

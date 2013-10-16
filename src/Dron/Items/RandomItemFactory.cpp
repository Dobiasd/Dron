#include "RandomItemFactory.h"
#include "BatteringRam.h"
#include "Abridger.h"
#include "Fragmenter.h"

#include "../GameStates/PlayModel.h"

namespace Dron
{
RandomItemFactory::RandomItemFactory() :
		randomGenerator_(randomDevice_()), randomIntDistributionType_(0, 3)
{
}

RandomItemFactory::ItemPtr RandomItemFactory::Create(const World& world, ConstPlayerPtrs playerPtrs) const
{
	World::Positions freePositions(world.GetFreePositions(playerPtrs));

	if (freePositions.empty())
		return ItemPtr();

	std::uniform_int_distribution<> randomIntDistributionPos(0, freePositions.size() - 1);
	World::Position pos(freePositions[randomIntDistributionPos(randomGenerator_)]);

	// Battering Rams are two times more likely than Abridgers.
	int randomNumber(randomIntDistributionType_(randomGenerator_));
	if (randomNumber == 0)
		return ItemPtr(new Abridger(pos, world.GetWidth() + world.GetHeight()));
	if (randomNumber == 1)
		return ItemPtr(new Fragmenter(pos, world.GetWidth() + world.GetHeight()));
	return ItemPtr(new BatteringRam(pos, world.GetWidth() + world.GetHeight()));
}

} /* namespace Dron */

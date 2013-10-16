#include "NewItemPlacer.h"

#include "../../Items/RandomItemFactory.h"

namespace Dron
{

NewItemPlacer::NewItemPlacer(double newItemProbability) :
		newItemProbability_(newItemProbability), randomGenerator_(randomDevice_()), randomDoubleDistribution_(0., 1.)
{
}

void NewItemPlacer::Control(PlayModel& model, Play&) const
{
	if (randomDoubleDistribution_(randomGenerator_) < newItemProbability_)
	{
		ItemPtr newItemPtr(
				RandomItemFactory::Instance().Create(model.world_,
						ConstPlayerPtrs(std::begin(model.playerPtrs_), std::end(model.playerPtrs_))));
		if (newItemPtr)
			model.world_.InsertItem(newItemPtr);
	}
}

} /* namespace Dron */

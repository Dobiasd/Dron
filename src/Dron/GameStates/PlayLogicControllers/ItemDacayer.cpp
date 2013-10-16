#include "ItemDacayer.h"

namespace Dron
{

void ItemDacayer::Control(PlayModel& model, Play&) const
{
	ItemPtrs& itemPtrs(model.world_.GetItemPtrs());
	for (auto it(std::begin(itemPtrs)); it != std::end(itemPtrs);)
	{
		(*it)->Decay();
		if ((*it)->IsDecayed())
			it = itemPtrs.erase(it);
		else
			++it;
	}
}

} /* namespace Dron */

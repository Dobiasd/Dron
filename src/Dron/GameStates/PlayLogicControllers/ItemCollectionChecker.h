#ifndef ITEMCOLLECTIONCHECKER_H_
#define ITEMCOLLECTIONCHECKER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Check if players collect items.
 */
class ItemCollectionChecker: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* ITEMCOLLECTIONCHECKER_H_ */

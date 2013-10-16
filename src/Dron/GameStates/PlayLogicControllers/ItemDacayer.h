#ifndef ITEMDECAYER_H_
#define ITEMDECAYER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Let Items decay.
 */
class ItemDacayer: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* ITEMDECAYER_H_ */

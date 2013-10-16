#ifndef PLAYERMOVER_H_
#define PLAYERMOVER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Move Players one step.
 */
class PlayerMover: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* PLAYERMOVER_H_ */

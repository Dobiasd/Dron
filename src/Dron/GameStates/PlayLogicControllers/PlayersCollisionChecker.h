#ifndef PLAYERSCOLLISIONCHECKER_H_
#define PLAYERSCOLLISIONCHECKER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Check if one player hits another.
 */
class PlayersCollisionChecker: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* PLAYERSCOLLISIONCHECKER_H_ */

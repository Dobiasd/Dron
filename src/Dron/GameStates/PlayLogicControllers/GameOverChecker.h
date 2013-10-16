#ifndef GAMEOVERCHECKER_H_
#define GAMEOVERCHECKER_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Did somebody win or was there even a draw?
 */
class GameOverChecker: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* GAMEOVERCHECKER_H_ */

#ifndef PLAYERSNEXTPOSITIONSCALCULATOR_H_
#define PLAYERSNEXTPOSITIONSCALCULATOR_H_

#include "../PlayLogicController.h"

namespace Dron
{

/*
 * Precalculate where the players would be after this time step.
 */
class PlayersNextPositionsCalculator: public Dron::PlayLogicController
{
public:
	virtual void Control(PlayModel& model, Play& play) const
	override;
};

} /* namespace Dron */

#endif /* PLAYERSNEXTPOSITIONSCALCULATOR_H_ */

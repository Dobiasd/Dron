#ifndef NEWITEMPLACER_H_
#define NEWITEMPLACER_H_

#include "../PlayLogicController.h"

#include <random>

namespace Dron
{

/*
 * Randomly places new items.
 */
class NewItemPlacer: public Dron::PlayLogicController
{
public:
	NewItemPlacer(double newItemProbability);
	virtual void Control(PlayModel& model, Play& play) const
	override;
private:
	double newItemProbability_;
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_real_distribution<> randomDoubleDistribution_;
};

} /* namespace Dron */

#endif /* NEWITEMPLACER_H_ */

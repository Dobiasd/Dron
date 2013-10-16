#ifndef DRON_AICONTROLLER_H_
#define DRON_AICONTROLLER_H_

#include "../PlayerController.h"

#include <random>
#include <memory>

namespace Dron
{

/*
 * An "Artificial intelligence" tron player
 * It just runs around, avoids walls, collects items if next to them,
 * and sometimes randomly changes its direction.
 */
class AIController: public PlayerController
{
public:
	AIController(const std::string& name, double randomness);
	virtual void PushKeyInput(const sf::Key::Code&) override
	{}
	virtual void CalculateNextDirection(const World& world, const Player& Player, ConstPlayerPtrs otherPlayerPtrs)
	override;
	typedef std::vector<Vector> Directions;
	typedef Vector2D<int> Vector;
protected:
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_real_distribution<> randomDoubleDistribution_;
	Directions possibleDirections_;
	double randomness_;
};

typedef std::shared_ptr<AIController> AIControllerPtr;
typedef std::shared_ptr<const AIController> ConstAIControllerPtr;

} /* namespace Dron */

#endif /* DRON_AICONTROLLER_H_ */

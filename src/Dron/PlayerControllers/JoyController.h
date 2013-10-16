#ifndef DRON_JOYCONTROLLER_H_
#define DRON_JOYCONTROLLER_H_

#include "../PlayerController.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <queue>
#include <memory>

namespace Dron
{

/*
 * Simple joypad controller for a tron player
 * Inputs are stacked to make the timing for quick turns easier to get.
 */
class JoyController: public PlayerController
{
public:
	JoyController(const std::string& name, unsigned int joyId);
	virtual void PushJoyInput(const sf::Event::JoyMoveEvent& joyMoveEvent)
	override;
	virtual void CalculateNextDirection(const World& world, const Player&, ConstPlayerPtrs otherPlayerPtrs)
	override;
protected:
	void PushDirectionIfNew(const Vector& direction);
	typedef std::queue<Vector> DirectionsQueue;
	DirectionsQueue inputDirections_;
	unsigned int joyId_;
};

typedef std::shared_ptr<JoyController> JoyControllerPtr;
typedef std::shared_ptr<const JoyController> ConstJoyControllerPtr;

} /* namespace Dron */

#endif /* DRON_JOYCONTROLLER_H_ */

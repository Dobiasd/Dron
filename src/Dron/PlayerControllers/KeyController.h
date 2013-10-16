#ifndef DRON_KEYCONTROLLER_H_
#define DRON_KEYCONTROLLER_H_

#include "../PlayerController.h"

#include <SFML/Window/Event.hpp>

#include <map>
#include <queue>
#include <memory>

namespace Dron
{

/*
 * Simple keyboard controller for a tron player
 * Inputs are stacked to make the timing for quick turns easier to get.
 */
class KeyController: public PlayerController
{
public:
	KeyController(const std::string& name);
	virtual void SetDirectionKey(const Vector& direction, sf::Key::Code keyCode);
	virtual void PushKeyInput(const sf::Key::Code& keyCode)
	override;
	virtual void CalculateNextDirection(const World& world, const Player&, ConstPlayerPtrs otherPlayerPtrs)
	override;
protected:
	typedef std::queue<Vector> DirectionsQueue;
	typedef std::map<sf::Key::Code, Vector> KeysToDirections;
	KeysToDirections keysToDirections_;
	DirectionsQueue inputDirections_;
};

typedef std::shared_ptr<KeyController> KeyControllerPtr;
typedef std::shared_ptr<const KeyController> ConstKeyControllerPtr;

} /* namespace Dron */

#endif /* DRON_KEYCONTROLLER_H_ */

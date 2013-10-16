#ifndef DRON_PLAYLOGICCONTROLLER_H_
#define DRON_PLAYLOGICCONTROLLER_H_

#include "PlayModel.h"

#include <memory>
#include <vector>

namespace sf
{
class Event;
}

namespace Dron
{

/*
 * Abstract base class for implementing different aspects of the game logic
 */
class PlayLogicController
{
public:
	virtual ~PlayLogicController()
	{
	}
	virtual void Control(PlayModel& model, Play& play) const = 0;
};

typedef std::shared_ptr<PlayLogicController> PlayLogicControllerPtr;
typedef std::vector<PlayLogicControllerPtr> PlayLogicControllerPtrs;

} /* namespace Dron */

#endif /* DRON_PLAYLOGICCONTROLLER_H_ */

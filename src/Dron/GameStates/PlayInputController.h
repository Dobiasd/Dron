#ifndef DRON_PLAYINPUTCONTROLLER_H_
#define DRON_PLAYINPUTCONTROLLER_H_

#include "PlayModel.h"

namespace sf
{
class Event;
}

namespace Dron
{

class Play;

/*
 * Forwards input events to the individual controllers of the players in the model.
 */
class PlayInputController
{
public:
	PlayInputController(PlayModel& model);
	bool ProcessEvent(const sf::Event& event, Play& play);
private:
	PlayModel& model_;
};

} /* namespace Dron */

#endif /* DRON_PLAYINPUTCONTROLLER_H_ */

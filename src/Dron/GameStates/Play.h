#ifndef PLAY_H_
#define PLAY_H_

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayInputController.h"
#include "PlayLogicController.h"

#include "../../GameState.h"

namespace Dron
{

class Player;

/*
 * The in-game state. Calls are delegated to the individual MVC components.
 * The controller changes the model and the view displays it.
 */
class Play: public GameState
{
public:
	Play(const World& world, PlayerPtrs playerPtrs, float stepsPerSecond, double newItemProbability,
			int blurAmount = 7);
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
	float stepsPerSecond_;
protected:
	typedef Vector2D<int> Vector;
	typedef Vector Position;
	typedef std::vector<Position> Positions;
	PlayModel model_;
	PlayView view_;
	PlayInputController inputController_;
	PlayLogicControllerPtrs logicControllerPtrs_;
	bool paused_;
	float elapsedTimeSinceLastStep_;
	std::size_t stepNum_;
};

} /* namespace Dron */

#endif /* PLAY_H_ */

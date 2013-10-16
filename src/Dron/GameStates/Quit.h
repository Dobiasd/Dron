#ifndef QUIT_H_
#define QUIT_H_

#include "../../GameState.h"

/*
 * Closes the window and thus signalizes the game class that it has come to its end.
 *
 * Model, View and Controller are joined because of their simplicity.
 */
class Quit: public GameState
{
public:
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
};

#endif /* QUIT_H_ */

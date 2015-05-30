#ifndef SHOWTEXTANDWAIT_H_
#define SHOWTEXTANDWAIT_H_

#include "../../GameState.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Dron
{

/*
 * Shows some text on the screen and waits for keyboard input.
 *
 * Model, View and Controller are joined because of their simplicity.
 */
class ShowTextAndWait: public GameState
{
public:
	ShowTextAndWait(const std::string& text, const sf::Color& color, const GameStatePtr& nextStatePtr, float waitTime =
			1.f, const sf::Image& backgroundImage = sf::Image());
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
private:
	std::string text_;
	sf::Color color_;
	GameStatePtr nextStatePtr_;
	float elapsedTimeSum_;
	float waitTime_;
	sf::Image backgroundImage_;
};

} /* namespace Dron */

#endif /* SHOWTEXTANDWAIT_H_ */

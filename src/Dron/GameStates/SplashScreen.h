#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_

#include "../../GameState.h"

#include <string>

namespace Dron
{

/*
 * Generates the in game sounds and gives a random tip while showing.
 *
 * Model, View and Controller are joined because of their simplicity.
 */
class SplashScreen: public GameState
{
public:
	SplashScreen(const std::string& title);
	virtual bool ProcessEvent(const sf::Event& event)
	override;
	virtual bool Update(float elapsedTime)
	override;
	virtual bool Display(sf::RenderTarget& renderTarget) const
	override;
private:
	std::string title_;
	bool firstFrame_;
	std::string tip_;
};

} /* namespace Dron */

#endif /* SPLASHSCREEN_H_ */

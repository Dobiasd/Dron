#ifndef GAME_H_
#define GAME_H_

#include "GameState.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <memory>

/*
 * Abstract base class for a game using SMFL
 *
 * It Provides InitSounds() for later use (supposedly in some kind of splash screen).
 * A double click into the window switched back and forth
 * between windowed mode and fullscreen.
 */
class Game
{
public:
	virtual ~Game()
	{
	}

	// Start the game.
	virtual bool Run();

	virtual void InitSounds() = 0;

	virtual sf::Image CaptureScreen() const;

protected:
	// Every game has to have a name.
	virtual std::string GetName() = 0;
	virtual bool Init() = 0;
	typedef std::unique_ptr<sf::RenderWindow> WindowPtr;
	WindowPtr windowPtr_;
	GameStatePtr gameStatePtr_;
	sf::View view_;
	bool fullScreen_;
};

#endif /* GAME_H_ */

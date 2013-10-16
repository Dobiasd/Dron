#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "../Vector2D.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <memory>

/*
 * Abstract base class for menu items.
 */
class MenuItem
{
public:
	typedef Vector2D<int> Position;

	// Every Item has to process keyboard inputs in some way.
	virtual void ProcessKey(const sf::Key::Code& keyCode) = 0;

	// Show the item a a given position.
	virtual void Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
			float height) const = 0;
};

typedef std::shared_ptr<MenuItem> MenuItemPtr;

#endif /* MENUITEM_H_ */

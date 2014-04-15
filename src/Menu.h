#ifndef MENU_H_
#define MENU_H_

#include "MenuItems/MenuItem.h"

#include <memory>
#include <vector>

/*
 * A basic menu operated with the arrow keys (or wasd) and enter.
 * The following keys are also supported: home, end, page up, page down
 */
class Menu
{
public:
	virtual void ProcessKeyCode(const sf::Key::Code&);
	virtual void Display(sf::RenderTarget& renderTarget) const;
	void AddMenuItem(const MenuItemPtr& ptr)
	{
		menuItemsPtrs_.push_back(ptr);
		itMenu = std::begin(menuItemsPtrs_);
	}

private:
	typedef std::vector<MenuItemPtr> MenuItemPtrs;
	MenuItemPtrs menuItemsPtrs_;
	MenuItemPtrs::const_iterator itMenu;
};

#endif /* MENU_H_ */

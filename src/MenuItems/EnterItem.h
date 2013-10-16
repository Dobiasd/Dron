#ifndef ENTERITEM_H_
#define ENTERITEM_H_

#include "MenuItem.h"

#include <functional>

/*
 * An item in a menu whose callback function can be invoked with the enter key
 */
class EnterItem: public MenuItem
{
public:
	typedef std::function<void(void)> Callback;
	EnterItem(const std::string& label, const Callback& callback);
	virtual void ProcessKey(const sf::Key::Code& keyCode)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
			float height) const
	override;
protected:
	std::string label_;
	Callback callback_;
};

#endif /* ENTERITEM_H_ */

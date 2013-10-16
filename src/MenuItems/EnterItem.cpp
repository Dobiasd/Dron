#include "EnterItem.h"

#include <SFML/Graphics/String.hpp>

EnterItem::EnterItem(const std::string& label, const Callback& callback) :
		label_(label), callback_(callback)
{
}

void EnterItem::Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color, float height) const
{
	sf::String sfText(label_);
	sfText.SetSize(height);
	sfText.SetColor(color);
	sfText.Move(static_cast<float>(pos.x_), static_cast<float>(pos.y_));
	renderTarget.Draw(sfText);
}

void EnterItem::ProcessKey(const sf::Key::Code& keyCode)
{
	if (keyCode == sf::Key::Return || keyCode == sf::Key::Space)
		callback_();
}

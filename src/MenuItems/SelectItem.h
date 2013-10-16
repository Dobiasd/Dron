/*
 * Dron (Dobi's Tron/Snake game)
 * Copyright (C) 2012 Tobias Hermann

 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SELECTITEM_H_
#define SELECTITEM_H_

#include "MenuItem.h"

#include "../Synthesizer.h"

#include <SFML/Graphics/String.hpp>

#include <memory>
#include <functional>
#include <string>

/*
 * An item in a menu that provides different choices selectable with the left, right or w, s.
 * A callback function can optionally be invoked with every change.
 *
 * As template parameter it takes the type of the container holding the possible choices.
 */
template<typename T>
class SelectItem: public MenuItem
{
public:
	typedef std::function<void(void)> Callback;
	SelectItem(const std::string& label, const T& variants, typename T::size_type start = 0, const Callback& callback =
			Callback());
	virtual void
	ProcessKey(const sf::Key::Code& keyCode)
	override;
	virtual void Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
			float height) const
	override;

	// Return the currently selected choice.
	const typename T::value_type& Get()
	{
		return *it_;
	}
	const std::string& GetLabel() const
	{
		return label_;
	}
	typedef typename T::size_type size_type;

	// Return the position of the current selection.
	typename T::size_type GetPos() const
	{
		return std::distance(std::begin(variants_), it_);
	}

	// Set the current selection to a specific position.
	void SetPos(typename T::size_type index)
	{
		it_ = std::begin(variants_) + std::min(index, variants_.size() - 1);
	}

protected:
	std::string label_;

	// Storage for the selectable item
	T variants_;

	// The current position
	typename T::const_iterator it_;

	// Will be invoked every time the selection is changed
	Callback callback_;
};

template<typename T>
SelectItem<T>::SelectItem(const std::string& label, const T& variants, typename T::size_type start,
		const Callback& callback) :
		label_(label), variants_(variants), it_(std::begin(variants_) + start), callback_(callback)
{
}

template<typename T>
void SelectItem<T>::ProcessKey(const sf::Key::Code& keyCode)
{
	if (keyCode == sf::Key::Right || keyCode == sf::Key::D)
	{
		if (it_ != std::end(variants_) - 1)
		{
			++it_;
			if (callback_)
				callback_();
			Synthesizer::PlaySound("MenuHorizontal");
		}
		else
		{
			Synthesizer::PlaySound("MenuHorizontalBump");
		}
	}
	else if (keyCode == sf::Key::Left || keyCode == sf::Key::A)
	{
		if (it_ != std::begin(variants_))
		{
			--it_;
			if (callback_)
				callback_();
			Synthesizer::PlaySound("MenuHorizontal");
		}
		else
		{
			Synthesizer::PlaySound("MenuHorizontalBump");
		}
	}
}

template<typename T>
std::string ToString(T val)
{
	std::ostringstream str;
	str << val;
	return str.str();
}

// Overloading for the case that the Items are shared_ptrs.
// In that case the type pointed to has to provide a member function GetName().
template<typename T>
std::string ToString(const std::shared_ptr<T>& ptr)
{
	if (!ptr)
		return "none";
	return ptr->GetName();
}

template<typename T>
void SelectItem<T>::Display(sf::RenderTarget& renderTarget, const Position& pos, const sf::Color& color,
		float height) const
{
	std::string text(label_);

	text += ": ";
	text += it_ != std::begin(variants_) ? "<-- " : "    ";
	text += ToString(*it_);
	text += it_ != std::end(variants_) - 1 ? " -->" : "";

	sf::String sfText(text);
	sfText.SetSize(height);
	sfText.SetColor(color);
	sfText.Move(static_cast<float>(pos.x_), static_cast<float>(pos.y_));
	renderTarget.Draw(sfText);
}

#endif /* SELECTITEM_H_ */

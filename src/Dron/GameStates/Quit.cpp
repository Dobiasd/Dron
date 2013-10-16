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

#include "Quit.h"

#include <iostream>

bool Quit::ProcessEvent(const sf::Event&)
{
	return true;
}

bool Quit::Update(float)
{
	quit_ = true;
	return true;
}

bool Quit::Display(sf::RenderTarget& renderTarget) const
{
	std::cout << "Quit." << std::endl;
	return true;
}

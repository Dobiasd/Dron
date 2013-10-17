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

bool Quit::Display(sf::RenderTarget&) const
{
	std::cout << "Quit." << std::endl;
	return true;
}

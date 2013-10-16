#include "Game.h"
#include "Synthesizer.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

void Game::InitSounds()
{
	// Generate default sounds for the menu.
	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Triangle(Synthesizer::FreqFromNote("E", 5)), 0.04, 0.06, 0.4, 0.09),
			"MenuHorizontal");
	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Sawtooth(Synthesizer::FreqFromNote("D", 3)), 0.04, 0.06, 0.4, 0.09),
			"MenuHorizontalBump");
	Synthesizer::KeepSound(Synthesizer::ADSR(Synthesizer::Sine(Synthesizer::FreqFromNote()), 0.04, 0.06, 0.4, 0.09),
			"MenuVertical");
	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Square(Synthesizer::FreqFromNote("D", 3)), 0.04, 0.06, 0.4, 0.09),
			"MenuVerticalBump");
}

sf::Image Game::CaptureScreen() const
{
	if (!windowPtr_)
	{
		throw(std::logic_error("No Screen to capture."));
	}
	return windowPtr_->Capture();
}

bool Game::Run()
{
	if (!Init())
		return false;

	std::string windowTitle(GetName() + " - double click window to enter full screen mode");

	windowPtr_ = WindowPtr(
			new sf::RenderWindow(sf::VideoMode(1024, 640, 32), windowTitle,
					sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar, sf::WindowSettings(32, 8, 8)));
	fullScreen_ = false;
	windowPtr_->UseVerticalSync(true);

	if (!windowPtr_ || !gameStatePtr_)
		return false;

	view_ = windowPtr_->GetView();

	std::cout << GetName() << " started." << std::endl;

	// To measure the time between two frames
	sf::Clock frameClock;

	// To time FPS display moments.
	sf::Clock oneSecClock;

	// To measure the time between two clicks
	sf::Clock doubleClickClock;

	std::string fpsString;

	while (windowPtr_->IsOpened())
	{
		// Adjust the view size to the possibly resized window.
		float width(windowPtr_->GetView().GetRect().GetWidth());
		float height(windowPtr_->GetView().GetRect().GetHeight());
		windowPtr_->SetView(sf::View(sf::FloatRect(0, 0, width, height)));

		// Time since last frame.
		float elapsedTime = frameClock.GetElapsedTime();
		frameClock.Reset();

		// Dispatch single events to the actual game state.
		sf::Event event;
		while (windowPtr_->GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
				windowPtr_->Close();
			if (event.Type == sf::Event::MouseButtonPressed)
			{
				if (doubleClickClock.GetElapsedTime() < 0.5)
				{
					if (!fullScreen_)
					{
						std::cout << "Switching to fullscreen." << std::endl;
						windowPtr_ = WindowPtr(
								new sf::RenderWindow(sf::VideoMode::GetMode(0), GetName(),
										sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar
												| sf::Style::Fullscreen, sf::WindowSettings(32, 8, 8)));
						windowPtr_->UseVerticalSync(true);
						fullScreen_ = true;
					}
					else
					{
						std::cout << "Switching to windowed mode." << std::endl;
						windowPtr_ = WindowPtr(
								new sf::RenderWindow(sf::VideoMode(1024, 640, 32), windowTitle,
										sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar,
										sf::WindowSettings(32, 8, 8)));
						windowPtr_->UseVerticalSync(true);
						fullScreen_ = false;
					}

				}
				doubleClickClock.Reset();
			}
			if (event.Type == sf::Event::Resized)
			{
				// Resize our view with the window,
				// so the views can render pixelwise,
				// with the new resolution.
				width = static_cast<float>(windowPtr_->GetWidth());
				height = static_cast<float>(windowPtr_->GetHeight());
				windowPtr_->SetView(view_ = sf::View(sf::FloatRect(0.f, 0.f, width, height)));
			}

			gameStatePtr_->ProcessEvent(event);
		}

		// Let the model do its work.
		gameStatePtr_->Update(elapsedTime);

		// Model to the screen
		gameStatePtr_->Display(*windowPtr_);

		// Display frames per second
		std::ostringstream str;

		if (oneSecClock.GetElapsedTime() > 1.f)
		{
			oneSecClock.Reset();
			int fps(static_cast<int>(1.f / elapsedTime));
			str << fps;
			fpsString = str.str();
		}
		sf::String sfTextFPS(std::string("FPS: ") + fpsString, sf::Font::GetDefaultFont(), 16.f);
		sfTextFPS.SetColor(sf::Color(92, 92, 92));
		sfTextFPS.Move(view_.GetRect().GetWidth() - (sfTextFPS.GetRect().GetWidth() + 2), 0.f), windowPtr_->Draw(
				sfTextFPS);

		windowPtr_->Display();

		// Did the actual game state put another state in charge?
		if (gameStatePtr_->IsDone())
		{
			std::cout << "Game state changed." << std::endl;
			gameStatePtr_ = gameStatePtr_->GetNextState();
		}

		// Bye?
		if (gameStatePtr_->GameQuitted())
		{
			windowPtr_->Close();
		}
	}
	return true;
}

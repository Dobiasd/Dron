#include "DronGame.h"

#include "GameStates/SplashScreen.h"
#include "../Synthesizer.h"

#include <iostream>

namespace Dron
{

DronGame::DronGame() :
		soundsInitialized_(false)
{
}

std::string DronGame::GetName()
{
	static std::string name("Dron (Dobi's Tron/Snake game) - " + std::string(__DATE__));
	return name;
}

void DronGame::InitSounds()
{
	Game::InitSounds();

	// Generate Dron specific sounds.

	// The battering ram sound:
	// Random noise is multiplied with a slow sine to create a tremolo like effekt.
	// After removing the high frequencies with a low pass filter
	// it is then stuffed into a fade out ADSR envelope and normalized.
	Synthesizer::KeepSound(
			Synthesizer::Normalize(
					Synthesizer::ADSR(
							Synthesizer::LowPass(Synthesizer::Multiply(Synthesizer::Sine(24), Synthesizer::Noise()),
									0.4, 0.2), .0001, .23, .0, .0)), "BatteringRam");

	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Triangle(Synthesizer::FreqFromNote("G", 4)), .01, .08, .7, .02), "Collect");
	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Triangle(Synthesizer::FreqFromNote("D", 4)), .01, .08, .7, .02),
			"UsedImmediately");
	Synthesizer::KeepSound(Synthesizer::ADSR(Synthesizer::Noise(), .0001, .5, .0, .0), "Die");
	Synthesizer::KeepSound(
			Synthesizer::Append(
					Synthesizer::ADSR(Synthesizer::Sine(Synthesizer::FreqFromNote("E", 4)), .01, .28, .7, .02),
					Synthesizer::ADSR(Synthesizer::Sine(Synthesizer::FreqFromNote("G", 4)), .01, .78, .7, .02)), "Win");
	Synthesizer::KeepSound(
			Synthesizer::ADSR(Synthesizer::Sawtooth(Synthesizer::FreqFromNote("C", 4)), .04, .05, .0, .0), "NewItem");
	Synthesizer::KeepSound(Synthesizer::ADSR(Synthesizer::Square(Synthesizer::FreqFromNote("F", 3)), .1, .3, .7, .1),
			"Draw");
	Synthesizer::KeepSound(Synthesizer::ADSR(Synthesizer::Square(Synthesizer::FreqFromNote("E", 2)), .01, .14, .0, .0),
			"ItemDecayed");

	Synthesizer::KeepSound(
			Synthesizer::ADSR(
					Synthesizer::Multiply(Synthesizer::Square(Synthesizer::FreqFromNote("C", 2)),
							Synthesizer::Sine(6., 1.)), .01, .4, .5, .1), "Pause");

	soundsInitialized_ = true;
}

bool DronGame::Init()
{
	gameStatePtr_ = GameStatePtr(new SplashScreen(GetName()));
	std::cout << GetName() << " initialized." << std::endl;
	return true;
}

} /* namespace Dron */

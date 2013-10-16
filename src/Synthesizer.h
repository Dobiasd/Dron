#ifndef SYNTHESIZER_H_
#define SYNTHESIZER_H_

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>

/*
 * Collection of Functions to create and play sounds
 */

namespace Synthesizer
{
typedef double Value;
typedef std::vector<Value> Signal1D;
typedef std::vector<Signal1D> Signal2D;

// Random Noise
Signal1D Noise(double length = 1., double sampleRate = 44100);

// Various signal generators
Signal1D Sine(double freq = 440., double length = 1., double amp = 1., double sampleRate = 44100);
Signal1D Square(double freq = 440., double length = 1., double amp = 1., double sampleRate = 44100);
Signal1D Triangle(double freq = 440., double length = 1., double amp = 1., double sampleRate = 44100);
Signal1D Sawtooth(double freq = 440., double length = 1., double amp = 1., double sampleRate = 44100);

// Operations on signals
Signal1D Multiply(const Signal1D& signal, const Value& factor);
Signal1D Multiply(const Signal1D& lhs, const Signal1D& rhs);
Signal1D Add(const Signal1D& lhs, const Signal1D& rhs);
Signal1D Append(const Signal1D& lhs, const Signal1D& rhs);

// Force Signal to stay in [-1,1]
Signal1D Normalize(const Signal1D& signal);

// Low-pass filter taking a time interval (dt) and a time constant (rc)
Signal1D LowPass(const Signal1D& signal, double dt, double rc);

// Multiply signal with an Attack-Decay-Sustain-Release-envelope
Signal1D ADSR(const Signal1D& in, double attackTime, double decayTime, double sustainLevel, double releaseTime,
		double sustainTime = .0, double sampleRate = 44100.);

// Translate a musical note to its corresponding frequency
double FreqFromNote(const std::string& name = "A", int octave = 4);

// Format so store sounds
typedef std::shared_ptr<sf::Sound> SFSoundPtr;
typedef std::shared_ptr<sf::SoundBuffer> SFSoundBufferPtr;
typedef std::pair<SFSoundPtr, SFSoundBufferPtr> SFSoundPtrWithSoundBufferPtr;

// Keep a generated sound in memory assiciated with a name
void KeepSound(const SFSoundPtrWithSoundBufferPtr soundPtrWithSoundBufferPtr, const std::string name);
void KeepSound(const Signal1D& signal, const std::string name);

// Play sound previously put in memory with KeepSound by its name. Return immediatly.
bool PlaySound(const std::string name);
void PlaySound(const SFSoundPtrWithSoundBufferPtr soundPtrWithSoundBufferPtr);
SFSoundPtrWithSoundBufferPtr ToSFSound(const Signal1D& signal);

// Disable/Enable PlaySound
void Mute(bool off);

} /* namespace Synthesizer */

#endif /* SYNTHESIZER_H_ */

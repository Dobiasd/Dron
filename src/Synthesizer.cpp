#include "Synthesizer.h"

#include "Pi.h"

#include <stdexcept>
#include <algorithm>
#include <cmath>

#include <iostream>
#include <random>
#include <limits>
#include <iterator>

namespace Synthesizer
{

typedef std::map<std::string, int> NoteNamesToNumbers;
typedef std::map<std::string, SFSoundPtrWithSoundBufferPtr> SoundMap;

NoteNamesToNumbers InitNoteNamesToNumbers()
{
	NoteNamesToNumbers noteNamesToNumbers;
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("A", 9));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("A#", 10));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("Bb", 10));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("B", 11));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("C", 0));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("C#", 1));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("Db", 1));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("D", 2));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("D#", 3));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("Eb", 3));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("E", 4));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("F", 5));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("F#", 6));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("Gb", 6));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("G", 7));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("G#", 8));
	noteNamesToNumbers.insert(NoteNamesToNumbers::value_type("Ab", 8));
	return noteNamesToNumbers;
}

namespace
{
NoteNamesToNumbers noteNamesToNumbers = InitNoteNamesToNumbers();
}

double FreqFromNote(const std::string& name, int octave)
{
	auto it(noteNamesToNumbers.find(name));
	if (it == std::end(noteNamesToNumbers))
		throw std::invalid_argument(name + " is no known note.");
	return 440. * std::pow(2, ((it->second + 12. * octave) - 49.) / 12.);
}

Signal1D Append(const Signal1D& lhs, const Signal1D& rhs)
{
	Signal1D out(lhs);
	out.insert(std::end(out), std::begin(rhs), std::end(rhs));
	return out;
}

namespace
{
std::random_device randomDevice;
std::mt19937 randomGenerator(randomDevice());
std::uniform_real_distribution<> randomDoubleDistribution(-1., 1.);
}

Signal1D Noise(double length, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	out.reserve(samples);
	for (Signal1D::size_type x(0); x < samples; ++x)
	{
		out.push_back(randomDoubleDistribution(randomGenerator));
	}
	return out;
}

Signal1D Line(double length, double start, double end, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	if (samples == 0)
		return out;
	out.reserve(samples);
	for (Signal1D::size_type x(0); x < samples; ++x)
	{
		out.push_back(start + x * (end - start) / samples);
	}
	return out;
}

Signal1D Sine(double freq, double length, double amp, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	out.reserve(samples);
	if (sampleRate <= std::numeric_limits<double>::epsilon())
		return out;
	for (Signal1D::size_type x(0); x < samples; ++x)
	{
		out.push_back(amp * std::sin(2 * pi * x * freq / sampleRate));
	}
	return out;
}

Signal1D Square(double freq, double length, double amp, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	out.reserve(samples);
	while (out.size() < samples)
	{
		out = Append(out, Line(.5 / freq, amp, amp, sampleRate));
		out = Append(out, Line(.5 / freq, -amp, -amp, sampleRate));
	}
	out.resize(samples);
	return out;
}

Signal1D Triangle(double freq, double length, double amp, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	out.reserve(samples);
	while (out.size() < samples)
	{
		out = Append(out, Line(.5 / freq, -amp, amp, sampleRate));
		out = Append(out, Line(.5 / freq, amp, -amp, sampleRate));
	}
	out.resize(samples);
	return out;
}

Signal1D Sawtooth(double freq, double length, double amp, double sampleRate)
{
	Signal1D out;
	Signal1D::size_type samples(static_cast<Signal1D::size_type>(length * sampleRate));
	out.reserve(samples);
	while (out.size() < samples)
	{
		out = Append(out, Line(1. / freq, -amp, amp, sampleRate));
	}
	out.resize(samples);
	return out;
}

Signal1D Multiply(const Signal1D& signal, const Value& factor)
{
	Signal1D out;
	out.reserve(signal.size());
	std::transform(std::begin(signal), std::end(signal), std::back_inserter(out), [&factor](const Value& value)
	{
		return value * factor;
	});
	return out;
}

Signal1D Multiply(const Signal1D& lhs, const Signal1D& rhs)
{
	Signal1D::size_type size(std::min(lhs.size(), rhs.size()));
	Signal1D out;
	out.reserve(size);
	std::transform(std::begin(lhs), std::begin(lhs) + size, std::begin(rhs), std::back_inserter(out),
			[](const Value& value1, const Value& value2)
			{
				return value1 * value2;
			});
	return out;
}

Signal1D Add(const Signal1D& lhs, const Signal1D& rhs)
{
	if (lhs.size() != rhs.size())
		throw std::length_error("Add: Samples must have the same size.");
	Signal1D out;
	out.reserve(lhs.size());
	std::transform(std::begin(lhs), std::end(lhs), std::begin(rhs), std::back_inserter(out),
			[](const Value& value1, const Value& value2)
			{
				return value1 + value2;
			});
	return out;
}

// Can be used internally for debugging
void PrintSignal(const Signal1D& signal)
{
	std::for_each(std::begin(signal), std::end(signal), [&](const Value& value)
	{
		std::cout << value << std::endl;
	});
}

Signal1D Normalize(const Signal1D& signal)
{
	double maxAbs(0.);
	std::for_each(std::begin(signal), std::end(signal), [&](const Value& value)
	{
		maxAbs = std::max(maxAbs, std::abs(value));
	});
	return Multiply(signal, 1. / maxAbs);
}

Signal1D LowPass(const Signal1D& signal, double dt, double rc)
{
	Signal1D out;
	Signal1D::size_type samples(signal.size());
	out.reserve(samples);
	out.push_back(signal.front());
	double alpha(dt / (rc + dt));
	for (Signal1D::size_type i(1); i < samples; ++i)
		out.push_back(alpha * signal[i] + (1 - alpha) * out.back());
	return out;
}

Signal1D ADSR(const Signal1D& in, double attackTime, double decayTime, double sustainLevel, double releaseTime, double,
		double sampleRate)
{
	Signal1D envelope(
			Append(Append(Line(attackTime, 0., 1., sampleRate), Line(decayTime, 1., sustainLevel, sampleRate)),
					Line(releaseTime, sustainLevel, 0., sampleRate)));
	return Multiply(in, envelope);
}

SFSoundPtrWithSoundBufferPtr ToSFSound(const Signal1D& signal)
{
	std::vector<sf::Int16> intSignal1D;
	intSignal1D.reserve(signal.size());
	std::transform(std::begin(signal), std::end(signal), std::back_inserter(intSignal1D), [](const Value& value)
	{
		return static_cast<sf::Int16>(32766.*std::max(std::min(value, 1.), -1.));
	});
	SFSoundPtrWithSoundBufferPtr soundPtrWithSoundBufferPtr(
			std::make_pair(std::make_shared<sf::Sound>(), std::make_shared<sf::SoundBuffer>()));
	soundPtrWithSoundBufferPtr.second->LoadFromSamples(&(intSignal1D[0]), intSignal1D.size(), 1, 44100);
	soundPtrWithSoundBufferPtr.first->SetBuffer(*soundPtrWithSoundBufferPtr.second);
	return soundPtrWithSoundBufferPtr;
}

namespace
{
SoundMap soundMap;
}

void KeepSound(const Signal1D& signal, const std::string& name)
{
	KeepSound(ToSFSound(signal), name);
}

void KeepSound(const SFSoundPtrWithSoundBufferPtr& soundPtrWithSoundBufferPtr, const std::string& name)
{
	soundMap[name] = soundPtrWithSoundBufferPtr;
}

bool PlaySound(const std::string& name)
{
	auto it(soundMap.find(name));
	if (it == std::end(soundMap))
		return false;
	PlaySound(it->second);
	return true;
}

namespace
{
bool muted(false);
}

void PlaySound(const SFSoundPtrWithSoundBufferPtr& soundPtrWithSoundBufferPtr)
{
	if (!muted)
		soundPtrWithSoundBufferPtr.first->Play();
}

void Mute(bool off)
{
	// Was the setting not really changed?
	if (off == muted)
		return;

	std::cout << "Sound: " << (muted ? "off" : "on") << std::endl;
	muted = off;
}

} /* namespace Synthesizer */

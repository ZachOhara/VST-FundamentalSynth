#ifndef PITCHBEND_H
#define PITCHBEND_H

#include "../JuceLibraryCode/JuceHeader.h"

class PitchBend {
public:
	PitchBend();
	~PitchBend();

	double getBentFrequency(double rawFrequency);
	void setModWheelValue(int wheelPos);

private:
	static const int MAX_WHEEL_VALUE = 0x3fff;
	const double SEMITONE = 16.0 / 15.0;
	static const int SEMITONE_RANGE = 2; // in either direction
	const double CORRECTION = .8952;

	double currentPitchMultiplier = 1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchBend)
};

#endif // PITCHBEND_H

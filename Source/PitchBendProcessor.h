#ifndef PITCHBEND_H
#define PITCHBEND_H

#include "../JuceLibraryCode/JuceHeader.h"

class PitchBendProcessor {
public:
	PitchBendProcessor();

	double getBentFrequency(double rawFrequency);
	void progressPitchBendRamp();
	void setModWheelValue(int wheelPos, int samples);
	void setPitchBend(double pitchBend);

private:
	static const int MAX_WHEEL_VALUE = 0x3fff;
	const double SEMITONE = 16.0 / 15.0;
	static const int SEMITONE_RANGE = 2; // in either direction
	const double CORRECTION = .8952;
	const double DELTA_PITCHBEND = 0.00001;

	double currentPitchBend = 0.5; // on [0,1]
	double targetPitchBend = 0.5;
	double deltaPitchBend = 0; // delta per sample

	double currentPitchMultiplier = 1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchBendProcessor)
};

#endif // PITCHBEND_H

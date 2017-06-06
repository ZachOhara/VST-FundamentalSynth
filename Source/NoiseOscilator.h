#ifndef NOISEOSCILATOR_H
#define NOISEOSCILATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

enum NoiseType {
	WHITE,
	PINK,
};

class NoiseOscilator {
public:
	NoiseOscilator();

	double getSampleValue();
	void setNoiseType(NoiseType newType);
	void setLevel(double newLevel);
	void setIsActive(bool newIsActive);

private:
	const double AMPLITUDE_CAP = 0.05;

	NoiseType noiseType = WHITE;
	double level = 1;
	bool isActive = true;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseOscilator)
};

#endif // NOISEOSCILATOR_H

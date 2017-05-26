#ifndef OSCILATORMIXER_H
#define OSCILATORMIXER_H

#include "../JuceLibraryCode/JuceHeader.h"

class OscilatorMixer {
public:
	OscilatorMixer();

	double mixValues(double* oscValues);

	void setRelativeLevel(int oscilatorIndex, double level);
	void setOscilatorIsActive(int oscilatorIndex, bool isActive);

private:
	double levels[3] = {1, 1, 1};
	bool oscIsActive[3] = {false, false, false};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilatorMixer)
};

#endif // OSCILATORMIXER_H

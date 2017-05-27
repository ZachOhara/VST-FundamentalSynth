#ifndef OSCILATORMIXER_H
#define OSCILATORMIXER_H

#include "../JuceLibraryCode/JuceHeader.h"

#define SYNTH_NUM_OSCILATORS 3

class OscilatorMixer {
public:
	OscilatorMixer();

	double mixValues(double* oscValues);

	void setRelativeLevel(int oscilatorIndex, double level);
	void setOscilatorIsActive(int oscilatorIndex, bool isActive);

private:
	double levels[SYNTH_NUM_OSCILATORS];
	bool oscIsActive[SYNTH_NUM_OSCILATORS];

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilatorMixer)
};

#endif // OSCILATORMIXER_H

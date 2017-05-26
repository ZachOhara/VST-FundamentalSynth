#ifndef TIMEFADER_H
#define TIMEFADER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeFader.h"

class TimeFader :
	public EnvelopeFader {
public:
	TimeFader();
	~TimeFader();

	const double MAX_VALUE = 2.0; // seconds
	const double STEP_SIZE = 0.001; // seconds
	const double MIN_VALUE = 0.002; // seconds

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimeFader)
};

#endif // TIMEFADER_H

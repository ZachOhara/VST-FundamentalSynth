#ifndef SUSTAINFADER_H
#define SUSTAINFADER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeFader.h"

class SustainFader :
	public EnvelopeFader {
public:
	SustainFader();

	const double STEP_SIZE = 1; // percent

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SustainFader)
};

#endif // SUSTAINFADER_H

#ifndef ENVELOPE_SUSTAINFADER_H_INCLUDED
#define ENVELOPE_SUSTAINFADER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeFader.h"

class SustainFader :
	public EnvelopeFader {
public:
	SustainFader();
	~SustainFader();

	const double STEP_SIZE = 1; // percent

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SustainFader)
};

#endif // !ENVELOPE_SUSTAINFADER_H_INCLUDED

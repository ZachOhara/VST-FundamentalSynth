#ifndef ENVELOPEFADER_H
#define EENVELOPEFADER_H

#include "../JuceLibraryCode/JuceHeader.h"

class EnvelopeFader :
	public Slider {
public:
	EnvelopeFader();
	~EnvelopeFader();

	const int TEXTBOX_WIDTH = 90; // pixels
	const int TEXTBOX_HEIGHT = 20; // pixels

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeFader)
};

#endif // ENVELOPEFADER_H

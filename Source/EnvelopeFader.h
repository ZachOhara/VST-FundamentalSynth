#ifndef ENVELOPE_ENVELOPEFADER_H_INCLUDED
#define ENVELOPE_ENVELOPEFADER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class EnvelopeFader :
	public Slider {
public:
	EnvelopeFader();
	~EnvelopeFader();

	const int TEXTBOX_WIDTH = 90; // pixels
	const int TEXTBOX_HEIGHT = 20; // pixels
};

#endif // !ENVELOPE_ENVELOPEFADER_H_INCLUDED
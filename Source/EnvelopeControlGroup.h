#ifndef ENVELOPECONTROLGROUP_H
#define ENVELOPECONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeProcessor.h"
#include "RadioButtonSet.h"

class EnvelopeControlGroup :
	public Component,
	Slider::Listener,
	RadioButtonSet::Listener {
public:
	EnvelopeControlGroup(EnvelopeProcessor* processor);

	void selectionChanged(String& newSelection) override;
	void sliderValueChanged(Slider* slider) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 300;

	Label* modeLabel;
	RadioButtonSet* modeButtonSet;

	struct EnvelopeSlider {
		Label* label;
		Slider* slider;
	};
	EnvelopeSlider attack;
	EnvelopeSlider decay;
	EnvelopeSlider sustain;
	EnvelopeSlider release;

	EnvelopeProcessor* envelopeProcessor;

	void initializeElement(EnvelopeSlider& element, String name,
		int yPos, double min, double max, double step, double start, bool skew);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeControlGroup)
};

#endif // ENVELOPECONTROLGROUP_H

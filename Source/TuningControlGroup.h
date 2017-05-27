#ifndef TUNINGCONTROLGROUP_H
#define TUNINGCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "TuningProcessor.h"
#include "RadioButtonSet.h"

class TuningControlGroup :
	public Component,
	RadioButtonSet::Listener,
	Slider::Listener {
public:
	TuningControlGroup(TuningProcessor* processor);

	void selectionChanged(String& newSelection) override;
	void sliderValueChanged(Slider* changed) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 100;
	const int BUTTONS_LEFT_OFFSET = 15;
	const int BUTTONS_TOP_OFFSET = 25;

	RadioButtonSet* modeButtonSet;
	Slider* keySlider;
	Label* keyLabel;

	TuningProcessor* tuningProcessor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TuningControlGroup)
};

#endif // TUNINGCONTROLGROUP_H

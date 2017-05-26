#ifndef TUNINGCONTROLGROUP_H
#define TUNINGCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "TuningSystem.h"
#include "RadioButtonSet.h"

class TuningControlGroup :
	public Component,
	RadioButtonSet::Listener,
	Slider::Listener {
public:
	TuningControlGroup(String name, String label, TuningSystem& processor);

	void selectionChanged(String& newSelection) override;
	void sliderValueChanged(Slider* changed) override;
	void resized() override;

private:
	const int WIDTH = 200;
	const int BUTTONS_LEFT_OFFSET = 15;
	const int BUTTONS_TOP_OFFSET = 25;
	const int HEIGHT = 100;

	TuningSystem* tuningProcessor;
	GroupComponent* groupOutline;
	RadioButtonSet* modeButtonSet;
	Slider* keySlider;
	Label* keyLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TuningControlGroup)
};

#endif // TUNINGCONTROLGROUP_H

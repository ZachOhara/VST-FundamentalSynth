#ifndef NOISEOSCILATORCONTROLGROUP_H
#define NOISEOSCILATORCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoiseOscilator.h"
#include "RadioButtonSet.h"

class NoiseOscilatorControlGroup :
	public Component,
	Button::Listener,
	Slider::Listener,
	RadioButtonSet::Listener {
public:
	NoiseOscilatorControlGroup(NoiseOscilator* processor);

	void selectionChanged(String& newSelection) override;
	void buttonClicked(Button* clicked) override;
	void sliderValueChanged(Slider* changed) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 125;

	ToggleButton* oscilatorEnabledButton;
	Label* oscilatorEnabledLabel;

	Slider* volumeSlider;
	Label* volumeLabel;

	RadioButtonSet* noiseTypeButtonSet;

	NoiseOscilator* oscilator;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoiseOscilatorControlGroup)
};

#endif // NOISEOSCILATORCONTROLGROUP_H

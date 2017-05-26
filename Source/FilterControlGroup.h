#ifndef FILTERCONTROLGROUP_H
#define FILTERCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

class FilterControlGroup :
	public Component,
	Slider::Listener,
	Button::Listener {
public:
	FilterControlGroup(String name, String label, Filter& filter);

	void sliderValueChanged(Slider* changed) override;
	void buttonClicked(Button* pressed) override;
	void resized() override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 200;

	ToggleButton* filterEnabledButton;
	Label* filterEnabledLabel;

	Slider* cutoffSlider;
	Slider* emphasisSlider;
	Slider* orderSlider;

	Label* cutoffLabel;
	Label* emphasisLabel;
	Label* orderLabel;

	Filter* filterProcessor;
	GroupComponent* groupOutline;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterControlGroup)
};

#endif // FILTERCONTROLGROUP_H

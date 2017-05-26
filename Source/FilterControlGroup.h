#ifndef FILTERCONTROLGROUP_H
#define FILTERCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

class FilterControlGroup :
	public Component,
	Slider::Listener,
	Button::Listener {
public:
	FilterControlGroup(Filter& processor);

	void sliderValueChanged(Slider* changed) override;
	void buttonClicked(Button* pressed) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 200;

	ToggleButton* filterEnabledButton;
	Label* filterEnabledLabel;

	struct ControlSlider {
		Label* label;
		Slider* slider;
	};

	ControlSlider cutoff;
	ControlSlider emphasis;
	ControlSlider order;

	Filter* filterProcessor;

	void initializeControlSlider(ControlSlider& slider, String name,
		int yPos, double min, double max, double step, double start);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterControlGroup)
};

#endif // FILTERCONTROLGROUP_H

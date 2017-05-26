#ifndef MIXERCONTROLGROUP_H
#define MIXERCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscilatorMixer.h"

class MixerControlGroup :
	public Component,
	public Slider::Listener,
	public Button::Listener {
public:
	MixerControlGroup(String name, String label, OscilatorMixer& baseMixer);
	~MixerControlGroup();

	void resized() override;
	void sliderValueChanged(Slider* changed) override;
	void buttonClicked(Button* clicked) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 425;

	Label* osc1label;
	Label* osc2label;
	Label* osc3label;

	Slider* osc1level;
	Slider* osc2level;
	Slider* osc3level;

	ToggleButton* osc1active;
	ToggleButton* osc2active;
	ToggleButton* osc3active;

	OscilatorMixer* baseMixer;
	GroupComponent* groupOutline;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerControlGroup)
};

#endif // MIXERCONTROLGROUP_H

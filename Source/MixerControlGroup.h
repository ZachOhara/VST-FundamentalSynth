#ifndef MIXERCONTROLGROUP_H
#define MIXERCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscilatorMixer.h"

class MixerControlGroup :
	public Component,
	Slider::Listener,
	Button::Listener {
public:
	MixerControlGroup(OscilatorMixer* processor);

	void sliderValueChanged(Slider* changed) override;
	void buttonClicked(Button* clicked) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 425;

	struct OscilatorControl {
		ToggleButton* activeButton;
		Label* label;
		Slider* levelSlider;
	};

	OscilatorControl controls[SYNTH_NUM_OSCILATORS];

	void initializeOscilatorControl(OscilatorControl& osc, int oscNum, int yPos);

	OscilatorMixer* mixer;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixerControlGroup)
};

#endif // MIXERCONTROLGROUP_H

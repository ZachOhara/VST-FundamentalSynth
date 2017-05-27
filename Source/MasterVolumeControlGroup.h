#ifndef MASTERVOLUMECONTROLGROUP_H
#define MASTERVOLUMECONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterVolume.h"

class MasterVolumeControlGroup :
	public Component,
	Slider::Listener {
public:
	MasterVolumeControlGroup(MasterVolumeProcessor* processor);

	void sliderValueChanged(Slider* changed) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 100;

	Label* label;
	Slider* slider;

	MasterVolumeProcessor* volumeProcessor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterVolumeControlGroup)
};

#endif // MASTERVOLUMECONTROLGROUP_H

#ifndef SYHTNMODECONTROLGROUP_H
#define SYHTNMODECONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "SettingsProcessor.h"
#include "RadioButtonSet.h"

class SynthModeControlGroup :
	public Component,
	RadioButtonSet::Listener {
public:
	SynthModeControlGroup(SettingsProcessor* processor);

	void selectionChanged(String& newSelection) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 100;

	RadioButtonSet* modeButtonSet;

	SettingsProcessor* settings;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthModeControlGroup)
};

#endif // SYHTNMODECONTROLGROUP_H

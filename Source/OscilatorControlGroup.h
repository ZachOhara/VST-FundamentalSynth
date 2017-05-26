#ifndef OSCILATORCONTROLGROUP_H
#define OSCILATORCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscilator.h"
#include "RadioButtonSet.h"

class OscilatorControlGroup :
	public Component,
	RadioButtonSet::Listener {
public:
	OscilatorControlGroup(int oscilatorNumber, Oscilator& oscilator);

	void selectionChanged(String& newSelection) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 125;

	Oscilator* oscilator;

	RadioButtonSet* waveTypeButtonSet;
	RadioButtonSet* octaveButtonSet;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilatorControlGroup)
};

#endif // OSCILATORCONTROLGROUP_H

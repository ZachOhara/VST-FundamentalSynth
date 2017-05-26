#ifndef OSCILATORCONTROLGROUP_H
#define OSCILATORCONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscilator.h"
#include "RadioButtonSet.h"

class OscilatorControlGroup :
	public Component,
	RadioButtonSet::Listener,
	ComboBox::Listener {
public:
	OscilatorControlGroup(String name, String label, Oscilator& oscilator);

	void selectionChanged(String& newSelection) override;
	void comboBoxChanged(ComboBox* boxChanged) override;

private:
	const int WIDTH = 200;
	const int HEIGHT = 125;

	Oscilator* baseOscilator;
	GroupComponent* groupOutline;
	RadioButtonSet* waveTypeButtonSet;
	RadioButtonSet* octaveSet;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilatorControlGroup)
};

#endif // OSCILATORCONTROLGROUP_H

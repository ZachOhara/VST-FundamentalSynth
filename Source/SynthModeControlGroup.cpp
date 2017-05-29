#include "SynthModeControlGroup.h"

SynthModeControlGroup::SynthModeControlGroup(SettingsProcessor* processor) {
	setSize(WIDTH, HEIGHT);
	settings = processor;

	String modes[2] = {"Polyphonic", "Monophonic"};
	modeButtonSet = new RadioButtonSet(this, modes, 2);
	modeButtonSet->setTopLeftPosition(15, 20);
	modeButtonSet->setSize(180, modeButtonSet->getNecessaryHeight());
	addAndMakeVisible(modeButtonSet);
}

void SynthModeControlGroup::selectionChanged(String & newSelection) {
	if (newSelection == "Polyphonic") {
		settings->setNewMode(POLYPHONIC);
	} else if (newSelection == "Monophonic") {
		settings->setNewMode(MONOPHONIC);
	}
}

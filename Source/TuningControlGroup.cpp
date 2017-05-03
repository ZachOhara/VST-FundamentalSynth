#include "TuningControlGroup.h"



TuningControlGroup::TuningControlGroup(String name, String label, TuningSystem& processor) {
	tuningProcessor = &processor;

	setSize(WIDTH, HEIGHT);
	
	String modes[2] = {"Equal Temperament", "Just Temperament"};
	modeButtonSet = new RadioButtonSet(this, modes, 2);
	addAndMakeVisible(modeButtonSet);
	modeButtonSet->setBounds(BUTTONS_LEFT_OFFSET, BUTTONS_TOP_OFFSET,
		WIDTH - BUTTONS_LEFT_OFFSET,
		modeButtonSet->getNecessaryHeight());

	groupOutline = new GroupComponent(name, label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	addAndMakeVisible(groupOutline);
	groupOutline->setTopLeftPosition(0, 0);
	groupOutline->setSize(getWidth(), getHeight());
}

TuningControlGroup::~TuningControlGroup() {

}

void TuningControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "Equal Temperament") {
		tuningProcessor->setTuningMode(EQUAL_TEMPERAMENT);
	} else if (newSelection == "Just Temperament") {
		tuningProcessor->setTuningMode(JUST_TEMPERAMENT);
	}
}

void TuningControlGroup::resized() {
}

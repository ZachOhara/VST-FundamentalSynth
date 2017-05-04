#include "OscilatorControlGroup.h"

OscilatorControlGroup::OscilatorControlGroup(String name, String label, Oscilator& oscilator) {
	baseOscilator = &oscilator;

	setSize(WIDTH, HEIGHT);

	String wavetypes[4] = {"Sine", "Triangle", "Sawtooth", "Square"};
	waveTypeButtonSet = new RadioButtonSet(this, wavetypes, 4);
	addAndMakeVisible(waveTypeButtonSet);
	waveTypeButtonSet->setBounds(15, 25,
		120, waveTypeButtonSet->getNecessaryHeight());

	String octaves[5] = {"32' (-2)", "16' (-1)", "8' (+0)", "4' (+1)", "2' (+2)"};
	octaveSet = new RadioButtonSet(this, octaves, 5);
	octaveSet->triggerClick(2);
	addAndMakeVisible(octaveSet);
	octaveSet->setTopLeftPosition(115, 17);
	octaveSet->setSize(90, octaveSet->getNecessaryHeight());
	
	/*
	octaveSelection = new ComboBox();
	octaveSelection->addItemList(StringArray(comboOptions, 6), 0);
	octaveSelection->setEditableText(false);
	octaveSelection->setSize(70, 25);
	octaveSelection->setTopLeftPosition(110, 55);
	octaveSelection->addListener(this);
	addAndMakeVisible(octaveSelection);
	*/

	groupOutline = new GroupComponent(name, label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	addAndMakeVisible(groupOutline);
	groupOutline->setTopLeftPosition(0, 0);
	groupOutline->setSize(getWidth(), getHeight());
}

OscilatorControlGroup::~OscilatorControlGroup() {
	// take no action
}

void OscilatorControlGroup::comboBoxChanged(ComboBox* boxChanged) {
	//baseOscilator->setOctaveOffset(octaveSelection->getSelectedId() - 3);
}

void OscilatorControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "Sine") {
		baseOscilator->setWaveType(SINE);
	} else if (newSelection == "Triangle") {
		baseOscilator->setWaveType(TRIANGLE);
	} else if(newSelection == "Sawtooth") {
		baseOscilator->setWaveType(SAWTOOTH);
	} else if(newSelection == "Square") {
		baseOscilator->setWaveType(SQUARE);
	} else if (newSelection == "32' (-2)") {
		baseOscilator->setOctaveOffset(-2);
	} else if (newSelection == "16' (-1)") {
		baseOscilator->setOctaveOffset(-1);
	} else if (newSelection == "8' (+0)") {
		baseOscilator->setOctaveOffset(0);
	} else if (newSelection == "4' (+1)") {
		baseOscilator->setOctaveOffset(1);
	} else if (newSelection == "2' (+2)") {
		baseOscilator->setOctaveOffset(2);
	}
}

void OscilatorControlGroup::resized() {

}

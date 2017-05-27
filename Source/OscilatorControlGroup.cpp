#include "OscilatorControlGroup.h"

OscilatorControlGroup::OscilatorControlGroup(Oscilator* processor) {
	setSize(WIDTH, HEIGHT);
	oscilator = processor;

	String wavetypes[4] = {"Sine", "Triangle", "Sawtooth", "Square"};
	waveTypeButtonSet = new RadioButtonSet(this, wavetypes, 4);
	waveTypeButtonSet->setTopLeftPosition(15, 25);
	waveTypeButtonSet->setSize(120, waveTypeButtonSet->getNecessaryHeight());
	addAndMakeVisible(waveTypeButtonSet);

	String octaves[5] = {"32' (-2)", "16' (-1)", "8' (+0)", "4' (+1)", "2' (+2)"};
	octaveButtonSet = new RadioButtonSet(this, octaves, 5);
	octaveButtonSet->setTopLeftPosition(115, 15);
	octaveButtonSet->setSize(90, octaveButtonSet->getNecessaryHeight());
	addAndMakeVisible(octaveButtonSet);

	octaveButtonSet->triggerClick(2);
}

void OscilatorControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "Sine") {
		oscilator->setWaveType(SINE);
	} else if (newSelection == "Triangle") {
		oscilator->setWaveType(TRIANGLE);
	} else if(newSelection == "Sawtooth") {
		oscilator->setWaveType(SAWTOOTH);
	} else if(newSelection == "Square") {
		oscilator->setWaveType(SQUARE);
	} else if (newSelection == "32' (-2)") {
		oscilator->setOctaveOffset(-2);
	} else if (newSelection == "16' (-1)") {
		oscilator->setOctaveOffset(-1);
	} else if (newSelection == "8' (+0)") {
		oscilator->setOctaveOffset(0);
	} else if (newSelection == "4' (+1)") {
		oscilator->setOctaveOffset(1);
	} else if (newSelection == "2' (+2)") {
		oscilator->setOctaveOffset(2);
	}
}

#include "FundamentalSynthesizerEditor.h"
#include "PluginProcessor.h"

FundamentalSynthesizerEditor::FundamentalSynthesizerEditor(FSynthAudioProcessor& p,
	SynthProcessorSet synth):

	AudioProcessorEditor (&p) {
	setSize(1150, 475);

	// FIRST COLUMN

	// 200 x 100
	tuningControl = new TuningControlGroup(synth.tuning);
	tuningControl->setTopLeftPosition(25, 25);
	addAndMakeVisible(tuningControl);
	generateGroupOutline("Tuning", tuningControl);

	// SECOND COLUMN

	// each is 200 x 125
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		oscilatorControls[i] = new OscilatorControlGroup(&synth.oscilatorArray[i]);
		oscilatorControls[i]->setTopLeftPosition(250, 25 + (i * 150));
		addAndMakeVisible(oscilatorControls[i]);
		String name = "Oscilator ";
		name << (i + 1);
		generateGroupOutline(name, oscilatorControls[i]);
	}

	// THIRD COLUMN

	// 200 x 425
	mixerControl = new MixerControlGroup(synth.mixer);
	mixerControl->setTopLeftPosition(475, 25);
	addAndMakeVisible(mixerControl);
	generateGroupOutline("Mixer", mixerControl);

	// FOURTH COLUMN

	// 200 x 200
	filterControl = new FilterControlGroup(synth.filter);
	filterControl->setTopLeftPosition(700, 25);
	addAndMakeVisible(filterControl);
	generateGroupOutline("Filter", filterControl);

	// FIFTH COLUMN

	// 200 x 300
	envelopeControl = new EnvelopeControlGroup(synth.envelope);
	envelopeControl->setTopLeftPosition(925, 25);
	addAndMakeVisible(envelopeControl);
	generateGroupOutline("Envelope", envelopeControl);
}

FundamentalSynthesizerEditor::~FundamentalSynthesizerEditor() {
	delete tuningControl;
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		delete oscilatorControls[i];
	}
	delete mixerControl;
	delete filterControl;
	delete envelopeControl;
}

void FundamentalSynthesizerEditor::generateGroupOutline(String label, Component* component) {
	GroupComponent* outline = new GroupComponent(label, label);
	outline->setTextLabelPosition(Justification::top);
	outline->setColour(outline->outlineColourId, Colours::black);
	outline->setTopLeftPosition(component->getPosition());
	outline->setSize(component->getWidth(), component->getHeight());
	addAndMakeVisible(outline);
}

void FundamentalSynthesizerEditor::paint (Graphics& g) {
    g.fillAll(Colours::white);
}

void FundamentalSynthesizerEditor::resized() {

}

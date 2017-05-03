#include "FundamentalSynthesizerEditor.h"
#include "PluginProcessor.h"

FundamentalSynthesizerEditor::FundamentalSynthesizerEditor(FSynthAudioProcessor& p, EnvelopeProcessor& envelope, TuningSystem& tuning) :
	AudioProcessorEditor (&p) {
	setSize(600, 500);

	envelopeControl = new EnvelopeControlGroup("Envelope", "Envelope", envelope);
	envelopeControl->setTopLeftPosition(250, 25);
	addAndMakeVisible(envelopeControl);

	tuningControl = new TuningControlGroup("Tuning", "Tuning", tuning);
	tuningControl->setTopLeftPosition(25, 25);
	addAndMakeVisible(tuningControl);
	/*
	String names[3] = {"Alice", "Bob", "Candice"};
	sampleSet = new RadioButtonSet(names, 3);

	addAndMakeVisible(sampleSet);
	sampleSet->setBounds(0, 0, 300, sampleSet->getNecessaryHeight());
	*/
}

FundamentalSynthesizerEditor::~FundamentalSynthesizerEditor() {
	delete envelopeControl;
}

void FundamentalSynthesizerEditor::paint (Graphics& g) {
    g.fillAll(Colours::white);
}

void FundamentalSynthesizerEditor::resized() {

}

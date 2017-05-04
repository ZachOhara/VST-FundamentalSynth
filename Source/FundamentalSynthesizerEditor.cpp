#include "FundamentalSynthesizerEditor.h"
#include "PluginProcessor.h"

FundamentalSynthesizerEditor::FundamentalSynthesizerEditor(FSynthAudioProcessor& p,
	EnvelopeProcessor& envelope, TuningSystem& tuning,
	Oscilator& oscilator1, Oscilator& oscilator2) :
	AudioProcessorEditor (&p) {
	setSize(600, 500);

	tuningControl = new TuningControlGroup("Tuning", "Tuning", tuning);
	tuningControl->setTopLeftPosition(25, 25);
	addAndMakeVisible(tuningControl);

	oscilator1control = new OscilatorControlGroup("Oscilator 1", "Oscilator 1", oscilator1);
	oscilator1control->setTopLeftPosition(25, 150);
	addAndMakeVisible(oscilator1control);

	oscilator2control = new OscilatorControlGroup("Oscilator 2", "Oscilator 2", oscilator2);
	oscilator2control->setTopLeftPosition(25, 300);
	addAndMakeVisible(oscilator2control);

	envelopeControl = new EnvelopeControlGroup("Envelope", "Envelope", envelope);
	envelopeControl->setTopLeftPosition(250, 25);
	addAndMakeVisible(envelopeControl);
}

FundamentalSynthesizerEditor::~FundamentalSynthesizerEditor() {
	delete tuningControl;
	delete oscilator1control;
	delete envelopeControl;
}

void FundamentalSynthesizerEditor::paint (Graphics& g) {
    g.fillAll(Colours::white);
}

void FundamentalSynthesizerEditor::resized() {

}

#include "FundamentalSynthesizerEditor.h"
#include "PluginProcessor.h"

FundamentalSynthesizerEditor::FundamentalSynthesizerEditor(FSynthAudioProcessor& p,
	EnvelopeProcessor& envelope, TuningSystem& tuning,
	Oscilator& oscilator1, Oscilator& oscilator2, Oscilator& oscilator3,
	OscilatorMixer& mixer, Filter& filter):

	AudioProcessorEditor (&p) {
	setSize(1200, 500);

	// FIRST COLUMN

	// 200 x 100
	tuningControl = new TuningControlGroup("Tuning", "Tuning", tuning);
	tuningControl->setTopLeftPosition(25, 25);
	addAndMakeVisible(tuningControl);

	// SECOND COLUMN

	// 200 x 125
	oscilator1control = new OscilatorControlGroup("Oscilator 1", "Oscilator 1", oscilator1);
	oscilator1control->setTopLeftPosition(250, 25);
	addAndMakeVisible(oscilator1control);

	// 200 x 125
	oscilator2control = new OscilatorControlGroup("Oscilator 2", "Oscilator 2", oscilator2);
	oscilator2control->setTopLeftPosition(250, 175);
	addAndMakeVisible(oscilator2control);

	// 200 x 125
	oscilator3control = new OscilatorControlGroup("Oscilator 3", "Oscilator 3", oscilator3);
	oscilator3control->setTopLeftPosition(250, 325);
	addAndMakeVisible(oscilator3control);

	// THIRD COLUMN

	// 200 x 500
	mixerControl = new MixerControlGroup("Mixer", "Mixer", mixer);
	mixerControl->setTopLeftPosition(475, 25);
	addAndMakeVisible(mixerControl);

	// FOURTH COLUMN

	// 200 x 200
	filterControl = new FilterControlGroup("Filter", "Filter", filter);
	filterControl->setTopLeftPosition(700, 25);
	addAndMakeVisible(filterControl);

	envelopeControl = new EnvelopeControlGroup("Envelope", "Envelope", envelope);
	envelopeControl->setTopLeftPosition(925, 25);
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

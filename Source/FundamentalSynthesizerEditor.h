#ifndef FUNDAMENTALSYNTHESIZEREDITOR_H
#define FUNDAMENTALSYNTHESIZEREDITOR_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "FundamentalSynthesizer.h"
#include "EnvelopeProcessor.h"
#include "TimeFader.h"
#include "SustainFader.h"
#include "EnvelopeControlGroup.h"
#include "RadioButtonSet.h"
#include "TuningControlGroup.h"
#include "OscilatorControlGroup.h"
#include "OscilatorMixer.h"
#include "MixerControlGroup.h"
#include "FilterControlGroup.h"

class FSynthAudioProcessor;

class FundamentalSynthesizerEditor :
	public AudioProcessorEditor {
public:
    FundamentalSynthesizerEditor(FSynthAudioProcessor& p,
		SynthProcessorSet synth);
    ~FundamentalSynthesizerEditor();
	
    void paint (Graphics&) override;
    void resized() override;

private:
	TuningControlGroup* tuningControl;
	OscilatorControlGroup* oscilatorControls[SYNTH_NUM_OSCILATORS];
	MixerControlGroup* mixerControl;
	FilterControlGroup* filterControl;

	EnvelopeControlGroup* envelopeControl;

	void generateGroupOutline(String label, Component* component);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FundamentalSynthesizerEditor)
};

#endif // FUNDAMENTALSYNTHESIZEREDITOR_H

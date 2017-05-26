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
		EnvelopeProcessor& envelope, TuningProcessor& tuning,
		Oscilator& oscilator1, Oscilator& oscilator2, Oscilator& oscilator3,
		OscilatorMixer& mixer, Filter& filter);
    ~FundamentalSynthesizerEditor();
	
    void paint (Graphics&) override;
    void resized() override;

private:
	TuningControlGroup* tuningControl;
	OscilatorControlGroup* oscilator1control;
	OscilatorControlGroup* oscilator2control;
	OscilatorControlGroup* oscilator3control;
	MixerControlGroup* mixerControl;
	FilterControlGroup* filterControl;

	EnvelopeControlGroup* envelopeControl;

	void generateGroupOutline(String label, Component* component);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FundamentalSynthesizerEditor)
};

#endif // FUNDAMENTALSYNTHESIZEREDITOR_H

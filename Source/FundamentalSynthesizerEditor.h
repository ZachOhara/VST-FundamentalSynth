#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FundamentalSynthesizer.h"
#include "EnvelopeProcessor.h"
#include "TimeFader.h"
#include "SustainFader.h"
#include "EnvelopeControlGroup.h"
#include "RadioButtonSet.h"
#include "TuningControlGroup.h"
#include "OscilatorControlGroup.h"

class FSynthAudioProcessor;

class FundamentalSynthesizerEditor :
	public AudioProcessorEditor {
public:
    FundamentalSynthesizerEditor(FSynthAudioProcessor& p,
		EnvelopeProcessor& envelope, TuningSystem& tuning,
		Oscilator& oscilator1, Oscilator& oscilator2, Oscilator& oscilator3);
    ~FundamentalSynthesizerEditor();
	
    void paint (Graphics&) override;
    void resized() override;

private:
	TuningControlGroup* tuningControl;
	OscilatorControlGroup* oscilator1control;
	OscilatorControlGroup* oscilator2control;
	OscilatorControlGroup* oscilator3control;
	EnvelopeControlGroup* envelopeControl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FundamentalSynthesizerEditor)
};

#endif // !PLUGINEDITOR_H_INCLUDED

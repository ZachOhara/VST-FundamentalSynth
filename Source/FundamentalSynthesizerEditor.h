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

class FSynthAudioProcessor;

class FundamentalSynthesizerEditor :
	public AudioProcessorEditor {
public:
    FundamentalSynthesizerEditor(FSynthAudioProcessor& p, EnvelopeProcessor& envelope, TuningSystem& tuning);
    ~FundamentalSynthesizerEditor();
	
    void paint (Graphics&) override;
    void resized() override;

private:
	EnvelopeControlGroup* envelopeControl;
	TuningControlGroup* tuningControl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FundamentalSynthesizerEditor)
};

#endif // !PLUGINEDITOR_H_INCLUDED

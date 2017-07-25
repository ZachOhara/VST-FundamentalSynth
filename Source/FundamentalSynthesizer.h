#ifndef FUNDAMENTALSYNTHESIZER_H
#define FUNDAMENTALSYNTHESIZER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscilator.h"
#include "NoiseOscilator.h"
#include "EnvelopeProcessor.h"
#include "TuningProcessor.h"
#include "PitchBendProcessor.h"
#include "OscilatorMixer.h"
#include "Filter.h"
#include "SettingsProcessor.h"

#include "Logger.h"

// This struct does not include every element of the synth,
// only the parts that will be passed to the GUI
struct SynthProcessorSet {
	TuningProcessor* tuning;
	Oscilator* oscilatorArray;
	OscilatorMixer* mixer;
	NoiseOscilator* noise;
	Filter* filter;
	EnvelopeProcessor* envelope;
	SettingsProcessor* settings;
};

enum NotePedalState {
	INACTIVE,
	PRESSED,
	PEDALED,
};

struct Notestatus {
	bool isNotePlaying = false;
	NotePedalState pedalState;
	NoteEnvelopeState envelopeState;

	double oscPhase[SYNTH_NUM_OSCILATORS];

	void beginNote(EnvelopeProcessor& envelope, double currentTime) {
		isNotePlaying = true; // this is turned off by the envelope processor, not here
		pedalState = PRESSED;
		envelope.beginNote(envelopeState, currentTime);
	}

	void releaseNote(EnvelopeProcessor& envelope, double currentTime) {
		pedalState = INACTIVE;
		envelope.releaseNote(envelopeState, currentTime);
	}
};

class FundamentalSynthesizer {
public:
	FundamentalSynthesizer();

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void freeResources();
	void processBlock(AudioSampleBuffer& audioBuffer, MidiBuffer& midiBuffer);

	SynthProcessorSet getInterfaceProcessors();

private:
	DebugLogger debugLog;

	double secondsPerSample;
	double secondsPerBlock;
	int currentSamplesPerBlock;

	double currentTime;
	double currentBlockTime;

	double* sampleBuffer;

	bool isPedalOn = false;

	Notestatus keyboardNotes[128];

	TuningProcessor tuningProcessor;
	Oscilator oscilators[SYNTH_NUM_OSCILATORS];
	OscilatorMixer mixer;
	NoiseOscilator noise;
	Filter filter;
	PitchBendProcessor pitchBendProcessor;
	EnvelopeProcessor envelopeProcessor;
	SettingsProcessor settings;

	void processMidiMessages(MidiBuffer& midiBuffer);
	void synthesizeAudio();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FundamentalSynthesizer)
};

#endif // FUNDAMENTALSYNTHESIZER_H

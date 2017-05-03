#ifndef SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H
#define SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "FundamentalSynthesizerEditor.h"
#include "Oscilator.h"
#include "EnvelopeProcessor.h"
#include "TuningSystem.h"
#include "PitchBend.h"

struct notestatus {
	bool isNotePlaying = false;
	NoteEnvelopeState envelopeState;
	NoteOscilatorState oscilatorState;
};

class FundamentalSynthesizer {
public:
	FundamentalSynthesizer();
	~FundamentalSynthesizer();


	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void freeResources();
	void processBlock(AudioSampleBuffer& audioBuffer, MidiBuffer& midiBuffer);

	EnvelopeProcessor& getEnvelopeProcessor();
	TuningSystem& getTuningProcessor();

private:
	double secondsPerSample;
	double secondsPerBlock;
	int currentSamplesPerBlock;

	double currentTime;
	double currentBlockTime;

	double* sampleBuffer;

	notestatus keyboardNotes[128];

	Oscilator oscilator;
	TuningSystem tuningMap;
	PitchBend pitchBendProcessor;
	EnvelopeProcessor envelopeProcessor;

	void processMidiMessages(MidiBuffer& midiBuffer);
	void synthesizeAudio();
};

#endif // !SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H

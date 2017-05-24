#ifndef SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H
#define SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "FundamentalSynthesizerEditor.h"
#include "Oscilator.h"
#include "EnvelopeProcessor.h"
#include "TuningSystem.h"
#include "PitchBend.h"
#include "OscilatorMixer.h"

enum NotePedalState {
	INACTIVE,
	PRESSED,
	PEDALED,
};

struct Notestatus {
	bool isNotePlaying = false;
	NotePedalState pedalState;
	NoteEnvelopeState envelopeState;

	void beginNote(EnvelopeProcessor& envelope, double currentTime) {
		isNotePlaying = true; // this is turned off by the envelope processor, not here
		pedalState = PRESSED;
		envelopeState.runningTime = currentTime; // should be <= 0
		envelope.beginNote(envelopeState);
	}

	void releaseNote(EnvelopeProcessor& envelope, double currentTime) {
		pedalState = INACTIVE;
		envelope.releaseNote(envelopeState);
		envelopeState.runningTime = currentTime; // should be <= 0
	}
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
	Oscilator& getOscilator1();
	Oscilator& getOscilator2();
	Oscilator& getOscilator3();
	OscilatorMixer& getMixer();

private:
	double secondsPerSample;
	double secondsPerBlock;
	int currentSamplesPerBlock;

	double currentTime;
	double currentBlockTime;

	double* sampleBuffer;

	bool isPedalOn = false;

	Notestatus keyboardNotes[128];

	Oscilator oscilator1;
	Oscilator oscilator2;
	Oscilator oscilator3;
	OscilatorMixer mixer;
	TuningSystem tuningMap;
	PitchBend pitchBendProcessor;
	EnvelopeProcessor envelopeProcessor;

	void processMidiMessages(MidiBuffer& midiBuffer);
	void synthesizeAudio();
};

#endif // !SYNTHESIZER_FUNDAMENTALSYNTHESIZER_H

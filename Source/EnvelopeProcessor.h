#ifndef ENVELOPEPROCESSOR_H_INCLUDED
#define ENVELOPEPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Logger.h"

enum EnvelopeScalingMode {
	LINEAR,
	EXPONENTIAL,
	LOGARITHMIC,
};

enum EnvelopeSection {
	SILENCE,
	PRE_ATTACK,
	ATTACK,
	DECAY,
	SUSTAIN,
	PRE_RELEASE,
	RELEASE,
};

struct NoteEnvelopeState {
	EnvelopeSection currentSection = SILENCE;
	double currentVolume = 0; // [0,1]
	double volumeDelta = 0; // per sample
	double runningTime = 0;
};

class EnvelopeProcessor {
public:
	EnvelopeProcessor();

	void beginNote(NoteEnvelopeState& state, double newTime);
	void releaseNote(NoteEnvelopeState& state, double newTime);
	bool isFinishedReleasing(NoteEnvelopeState& state);
	double getVolumeAfterTime(NoteEnvelopeState& state);

	void setScalingMode(EnvelopeScalingMode newMode);
	void setSecondsPerSample(double time);
	void setAttackTime(double time);
	void setDecayTime(double time);
	void setSustainLevel(double level);
	void setReleaseTime(double time);

private:
	EnvelopeScalingMode currentMode = LINEAR;
	double secondsPerSample = 0;
	double attackTime = 0;
	double decayTime = 0;
	double sustainLevel = 1;
	double releaseTime = 0;

	double getScaledLevel(double unscaledLevel);

	bool isReadyToProgress(NoteEnvelopeState& state);
	void progressState(NoteEnvelopeState& state);
	void progressToAttack(NoteEnvelopeState& statee);
	void progressToDecay(NoteEnvelopeState& state);
	void progressToSustain(NoteEnvelopeState& state);
	void progressToRelease(NoteEnvelopeState& state);
	void progressToSilence(NoteEnvelopeState& state);

	double getAttackTime();
	double getDecayTime();
	double getSustainLevel();
	double getReleaseTime();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeProcessor)
};

#endif // ENVELOPEPROCESSOR_H_INCLUDED

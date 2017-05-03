#ifndef ENVELOPEPROCESSOR_H_INCLUDED
#define ENVELOPEPROCESSOR_H_INCLUDED

#include "TimeFader.h"
#include "SustainFader.h"

enum envelopeScalingMode {
	LINEAR,
	EXPONENTIAL,
	LOGARITHMIC,
};

enum envelopeSection {
	SILENCE,
	PRE_ATTACK,
	ATTACK,
	DECAY,
	SUSTAIN,
	PRE_RELEASE,
	RELEASE,
};

struct envelopeNoteState {
	int currentState = 0; // 0 for silent, [1,4] for ADSR
	envelopeSection currentSection = SILENCE;
	double currentVolume = 0; // [0,1]
	double volumeDelta = 0; // per sample
	double runningTime = 0;
};

class EnvelopeProcessor {
public:
	EnvelopeProcessor();
	~EnvelopeProcessor();

	void beginNote(envelopeNoteState& state);
	void releaseNote(envelopeNoteState& state);
	bool isFinishedReleasing(envelopeNoteState& state);
	double getVolumeAfterTime(envelopeNoteState& state);

	void setScalingMode(envelopeScalingMode newMode);
	void setSecondsPerSample(double time);
	void setAttackTime(double time);
	void setDecayTime(double time);
	void setSustainLevel(double level);
	void setReleaseTime(double time);

private:
	envelopeScalingMode currentMode = LINEAR;
	double secondsPerSample = 0;
	double attackTime = 0;
	double decayTime = 0;
	double sustainLevel = 1;
	double releaseTime = 0;

	double getScaledLevel(double unscaledLevel);

	bool isReadyToProgress(envelopeNoteState& state);
	void progressState(envelopeNoteState& state);
	void progressToAttack(envelopeNoteState& statee);
	void progressToDecay(envelopeNoteState& state);
	void progressToSustain(envelopeNoteState& state);
	void progressToRelease(envelopeNoteState& state);
	void progressToSilence(envelopeNoteState& state);

	double getAttackTime();
	double getDecayTime();
	double getSustainLevel();
	double getReleaseTime();
};

#endif // !ENVELOPEPROCESSOR_H_INCLUDED

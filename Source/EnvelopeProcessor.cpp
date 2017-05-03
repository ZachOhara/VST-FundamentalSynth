#include "EnvelopeProcessor.h"

EnvelopeProcessor::EnvelopeProcessor() {
	
}

EnvelopeProcessor::~EnvelopeProcessor() {
	// take no action
}

void EnvelopeProcessor::beginNote(envelopeNoteState& state) {
	state.currentSection = PRE_ATTACK;
}

void EnvelopeProcessor::releaseNote(envelopeNoteState& state) {
	state.currentSection = PRE_RELEASE;
}

bool EnvelopeProcessor::isFinishedReleasing(envelopeNoteState& state) {
	//return state.runningTime > getReleaseTime() && state.currentState == 3; // TODO: fix this bullshit
	return state.currentSection == SILENCE;
}

double EnvelopeProcessor::getVolumeAfterTime(envelopeNoteState& state) {
	if (isReadyToProgress(state)) {
		progressState(state);
	}
	state.currentVolume += state.volumeDelta;
	state.runningTime += secondsPerSample;
	return getScaledLevel(state.currentVolume);
}

double EnvelopeProcessor::getScaledLevel(double unscaledLevel) {
	switch (currentMode) {
	case LINEAR:
		return unscaledLevel;
	case EXPONENTIAL:
		return std::pow(unscaledLevel, 2); // TODO fix this
	case LOGARITHMIC:
		return std::pow(unscaledLevel, 0.5);
	default:
		return 0;
	}
}

bool EnvelopeProcessor::isReadyToProgress(envelopeNoteState& state) {
	switch (state.currentSection) {
	case SILENCE:
		return false; // triggered by a call to beginNote()
	case PRE_ATTACK:
		return state.runningTime > 0;
	case ATTACK:
		return state.runningTime > getAttackTime();
	case DECAY:
		return state.runningTime > getAttackTime() + getDecayTime();
	case SUSTAIN:
		return false; // triggered by a call to releaseNote()
	case PRE_RELEASE:
		return state.runningTime > 0;
	case RELEASE:
		return state.runningTime > getReleaseTime();
	default:
		return false;
	}
}

void EnvelopeProcessor::progressState(envelopeNoteState& state) {
	switch (state.currentSection) {
	case PRE_ATTACK:
		progressToAttack(state);
		break;
	case ATTACK:
		progressToDecay(state);
		break;
	case DECAY:
		progressToSustain(state);
		break;
	case PRE_RELEASE:
		progressToRelease(state);
		break;
	case RELEASE:
		progressToSilence(state);
		break;
	}
}

void EnvelopeProcessor::progressToAttack(envelopeNoteState& state) {
	if (state.runningTime <= getAttackTime()) {
		state.currentSection = ATTACK;
		state.volumeDelta = (1 - state.currentVolume) / (getAttackTime() / secondsPerSample);
	} else {
		state.currentVolume = 1;
		progressToDecay(state);
	}
}

void EnvelopeProcessor::progressToDecay(envelopeNoteState& state) {
	if (state.runningTime <= getAttackTime() + getDecayTime()) {
		state.currentSection = DECAY;
		state.volumeDelta = (getSustainLevel() - state.currentVolume) / (getDecayTime() / secondsPerSample);
	} else {
		progressToSustain(state);
	}
}

void EnvelopeProcessor::progressToSustain(envelopeNoteState& state) {
	state.currentSection = SUSTAIN;
	state.currentVolume = getSustainLevel();
	state.volumeDelta = 0;
}

void EnvelopeProcessor::progressToRelease(envelopeNoteState& state) {
	if (state.runningTime <= getReleaseTime()) {
		state.currentSection = RELEASE;
		state.volumeDelta = (0 - state.currentVolume) / (getReleaseTime() / secondsPerSample);
	} else {
		progressToSilence(state);
	}
}

void EnvelopeProcessor::progressToSilence(envelopeNoteState& state) {
	state.currentSection = SILENCE;
	state.currentVolume = 0;
	state.volumeDelta = 0;
}

double EnvelopeProcessor::getAttackTime() {
	return attackTime;
}

double EnvelopeProcessor::getDecayTime() {
	return decayTime;
}

double EnvelopeProcessor::getSustainLevel() {
	return sustainLevel;
}

double EnvelopeProcessor::getReleaseTime() {
	return releaseTime;
}


void EnvelopeProcessor::setScalingMode(envelopeScalingMode newMode) {
	currentMode = newMode;
}

void EnvelopeProcessor::setSecondsPerSample(double time) {
	secondsPerSample = time;
}

void EnvelopeProcessor::setAttackTime(double time) {
	attackTime = time;
}

void EnvelopeProcessor::setDecayTime(double time) {
	decayTime = time;
}

void EnvelopeProcessor::setSustainLevel(double level) {
	sustainLevel = level;
}

void EnvelopeProcessor::setReleaseTime(double time) {
	releaseTime = time;
}

#include "PitchBendProcessor.h"

PitchBendProcessor::PitchBendProcessor() {

}

double PitchBendProcessor::getBentFrequency(double rawFrequency) {
	return rawFrequency * currentPitchMultiplier;
}

void PitchBendProcessor::progressPitchBendRamp() {
	// this should be called once per sample
	currentPitchBend += deltaPitchBend;
	if ((deltaPitchBend > 0 && currentPitchBend >= targetPitchBend)
		|| (deltaPitchBend < 0 && currentPitchBend <= targetPitchBend)) {
		currentPitchBend = targetPitchBend;
		deltaPitchBend = 0;
	}
	setPitchBend(currentPitchBend);
}

void PitchBendProcessor::setModWheelValue(int wheelPos, int samples) {
	double pitchBend = ((double) wheelPos) / MAX_WHEEL_VALUE;
	targetPitchBend = pitchBend;
	deltaPitchBend = DELTA_PITCHBEND;
	if (targetPitchBend < currentPitchBend) {
		deltaPitchBend *= -1;
	}
}

void PitchBendProcessor::setPitchBend(double pitchBend) {
	// pitchBend should be on [0,1]
	pitchBend *= 2;
	pitchBend -= 1;
	pitchBend *= SEMITONE_RANGE;
	pitchBend *= CORRECTION;

	currentPitchMultiplier = std::pow(SEMITONE, pitchBend);
}

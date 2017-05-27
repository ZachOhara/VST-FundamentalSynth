#include "PitchBendProcessor.h"

PitchBendProcessor::PitchBendProcessor() {

}

double PitchBendProcessor::getBentFrequency(double rawFrequency) {
	return rawFrequency * currentPitchMultiplier;
}

void PitchBendProcessor::setModWheelValue(int wheelPos) {
	double pitchBend = ((double) wheelPos) / MAX_WHEEL_VALUE;
	pitchBend *= 2;
	pitchBend -= 1;
	pitchBend *= SEMITONE_RANGE;
	pitchBend *= CORRECTION;

	currentPitchMultiplier = std::pow(SEMITONE, pitchBend);
}

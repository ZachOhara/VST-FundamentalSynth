#include "NoiseOscilator.h"

NoiseOscilator::NoiseOscilator() {
	
}

double NoiseOscilator::getSampleValue() {
	if (isActive) {
		if (noiseType == WHITE) {
			return (((double) rand()) / RAND_MAX) * level * AMPLITUDE_CAP;
		} else if (noiseType == PINK) {
			return 0; // TODO implement later
		}
	} else {
		return 0;
	}
}

void NoiseOscilator::setNoiseType(NoiseType newType) {
	noiseType = newType;
}

void NoiseOscilator::setLevel(double newLevel) {
	level = newLevel;
}

void NoiseOscilator::setIsActive(bool newIsActive) {
	isActive = newIsActive;
}

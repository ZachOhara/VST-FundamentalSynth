#include "NoiseOscilator.h"

NoiseOscilator::NoiseOscilator() {
	// all these constants are determined experimentally
	pinkFilter.setCutoff(4600);
	pinkFilter.setEmphasis(1);
	pinkFilter.setOrder(3);
	pinkFilter.setIsEnabled(true);
}

double NoiseOscilator::getSampleValue() {
	if (isActive) {
		double white = (((double) rand()) / RAND_MAX) * level * AMPLITUDE_CAP;
		double pink = pinkFilter.getNextOutput(white);
		if (noiseType == WHITE) {
			return white;
		} else if (noiseType == PINK) {
			return pink;
		}
	} else {
		return 0;
	}
}

void NoiseOscilator::setSampleRate(double newSampleRate) {
	pinkFilter.setSampleRate(newSampleRate);
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

#include "OscilatorMixer.h"

OscilatorMixer::OscilatorMixer() {
	
}

OscilatorMixer::~OscilatorMixer() {

}

double OscilatorMixer::mixValues(double* oscValues) {
	int numActive = 0;
	double sampleOutput = 0;
	for (int i = 0; i < 3; i++) {
		if (oscIsActive[i]) {
			numActive += 1;
			sampleOutput += oscValues[i] * levels[i];
		}
	}
	return sampleOutput / numActive;
}

void OscilatorMixer::setRelativeLevel(int oscilatorIndex, double level) {
	levels[oscilatorIndex] = level;
}

void OscilatorMixer::setOscilatorIsActive(int oscilatorIndex, bool isActive) {
	oscIsActive[oscilatorIndex] = isActive;
}

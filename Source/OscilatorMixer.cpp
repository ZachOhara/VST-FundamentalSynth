#include "OscilatorMixer.h"

OscilatorMixer::OscilatorMixer() {
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		levels[i] = 1;
		oscIsActive[i] = true;
	}
}

double OscilatorMixer::mixValues(double* oscValues) {
	double level;
	double totalLevel = 0;
	double sampleOutput = 0;
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		if (oscIsActive[i]) {
			level = std::pow(levels[i], 1.5); // exponent determined experimentally, "sounds best"
			totalLevel += level;
			sampleOutput += oscValues[i] * level;
		}
	}
	if (totalLevel == 0) {
		return 0;
	} else {
		return sampleOutput / totalLevel;
	}
}

void OscilatorMixer::setRelativeLevel(int oscilatorIndex, double level) {
	levels[oscilatorIndex] = level;
}

void OscilatorMixer::setOscilatorIsActive(int oscilatorIndex, bool isActive) {
	oscIsActive[oscilatorIndex] = isActive;
}

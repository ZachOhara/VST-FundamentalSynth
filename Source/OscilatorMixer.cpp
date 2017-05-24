#include "OscilatorMixer.h"

OscilatorMixer::OscilatorMixer() {
	
}

OscilatorMixer::~OscilatorMixer() {

}

double OscilatorMixer::mixValues(double* oscValues) {
	double level;
	double totalLevel = 0;
	double sampleOutput = 0;
	for (int i = 0; i < 3; i++) {
		if (oscIsActive[i]) {
			level = std::pow(levels[i], 1.5); // exponent determined experimentally, "sounds best"
			totalLevel += level;
			sampleOutput += oscValues[i] * level;
		}
	}
	return sampleOutput / totalLevel;
}

void OscilatorMixer::setRelativeLevel(int oscilatorIndex, double level) {
	levels[oscilatorIndex] = level;
}

void OscilatorMixer::setOscilatorIsActive(int oscilatorIndex, bool isActive) {
	oscIsActive[oscilatorIndex] = isActive;
}

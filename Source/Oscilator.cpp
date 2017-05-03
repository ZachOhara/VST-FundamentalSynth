#include "Oscilator.h"

Oscilator::Oscilator() {
	initSineTable();
}


Oscilator::~Oscilator() {
	// take no action
}

double Oscilator::getSampleValue(NoteOscilatorState& oscilatorState, double frequency, double time) {
	double phase = (frequency * time) + oscilatorState.phaseOffset;
	phase = phase - ((int) phase);
	oscilatorState.lastPhase = phase;
	//return AMPLITUDE_FACTOR * getSineFromTable(phase);
	return AMPLITUDE_FACTOR * std::sin(double_Pi * 2 * phase);
}

void Oscilator::prepareFrequencyChange(NoteOscilatorState & oscilatorState, double oldFrequency, double newFrequency, double time) {
	double nextPhase = (newFrequency * time);
	oscilatorState.phaseOffset = oscilatorState.lastPhase - nextPhase;
}

double Oscilator::getSineFromTable(double phase) {
	phase *= SINE_TABLE_SAMPLES;
	int index = (int) phase;
	double extra = std::floor(phase) - phase; // should be [0,1]
	double lowVal = sineWaveTable[index];
	double highVal;
	if (index < SINE_TABLE_SAMPLES - 1) {
		highVal = sineWaveTable[index + 1];
	} else {
		highVal = sineWaveTable[0];
	}
	double average = (lowVal * (1 - extra)) + (highVal * extra);
	return average;
}

void Oscilator::initSineTable() {
	for (int i = 0; i < SINE_TABLE_SAMPLES; i++) {
		sineWaveTable[i] = std::sin((double_Pi * 2) * (((double) i) / SINE_TABLE_SAMPLES));
	}
}

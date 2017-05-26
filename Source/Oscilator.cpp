#include "Oscilator.h"

Oscilator::Oscilator() {
	initSineTable();
}

double Oscilator::getSampleValue(double frequency, double time) {
	frequency *= currentOctave;
	double phase = (frequency * time);
	phase = phase - ((int) phase);
	return AMPLITUDE_FACTOR * getUnalteredValue(phase);
}

double Oscilator::getUnalteredValue(double phase) {
	switch (currentType) {
	case SINE:
		//return getSineFromTable(phase);
		return std::sin(double_Pi * 2 * phase);
	case TRIANGLE:
		return (4 * (std::abs(phase - 0.5))) - 1;
	case SAWTOOTH:
		return 2 * (phase - 0.5);
	case SQUARE:
		return phase < 0.5 ? 1 : -1;
	}
}

void Oscilator::setWaveType(WaveType newType) {
	currentType = newType;
}

void Oscilator::setOctaveOffset(int newOctave) {
	currentOctave = std::pow(2, newOctave);
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

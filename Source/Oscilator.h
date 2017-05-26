#ifndef OSCILATOR_OSCILATOR_H
#define OSCILATOR_OSCILATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

enum WaveType {
	SINE,
	TRIANGLE,
	SAWTOOTH,
	SQUARE,
};

class Oscilator {
public:
	Oscilator();

	double Oscilator::getSampleValue(double frequency, double time);
	void setWaveType(WaveType newType);
	void setOctaveOffset(int newOctave);

private:
	const double AMPLITUDE_FACTOR = 0.1;
	const int SINE_TABLE_SAMPLES = 100000;
	double sineWaveTable[100000];

	WaveType currentType = SINE;
	double currentOctave = 1;

	double getUnalteredValue(double phase);
	double getSineFromTable(double phase);
	void initSineTable();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscilator)
};

#endif // OSCILATOR_OSCILATOR_H

#ifndef OSCILATOR_OSCILATOR_H
#define OSCILATOR_OSCILATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

struct NoteOscilatorState {
	double phaseOffset = 0;
	double lastPhase = 0;
};

class Oscilator {
public:
	Oscilator();
	~Oscilator();

	double Oscilator::getSampleValue(NoteOscilatorState& oscilatorState,  double frequency, double time);
	void Oscilator::prepareFrequencyChange(NoteOscilatorState& oscilatorState, double oldFrequency, double newFrequency, double time);

private:
	const double AMPLITUDE_FACTOR = 0.1;
	const int SINE_TABLE_SAMPLES = 100000;
	double sineWaveTable[100000];

	double getSineFromTable(double phase);
	void initSineTable();
};

#endif // !OSCILATOR_OSCILATOR_H

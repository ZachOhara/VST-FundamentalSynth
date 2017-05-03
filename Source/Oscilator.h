#ifndef OSCILATOR_OSCILATOR_H
#define OSCILATOR_OSCILATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

class Oscilator {
public:
	Oscilator();
	~Oscilator();

	double Oscilator::getSampleValue(double frequency, double time);
	
private:
	const double AMPLITUDE_FACTOR = 0.1;
	const int SINE_TABLE_SAMPLES = 100000;
	double sineWaveTable[100000];

	double getSineFromTable(double phase);
	void initSineTable();
};

#endif // !OSCILATOR_OSCILATOR_H

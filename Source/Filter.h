#ifndef FILTER_H
#define FILTER_H

#include "../JuceLibraryCode/JuceHeader.h"

class Filter {
public:
	Filter();
	~Filter();

	double getNextOutput(double currentInput);

	void clearSamples();
	void setCutoff(double frequency);
	void setSampleRate(double frequency);

private:
	double cutoff = 0;
	double sampleRate;

	double x0, x1, x2, y1, y2;
	double b0, b1, b2, a1, a2;

	void recalculateCoeffs();
};

#endif // !FILTER_H

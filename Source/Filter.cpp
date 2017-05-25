#include "Filter.h"

Filter::Filter() {

}

Filter::~Filter() {

}

double Filter::getNextOutput(double currentInput) {
	// first, calculate the output
	x0 = currentInput;
	double y0 = (b0 * x0) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2);
	// next, shift the samples
	x2 = x1;
	x1 = x0;
	y2 = y1;
	y1 = y0;
	// finally, return
	return y0;
}

void Filter::clearSamples() {
	x0 = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

void Filter::setCutoff(double frequency) {
	cutoff = frequency;
	if (sampleRate != 0 && cutoff != 0) {
		recalculateCoeffs();
	}
}

void Filter::setSampleRate(double frequency) {
	sampleRate = frequency;
	if (sampleRate != 0 && cutoff != 0) {
		recalculateCoeffs();
	}
}

void Filter::recalculateCoeffs() {
	double c = 1 / std::tan(double_Pi * (cutoff / sampleRate));
	double c_squared = c * c;
	double d = c_squared + (c * std::pow(2, 0.5)) + 1;
	b0 = 1 / d;
	b1 = 2 / d;
	b2 = 1 / d;
	a1 = 2 * (1 - c_squared) / d;
	a2 = (c_squared - (c * std::pow(2, 0.5)) + 1) / d;
}

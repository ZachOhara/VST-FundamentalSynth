#include "Filter.h"

Filter::Filter() {

}

double Filter::getNextOutput(double currentInput) {
	double output = currentInput;
	for (int i = 0; i < order; i++) {
		output = calculateOrderOutput(orderStates[i], output);
	}
	if (isEnabled) {
		return (output * emphasis) + (currentInput * (1 - emphasis));
	} else {
		return currentInput;
	}
}

double Filter::calculateOrderOutput(FilterState& state, double currentInput) {
	// first, calculate the output
	state.x0 = currentInput;
	double y0 = (b0 * state.x0) + (b1 * state.x1) + (b2 * state.x2) - (a1 * state.y1) - (a2 * state.y2);
	// next, shift the samples
	state.x2 = state.x1;
	state.x1 = state.x0;
	state.y2 = state.y1;
	state.y1 = y0;
	// finally, return
	return y0;
}

void Filter::clearSamples() {
	for (int i = 0; i < sizeof(orderStates) / sizeof(orderStates[0]); i++) {
		clearFilterState(orderStates[i]);
	}
}

void Filter::clearFilterState(FilterState& state) {
	state.x0 = 0;
	state.x1 = 0;
	state.x2 = 0;
	state.y1 = 0;
	state.y2 = 0;
}

void Filter::setSampleRate(double frequency) {
	sampleRate = frequency;
	if (sampleRate != 0 && cutoff != 0) {
		recalculateCoeffs();
	}
}

void Filter::setCutoff(double frequency) {
	cutoff = frequency;
	if (sampleRate != 0 && cutoff != 0) {
		recalculateCoeffs();
	}
}

void Filter::setEmphasis(double newEmphasis) {
	emphasis = newEmphasis;
}

void Filter::setOrder(int newOrder) {
	order = newOrder;
}

void Filter::setIsEnabled(bool newIsEnabled) {
	isEnabled = newIsEnabled;
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

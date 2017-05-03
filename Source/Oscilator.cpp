#include "Oscilator.h"

Oscilator::Oscilator() {
	// take no action
}


Oscilator::~Oscilator() {
	// take no action
}

double Oscilator::getSampleValue(double frequency, double time) {
	return AMPLITUDE_FACTOR * std::sin(double_Pi * frequency * time);
}

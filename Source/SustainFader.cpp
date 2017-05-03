#include "SustainFader.h"

SustainFader::SustainFader() {
	setRange(0, 100, STEP_SIZE); // percent
	setTextValueSuffix("%");
	setValue(100);
}

SustainFader::~SustainFader() {
	// take no action
}

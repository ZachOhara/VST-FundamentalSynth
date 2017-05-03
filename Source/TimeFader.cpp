#include "TimeFader.h"

TimeFader::TimeFader() {
	setRange(MIN_VALUE, MAX_VALUE, STEP_SIZE);
	setTextValueSuffix("s");
}

TimeFader::~TimeFader() {
	// take no action
}

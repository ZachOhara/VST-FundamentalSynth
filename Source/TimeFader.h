#ifndef ENVELOPE_TIMEFADER_H_INCLUDED
#define ENVELOPE_TIMEFADER_H_INCLUDED

#include "EnvelopeFader.h"

class TimeFader :
	public EnvelopeFader {
public:
	TimeFader();
	~TimeFader();

	const double MAX_VALUE = 2.0; // seconds
	const double STEP_SIZE = 0.001; // seconds
	const double MIN_VALUE = 0.002; // seconds
};

#endif // !ENVELOPE_TIMEFADER_H_INCLUDED

#ifndef ENVELOPE_SUSTAINFADER_H_INCLUDED
#define ENVELOPE_SUSTAINFADER_H_INCLUDED

#include "EnvelopeFader.h"

class SustainFader :
	public EnvelopeFader {
public:
	SustainFader();
	~SustainFader();

	const double STEP_SIZE = 1; // percent
};

#endif // !ENVELOPE_SUSTAINFADER_H_INCLUDED

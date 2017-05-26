#ifndef FILTER_H
#define FILTER_H

#include "../JuceLibraryCode/JuceHeader.h"

struct FilterState {
	double x0, x1, x2, y1, y2;
};

class Filter {
public:
	Filter();
	~Filter();

	double getNextOutput(double currentInput);

	void clearSamples();
	void setSampleRate(double frequency);
	void setCutoff(double frequency);
	void setEmphasis(double newEmphasis);
	void setOrder(int newOrder);
	void setIsEnabled(bool newIsEnabled);

private:
	double cutoff = 0;
	double sampleRate;
	double emphasis;
	int order;
	bool isEnabled;

	FilterState orderStates[3];

	double b0, b1, b2, a1, a2;

	double calculateOrderOutput(FilterState& state, double currentInput);
	void clearFilterState(FilterState& state);
	void recalculateCoeffs();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};

#endif // !FILTER_H

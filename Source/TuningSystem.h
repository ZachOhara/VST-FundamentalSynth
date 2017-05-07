#ifndef TUNINGSYSTEM_H
#define TUNINGSYSTEM_H

#include "../JuceLibraryCode/JuceHeader.h"

enum tuningMode {
	EQUAL_TEMPERAMENT,
	JUST_TEMPERAMENT
};

class TuningSystem {
public:
	TuningSystem();
	~TuningSystem();

	double getFrequency(int midiNote);

	void setTuningMode(tuningMode newMode);
	void setKey(int semitonesAboveA);

private:
	const int MIDDLE_A = 57;
	const double MIDDLE_A_TUNING = 440.0;

	const int JUSTIFIED_RATIOS[11][2] = {
		{16, 15}, {9, 8}, {6, 5}, {5, 4}, {4, 3}, 
		{45, 32}, {3, 2}, {8, 5}, {5, 3}, {9, 5}, {15, 8}
	};

	double standardEqualMap[128];
	double justifiedKeyMaps[12][128];

	tuningMode currentMode = JUST_TEMPERAMENT;
	int currentModeKey = 0;

	void initStandardEqual();
	void initJustified(int key);
};

#endif // !TUNINGSYSTEM_H

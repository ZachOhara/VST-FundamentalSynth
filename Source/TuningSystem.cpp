#include "TuningSystem.h"

TuningSystem::TuningSystem() {
	initStandardEqual();
	for (int i = 0; i < 12; i++) {
		initJustified(i);
	}
}

TuningSystem::~TuningSystem() {
	// take no action
}

double TuningSystem::getFrequency(int midiNote) {
	switch (currentMode) {
	case EQUAL_TEMPERAMENT:
		return standardEqualMap[midiNote];
	case JUST_TEMPERAMENT:
		return justifiedKeyMaps[currentModeKey][midiNote];
	default:
		return 0;
	}
}

void TuningSystem::setTuningMode(tuningMode newMode) {
	currentMode = newMode;
}

void TuningSystem::initStandardEqual() {
	standardEqualMap[MIDDLE_A] = MIDDLE_A_TUNING; // tuning A4 = 440hz

	for (int i = MIDDLE_A - 1; i >= 0; i--) {
		standardEqualMap[i] = standardEqualMap[57] / std::pow(2, (57 - i) / 12.0);
	}
	for (int i = MIDDLE_A + 1; i <= 127; i++) {
		standardEqualMap[i] = standardEqualMap[57] * std::pow(2, (i - 57) / 12.0);
	}
}

void TuningSystem::initJustified(int key) {
	const int keyCenter = MIDDLE_A + key;
	// base the tonic off of the equal temperament tuning
	justifiedKeyMaps[key][keyCenter] = standardEqualMap[keyCenter];

	for (int i = 0; i < 11; i++) {
		justifiedKeyMaps[key][keyCenter + i + 1] = justifiedKeyMaps[key][keyCenter]
			* JUSTIFIED_RATIOS[i][0] / JUSTIFIED_RATIOS[i][1];
	}
	
	int octaveOffset = 0;
	for (int i = keyCenter - 1; i >= 0; i--) {
		while (i + (12 * octaveOffset) < keyCenter) {
			octaveOffset += 1;
		}
		justifiedKeyMaps[key][i] = justifiedKeyMaps[key][i + (12 * octaveOffset)] / std::pow(2, octaveOffset);
	}
	octaveOffset = 0;
	for (int i = keyCenter + 12; i <= 127; i++) {
		while (i - (12 * octaveOffset) > keyCenter + 11) {
			octaveOffset += 1;
		}
		justifiedKeyMaps[key][i] = justifiedKeyMaps[key][i - (12 * octaveOffset)] * std::pow(2, octaveOffset);
	}
	
	/*
	int octave;
	for (int i = keyCenter - 1; i >= 0; i--) {
		octave = (int) ((MIDDLE_A - i) / 12);
		justifiedKeyMaps[key][i] = justifiedKeyMaps[key][i + (12 * octave)] / std::pow(2, octave);
	}
	for (int i = keyCenter + 12; i <= 127; i++) {
		octave = (int) ((i - (MIDDLE_A + 11)) / 12);
		justifiedKeyMaps[key][i] = justifiedKeyMaps[key][i - (12* octave)] * std::pow(2, octave);
	}
	*/
}


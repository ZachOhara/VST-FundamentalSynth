#ifndef SETTINGSPROCESSOR_H
#define SETTINGSPROCESSOR_H

enum SynthMode {
	POLYPHONIC,
	MONOPHONIC,
};

class SettingsProcessor {
public:
	SettingsProcessor();

	SynthMode getCurrentMode();
	void setNewMode(SynthMode newMode);

	double getMasterVolume();
	void setMasterVolume(double newVolume);

private:
	SynthMode currentMode = POLYPHONIC;
	double masterVolume = 1;
};

#endif // SETTINGSPROCESSOR_H

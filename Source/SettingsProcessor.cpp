#include "SettingsProcessor.h"

SettingsProcessor::SettingsProcessor() {

}

SynthMode SettingsProcessor::getCurrentMode() {
	return currentMode;
}

void SettingsProcessor::setNewMode(SynthMode newMode) {
	currentMode = newMode;
}

double SettingsProcessor::getMasterVolume() {
	return masterVolume;
}

void SettingsProcessor::setMasterVolume(double newVolume) {
	masterVolume = newVolume;
}

#include "MasterVolume.h"

MasterVolumeProcessor::MasterVolumeProcessor() {

}

double MasterVolumeProcessor::attenuate(double value) {
	return value * masterVolume;
}

void MasterVolumeProcessor::setMasterVolume(double newVolume) {
	masterVolume = newVolume;
}

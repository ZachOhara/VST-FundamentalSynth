#ifndef MASTERVOLUME_H
#define MASTERVOLUME_H

class MasterVolumeProcessor {
public:
	MasterVolumeProcessor();

	double attenuate(double value);

	void setMasterVolume(double newVolume);

private:
	double masterVolume = 1;
};

#endif // MASTERVOLUME_H

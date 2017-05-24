#ifndef OSCILATORMIXER_H
#define OSCILATORMIXER_H

class OscilatorMixer {
public:
	OscilatorMixer();
	~OscilatorMixer();

	double mixValues(double* oscValues);

	void setRelativeLevel(int oscilatorIndex, double level);
	void setOscilatorIsActive(int oscilatorIndex, bool isActive);

private:
	double levels[3] = {1, 1, 1};
	bool oscIsActive[3] = {true, false, false};
};

#endif // !OSCILATORMIXER_H

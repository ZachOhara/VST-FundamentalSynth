#include "FundamentalSynthesizer.h"

FundamentalSynthesizer::FundamentalSynthesizer() {
	secondsPerSample = 0;
}

FundamentalSynthesizer::~FundamentalSynthesizer() {
	// take no action
}

void FundamentalSynthesizer::prepareToPlay(double sampleRate, int samplesPerBlock) {
	secondsPerSample = 1 / sampleRate;
	secondsPerBlock = secondsPerSample * samplesPerBlock;
	currentTime = 0;
	currentBlockTime = 0;
	currentSamplesPerBlock = samplesPerBlock;
	sampleBuffer = (double*) malloc(sizeof(double) * samplesPerBlock);

	filter.setSampleRate(sampleRate);
	filter.setCutoff(1000);
	envelopeProcessor.setSecondsPerSample(secondsPerSample);
}

void FundamentalSynthesizer::freeResources() {
	filter.clearSamples();
	free(sampleBuffer);
}

void FundamentalSynthesizer::processBlock(AudioSampleBuffer& audioBuffer, MidiBuffer& midiBuffer) {
	currentBlockTime += secondsPerBlock;
	currentTime = currentBlockTime;

	processMidiMessages(midiBuffer);
	synthesizeAudio();

	float* const bufferLeft = audioBuffer.getWritePointer(0);
	float* const bufferRight = audioBuffer.getWritePointer(1);

	for (int i = 0; i < currentSamplesPerBlock; i++) {
		bufferLeft[i] = (float) sampleBuffer[i];
		bufferRight[i] = (float) sampleBuffer[i];
		sampleBuffer[i] = 0; // free for next block
	}
}

void FundamentalSynthesizer::processMidiMessages(MidiBuffer& midiBuffer) {
	MidiMessage message;
	int time;
	for (MidiBuffer::Iterator i(midiBuffer); i.getNextEvent(message, time);) {
		int noteValue = message.getNoteNumber();
		double seconds = time * secondsPerSample;
		if (message.isNoteOn()) {
			keyboardNotes[noteValue].beginNote(envelopeProcessor, -seconds);
		} else if (message.isNoteOff()) {
			// if pedal is not on...
			if (!isPedalOn) {
				// ...release the note
				keyboardNotes[noteValue].releaseNote(envelopeProcessor, -seconds);
			} else {
				// else, mark the note as pedaled
				keyboardNotes[noteValue].pedalState = PEDALED;
			}
		} else if (message.isPitchWheel()) {
			pitchBendProcessor.setModWheelValue(message.getPitchWheelValue());
		} else if (message.isSustainPedalOff()) {
			isPedalOn = true;
		} else if (message.isSustainPedalOn()) {
			isPedalOn = false;
			for (int i = 0; i < 128; i++) {
				if (keyboardNotes[i].pedalState == PEDALED) {
					keyboardNotes[i].releaseNote(envelopeProcessor, -seconds);
				}
			}
		}
	}
}

void FundamentalSynthesizer::synthesizeAudio() {

	for (int sample = 0; sample < currentSamplesPerBlock; sample++) {
		for (int i = 0; i < 128; i++) {
			if (keyboardNotes[i].isNotePlaying) {		

				// get the frequency in the current tuning system
				double frequency = tuningMap.getFrequency(i);
				frequency = pitchBendProcessor.getBentFrequency(frequency);

				// mix the oscilators
				double oscilators[3] = {
					oscilator1.getSampleValue(frequency, currentTime),
					oscilator2.getSampleValue(frequency, currentTime),
					oscilator3.getSampleValue(frequency, currentTime),
				};
				double sampleValue = mixer.mixValues(oscilators);
				
				// filter it
				sampleValue = filter.getNextOutput(sampleValue);

				// write to the current sample
				sampleBuffer[sample] += sampleValue
					* envelopeProcessor.getVolumeAfterTime(keyboardNotes[i].envelopeState);

				// check if note is finished releasing
				if (envelopeProcessor.isFinishedReleasing(keyboardNotes[i].envelopeState)) {
					keyboardNotes[i].isNotePlaying = false;
				}
			}
		}
		currentTime += secondsPerSample;
	}
}

EnvelopeProcessor& FundamentalSynthesizer::getEnvelopeProcessor() {
	return envelopeProcessor;
}

TuningSystem& FundamentalSynthesizer::getTuningProcessor() {
	return tuningMap;
}

Oscilator& FundamentalSynthesizer::getOscilator1() {
	return oscilator1;
}

Oscilator& FundamentalSynthesizer::getOscilator2() {
	return oscilator2;
}

Oscilator& FundamentalSynthesizer::getOscilator3() {
	return oscilator3;
}

OscilatorMixer& FundamentalSynthesizer::getMixer() {
	return mixer;
}

Filter& FundamentalSynthesizer::getFilter() {
	return filter;
}

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

	envelopeProcessor.setSecondsPerSample(secondsPerSample);
}

void FundamentalSynthesizer::freeResources() {
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
		if (message.isNoteOn()) {
			keyboardNotes[noteValue].isNotePlaying = true;
			keyboardNotes[noteValue].envelopeState.runningTime = -time * secondsPerSample;
			envelopeProcessor.beginNote(keyboardNotes[noteValue].envelopeState);
		} else if (message.isNoteOff()) {
			envelopeProcessor.releaseNote(keyboardNotes[noteValue].envelopeState);
			keyboardNotes[noteValue].envelopeState.runningTime = -time * secondsPerSample;
		} else if (message.isPitchWheel()) {
			pitchBendProcessor.setModWheelValue(message.getPitchWheelValue());
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

				// write to the current sample
				sampleBuffer[sample] += oscilator.getSampleValue(frequency, currentTime)
					* envelopeProcessor.getVolumeAfterTime(keyboardNotes[i].envelopeState);
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

#include "FundamentalSynthesizer.h"

FundamentalSynthesizer::FundamentalSynthesizer() {
	secondsPerSample = 0;
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
	for (MidiBuffer::Iterator iterator(midiBuffer); iterator.getNextEvent(message, time);) {
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
		for (int note = 0; note < 128; note++) {
			if (keyboardNotes[note].isNotePlaying) {		

				// get the frequency in the current tuning system
				double frequency = tuningProcessor.getFrequency(note);
				frequency = pitchBendProcessor.getBentFrequency(frequency);

				// get values from the oscilators
				double oscilatorValues[SYNTH_NUM_OSCILATORS];
				for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
					oscilatorValues[i] = oscilators[i].getSampleValue(frequency, currentTime);
				}

				// mix the oscilators
				double sampleValue = mixer.mixValues(oscilatorValues);
				
				// filter it
				sampleValue = filter.getNextOutput(sampleValue);

				// apply envelope
				sampleValue *= envelopeProcessor.getVolumeAfterTime(keyboardNotes[note].envelopeState);

				// apply master volume
				sampleValue = masterVolume.attenuate(sampleValue);

				// write to the current sample
				sampleBuffer[sample] += sampleValue;

				// check if note is finished releasing
				if (envelopeProcessor.isFinishedReleasing(keyboardNotes[note].envelopeState)) {
					keyboardNotes[note].isNotePlaying = false;
				}
			}
		}
		currentTime += secondsPerSample;
	}
}

SynthProcessorSet FundamentalSynthesizer::getInterfaceProcessors() {
	SynthProcessorSet synth;
	synth.tuning = &tuningProcessor;
	synth.oscilatorArray = oscilators;
	synth.mixer = &mixer;
	synth.filter = &filter;
	synth.envelope = &envelopeProcessor;
	synth.master = &masterVolume;
	return synth;
}

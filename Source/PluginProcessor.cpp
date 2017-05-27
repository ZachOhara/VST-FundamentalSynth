#include "PluginProcessor.h"
#include "FundamentalSynthesizerEditor.h"

FSynthAudioProcessor::FSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	
}

const String FSynthAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool FSynthAudioProcessor::acceptsMidi() const {
	return true;
}

bool FSynthAudioProcessor::producesMidi() const {
	return false;
}

double FSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int FSynthAudioProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FSynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void FSynthAudioProcessor::setCurrentProgram (int index) {
	// take no action
}

const String FSynthAudioProcessor::getProgramName (int index) {
    return String();
}

void FSynthAudioProcessor::changeProgramName (int index, const String& newName) {
	
}

void FSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
	fundamentalSynthesizer.prepareToPlay(sampleRate, samplesPerBlock);
}

void FSynthAudioProcessor::releaseResources() {
	fundamentalSynthesizer.freeResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FSynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    // this may be important- leaving it here if it is
	/*
	const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	*/

	fundamentalSynthesizer.processBlock(buffer, midiMessages);
}

bool FSynthAudioProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor* FSynthAudioProcessor::createEditor() {
	return new FundamentalSynthesizerEditor(*this, fundamentalSynthesizer.getInterfaceProcessors());
}

void FSynthAudioProcessor::getStateInformation (MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FSynthAudioProcessor();
}

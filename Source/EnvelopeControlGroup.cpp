#include "EnvelopeControlGroup.h"

EnvelopeControlGroup::EnvelopeControlGroup(String name, String label, EnvelopeProcessor& envelope) :
	Component() {

	envelopeProcessor = &envelope;

	setSize(envelopeControlSpacing.necessaryTotalWidth, envelopeControlSpacing.necessaryTotalHeight);

	groupOutline = new GroupComponent(name, label);

	groupOutline->setText(label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	groupOutline->setBounds(0, 0, envelopeControlSpacing.necessaryTotalWidth, envelopeControlSpacing.necessaryTotalHeight);
	addAndMakeVisible(groupOutline);

	addAndMakeVisible(envelopeAttackFader);
	envelopeAttackFader.addListener(this);
	addAndMakeVisible(envelopeAttackLabel);
	envelopeAttackLabel.setText("Attack", dontSendNotification);
	envelopeAttackLabel.attachToComponent(&envelopeAttackFader, false);

	addAndMakeVisible(envelopeDecayFader);
	envelopeDecayFader.addListener(this);
	addAndMakeVisible(envelopeDecayLabel);
	envelopeDecayLabel.setText("Decay", dontSendNotification);
	envelopeDecayLabel.attachToComponent(&envelopeDecayFader, false);

	addAndMakeVisible(envelopeSustainFader);
	envelopeSustainFader.addListener(this);
	addAndMakeVisible(envelopeSustainLabel);
	envelopeSustainLabel.setText("Sustain", dontSendNotification);
	envelopeSustainLabel.attachToComponent(&envelopeSustainFader, false);

	addAndMakeVisible(envelopeReleaseFader);
	envelopeReleaseFader.addListener(this);
	addAndMakeVisible(envelopeReleaseLabel);
	envelopeReleaseLabel.setText("Release", dontSendNotification);
	envelopeReleaseLabel.attachToComponent(&envelopeReleaseFader, false);

	// Buttons
	addAndMakeVisible(modeButtonsLabel);
	modeButtonsLabel.setText("Scaling Mode:", dontSendNotification);

	String modes[3] = {"Linear", "Exponential", "Logarithmic"};
	modeButtonSet = new RadioButtonSet(this, modes, 3);
	addAndMakeVisible(modeButtonSet);
	modeButtonSet->setBounds(envelopeControlSpacing.buttonsLeftOffset,
		envelopeControlSpacing.buttonsTopOffset,
		envelopeControlSpacing.buttonLabelsWidth,
		modeButtonSet->getNecessaryHeight());

	// TODO find a better way to set defaults than hard-coding
	
	// set default scaling method
	modeButtonSet->triggerClick(2); // default == logarithmic
	// set default ADSR times (this is a horrible hack)
	sliderValueChanged(&envelopeAttackFader);
	sliderValueChanged(&envelopeDecayFader);
	sliderValueChanged(&envelopeSustainFader);
	sliderValueChanged(&envelopeReleaseFader);
}

EnvelopeControlGroup::~EnvelopeControlGroup() {
	delete groupOutline;
}

void EnvelopeControlGroup::selectionChanged(String & newSelection) {
	if (newSelection == "Linear") {
		envelopeProcessor->setScalingMode(LINEAR);
	} else if (newSelection == "Exponential") {
		envelopeProcessor->setScalingMode(EXPONENTIAL);
	} else if (newSelection == "Logarithmic") {
		envelopeProcessor->setScalingMode(LOGARITHMIC);
	}
}

void EnvelopeControlGroup::sliderValueChanged(Slider* slider) {
	if (slider == &envelopeAttackFader) {
		envelopeProcessor->setAttackTime(envelopeAttackFader.getValue());
	} else if (slider == &envelopeDecayFader) {
		envelopeProcessor->setDecayTime(envelopeDecayFader.getValue());
	} else if (slider == &envelopeSustainFader) {
		envelopeProcessor->setSustainLevel(envelopeSustainFader.getValue() / 100);
	} else if (slider == &envelopeReleaseFader) {
		envelopeProcessor->setReleaseTime(envelopeReleaseFader.getValue());
	}
}

void EnvelopeControlGroup::paint(Graphics& g) {
	//g.fillAll(Colours::darkred);
}


void EnvelopeControlGroup::resized() {
	envelopeAttackFader.setBounds(envelopeControlSpacing.envelopeLeftOffset, envelopeControlSpacing.envelopeTopOffset, envelopeControlSpacing.envelopeFaderWidth, envelopeControlSpacing.envelopeFaderHeight);
	envelopeDecayFader.setBounds(envelopeControlSpacing.envelopeLeftOffset + (1 * envelopeControlSpacing.envelopeSideSpace), envelopeControlSpacing.envelopeTopOffset, envelopeControlSpacing.envelopeFaderWidth, envelopeControlSpacing.envelopeFaderHeight);
	envelopeSustainFader.setBounds(envelopeControlSpacing.envelopeLeftOffset + (2 * envelopeControlSpacing.envelopeSideSpace), envelopeControlSpacing.envelopeTopOffset, envelopeControlSpacing.envelopeFaderWidth, envelopeControlSpacing.envelopeFaderHeight);
	envelopeReleaseFader.setBounds(envelopeControlSpacing.envelopeLeftOffset + (3 * envelopeControlSpacing.envelopeSideSpace), envelopeControlSpacing.envelopeTopOffset, envelopeControlSpacing.envelopeFaderWidth, envelopeControlSpacing.envelopeFaderHeight);

	// Buttons
	modeButtonsLabel.setBounds(envelopeControlSpacing.modeLabelLeftOffset, envelopeControlSpacing.modeLabelTopOffset, envelopeControlSpacing.modeLabelWidth, envelopeControlSpacing.modeLabelHeight);
	/*
	linearModeButton.setBounds(envelopeControlSpacing.buttonsLeftOffset, envelopeControlSpacing.buttonsTopOffset, envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsHeight);
	linearModeLabel.setBounds(envelopeControlSpacing.buttonsLeftOffset + envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsTopOffset, envelopeControlSpacing.buttonLabelsWidth, envelopeControlSpacing.buttonsHeight);
	exponentialModeButton.setBounds(envelopeControlSpacing.buttonsLeftOffset, envelopeControlSpacing.buttonsTopOffset + (1 * envelopeControlSpacing.buttonsVerticalSpace), envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsHeight);
	exponentialModeLabel.setBounds(envelopeControlSpacing.buttonsLeftOffset + envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsTopOffset + (1 * envelopeControlSpacing.buttonsVerticalSpace), envelopeControlSpacing.buttonLabelsWidth, envelopeControlSpacing.buttonsHeight);
	logarithmicModeButton.setBounds(envelopeControlSpacing.buttonsLeftOffset, envelopeControlSpacing.buttonsTopOffset + (2 * envelopeControlSpacing.buttonsVerticalSpace), envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsHeight);
	logarithmicModeLabel.setBounds(envelopeControlSpacing.buttonsLeftOffset + envelopeControlSpacing.buttonsWidth, envelopeControlSpacing.buttonsTopOffset + (2 * envelopeControlSpacing.buttonsVerticalSpace), envelopeControlSpacing.buttonLabelsWidth, envelopeControlSpacing.buttonsHeight);
	*/
}

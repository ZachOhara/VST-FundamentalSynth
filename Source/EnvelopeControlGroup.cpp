#include "EnvelopeControlGroup.h"

EnvelopeControlGroup::EnvelopeControlGroup(EnvelopeProcessor* envelope) :
	Component() {
	setSize(WIDTH, HEIGHT);
	envelopeProcessor = envelope;

	// Buttons
	modeLabel = new Label();
	modeLabel->setText("Mode:", dontSendNotification);
	modeLabel->setTopLeftPosition(30, 40);
	modeLabel->setSize(100, 20);
	addAndMakeVisible(modeLabel);

	String modes[3] = {"Linear", "Exponential", "Logarithmic"};
	modeButtonSet = new RadioButtonSet(this, modes, 3);
	modeButtonSet->setTopLeftPosition(85, 22);
	modeButtonSet->setSize(120, modeButtonSet->getNecessaryHeight());
	addAndMakeVisible(modeButtonSet);

	// Sliders
	// 50px space between
	initializeElement(attack, "Attack (ms)", 90, 2, 2000, 1, 2, true);
	initializeElement(decay, "Decay (ms)", 140, 2, 2000, 1, 2, true);
	initializeElement(sustain, "Sustain (%)", 190, 0, 100, 1, 100, false);
	initializeElement(release, "Release (ms)", 240, 2, 2000, 1, 2, true);

	// TODO find a better way to set defaults than hard-coding
	modeButtonSet->triggerClick(2); // default == logarithmic
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
	if (slider == attack.slider) {
		envelopeProcessor->setAttackTime(attack.slider->getValue() / 1000);
	} else if (slider == decay.slider) {
		envelopeProcessor->setDecayTime(decay.slider->getValue() / 1000);
	} else if (slider == sustain.slider) {
		envelopeProcessor->setSustainLevel(sustain.slider->getValue() / 100);
		// yes, this should be 100, unlike the others
	} else if (slider == release.slider) {
		envelopeProcessor->setReleaseTime(release.slider->getValue() / 1000);
	}
}

void EnvelopeControlGroup::initializeElement(EnvelopeSlider& element, String name,
	int yPos, double min, double max, double step, double start, bool skew) {
	element.label = new Label();
	element.label->setText(name, dontSendNotification);
	element.label->setSize(150, 20);
	element.label->setTopLeftPosition(10, yPos);
	addAndMakeVisible(element.label);

	element.slider = new Slider();
	element.slider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
	element.slider->setTextValueSuffix("");
	element.slider->addListener(this);
	element.slider->setRange(min, max, step);
	if (skew) {
		element.slider->setSkewFactorFromMidPoint(300);
	}
	element.slider->setValue(start);
	element.slider->setSize(180, 20);
	element.slider->setTopLeftPosition(10, yPos + 20);
	addAndMakeVisible(element.slider);

	// TODO better defaults
	sliderValueChanged(element.slider);
}

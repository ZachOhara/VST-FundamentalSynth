#include "NoiseOscilatorControlGroup.h"

NoiseOscilatorControlGroup::NoiseOscilatorControlGroup(NoiseOscilator* processor) {
	setSize(WIDTH, HEIGHT);
	oscilator = processor;

	oscilatorEnabledButton = new ToggleButton();
	oscilatorEnabledButton->addListener(this);
	oscilatorEnabledButton->setSize(20, 20);
	oscilatorEnabledButton->setTopLeftPosition(15, 25);
	addAndMakeVisible(oscilatorEnabledButton);

	oscilatorEnabledLabel = new Label();
	oscilatorEnabledLabel->setText("Enabled", dontSendNotification);
	oscilatorEnabledLabel->setSize(100, 20);
	oscilatorEnabledLabel->setTopLeftPosition(35, 25);
	addAndMakeVisible(oscilatorEnabledLabel);

	String noisetypes[2] = {"White", "Pink"};
	noiseTypeButtonSet = new RadioButtonSet(this, noisetypes, 2);
	noiseTypeButtonSet->setTopLeftPosition(100, 25);
	noiseTypeButtonSet->setSize(120, noiseTypeButtonSet->getNecessaryHeight());
	addAndMakeVisible(noiseTypeButtonSet);

	volumeLabel = new Label();
	volumeLabel->setText("Volume", dontSendNotification);
	volumeLabel->setTopLeftPosition(30, 75);
	volumeLabel->setSize(100, 20);
	addAndMakeVisible(volumeLabel);

	volumeSlider = new Slider();
	volumeSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	volumeSlider->addListener(this);
	volumeSlider->setRange(0, 1, 0);
	volumeSlider->setValue(1);
	volumeSlider->setTopLeftPosition(10, 95);
	volumeSlider->setSize(180, 20);
	addAndMakeVisible(volumeSlider);
}

void NoiseOscilatorControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "White") {
		oscilator->setNoiseType(WHITE);
	} else if (newSelection == "Pink") {
		oscilator->setNoiseType(PINK);
	}
}

void NoiseOscilatorControlGroup::buttonClicked(Button* clicked) {
	if (clicked == oscilatorEnabledButton) {
		oscilator->setIsActive(oscilatorEnabledButton->getToggleState());
	}
}

void NoiseOscilatorControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == volumeSlider) {
		oscilator->setLevel(volumeSlider->getValue());
	}
}

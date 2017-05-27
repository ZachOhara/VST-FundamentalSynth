#include "TuningControlGroup.h"

TuningControlGroup::TuningControlGroup(TuningProcessor* processor) {
	setSize(WIDTH, HEIGHT);
	tuningProcessor = processor;
	
	String modes[2] = {"Equal Temperament", "Just Temperament"};
	modeButtonSet = new RadioButtonSet(this, modes, 2);
	modeButtonSet->setTopLeftPosition(BUTTONS_LEFT_OFFSET, BUTTONS_TOP_OFFSET);
	modeButtonSet->setSize(WIDTH - BUTTONS_LEFT_OFFSET, modeButtonSet->getNecessaryHeight());
	addAndMakeVisible(modeButtonSet);

	keySlider = new Slider();
	keySlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	keySlider->addListener(this);
	keySlider->setTopLeftPosition(40, 70);
	keySlider->setSize(150, 20);
	keySlider->setRange(0, 11, 1);
	keySlider->setValue(3);
	addAndMakeVisible(keySlider);

	keyLabel = new Label();
	keyLabel->setText("A", dontSendNotification);
	keyLabel->attachToComponent(keySlider, true);
	addAndMakeVisible(keyLabel);
}

void TuningControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "Equal Temperament") {
		tuningProcessor->setTuningMode(EQUAL_TEMPERAMENT);
	} else if (newSelection == "Just Temperament") {
		tuningProcessor->setTuningMode(JUST_TEMPERAMENT);
	}
}

void TuningControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == keySlider) {
		static const String keys[12] = {"A", "A#", "B", "C", "C#",
			"D", "D#", "E", "F", "F#", "G", "G#"};
		int newKey = (int) keySlider->getValue();
		keyLabel->setText(keys[newKey], dontSendNotification);
		tuningProcessor->setKey(newKey);
	}
}

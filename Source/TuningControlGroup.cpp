#include "TuningControlGroup.h"

TuningControlGroup::TuningControlGroup(String name, String label, TuningSystem& processor) {
	tuningProcessor = &processor;

	setSize(WIDTH, HEIGHT);
	
	String modes[2] = {"Equal Temperament", "Just Temperament"};
	modeButtonSet = new RadioButtonSet(this, modes, 2);
	addAndMakeVisible(modeButtonSet);
	modeButtonSet->setBounds(BUTTONS_LEFT_OFFSET, BUTTONS_TOP_OFFSET,
		WIDTH - BUTTONS_LEFT_OFFSET,
		modeButtonSet->getNecessaryHeight());

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

	groupOutline = new GroupComponent(name, label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	addAndMakeVisible(groupOutline);
	groupOutline->setTopLeftPosition(0, 0);
	groupOutline->setSize(getWidth(), getHeight());
}

void TuningControlGroup::selectionChanged(String& newSelection) {
	if (newSelection == "Equal Temperament") {
		tuningProcessor->setTuningMode(EQUAL_TEMPERAMENT);
	} else if (newSelection == "Just Temperament") {
		tuningProcessor->setTuningMode(JUST_TEMPERAMENT);
	}
}

void TuningControlGroup::sliderValueChanged(Slider* changed) {
	static const String keys[12] = {"A", "A#", "B", "C", "C#",
		"D", "D#", "E", "F", "F#", "G", "G#"};
	int newKey = (int) keySlider->getValue();
	keyLabel->setText(keys[newKey], dontSendNotification);
	tuningProcessor->setKey(newKey);
}

void TuningControlGroup::resized() {

}

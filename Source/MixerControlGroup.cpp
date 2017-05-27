#include "MixerControlGroup.h"

MixerControlGroup::MixerControlGroup(OscilatorMixer* processor) {

	setSize(WIDTH, HEIGHT);
	mixer = processor;

	// for reference, the panels for each oscilator are at the following y-pos:
	// osc1: 25
	// osc2: 175
	// osc3: 325
	// coordinates are relative to window, so subtract 25 to get relative to this
	// height of each is 125 without external spacing

	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		initializeOscilatorControl(controls[i], i + 1, 40 + (150 * i));
		// TODO: figure out a better way of loading defaults
		controls[i].activeButton->triggerClick();
		sliderValueChanged(controls[i].levelSlider);
	}
}

void MixerControlGroup::initializeOscilatorControl(OscilatorControl & osc, int oscNum, int yPos) {
	osc.activeButton = new ToggleButton();
	osc.activeButton->addListener(this);
	osc.activeButton->setTopLeftPosition(20, yPos);
	osc.activeButton->setSize(20, 20);
	addAndMakeVisible(osc.activeButton);

	osc.label = new Label();
	String name = "Oscilator ";
	name << oscNum;
	osc.label->setText(name, dontSendNotification);
	osc.label->setTopLeftPosition(40, yPos);
	osc.label->setSize(100, 20);
	addAndMakeVisible(osc.label);

	osc.levelSlider = new Slider();
	osc.levelSlider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	osc.levelSlider->addListener(this);
	osc.levelSlider->setRange(0, 1, 0);
	osc.levelSlider->setValue(1);
	osc.levelSlider->setTopLeftPosition(10, yPos + 30);
	osc.levelSlider->setSize(180, 20);
	addAndMakeVisible(osc.levelSlider);
}

void MixerControlGroup::sliderValueChanged(Slider* changed) {
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		if (changed == controls[i].levelSlider) {
			mixer->setRelativeLevel(i, controls[i].levelSlider->getValue());
		}
	}
}

void MixerControlGroup::buttonClicked(Button* clicked) {
	for (int i = 0; i < SYNTH_NUM_OSCILATORS; i++) {
		if (clicked == controls[i].activeButton) {
			mixer->setOscilatorIsActive(i, controls[i].activeButton->getToggleState());
		}
	}
}

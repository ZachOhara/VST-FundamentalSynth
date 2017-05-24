#include "MixerControlGroup.h"

MixerControlGroup::MixerControlGroup(String name, String label, OscilatorMixer& mixer) {
	baseMixer = &mixer;

	setSize(WIDTH, HEIGHT);

	// for reference, the panels for each oscilator are at the following y-pos:
	// osc1: 25
	// osc2: 175
	// osc3: 325
	// coordinates are relative to window, so subtract 25 to get relative to this
	// height of each is 125 without external spacing


	// oscilator 1 controls
	osc1active = new ToggleButton();
	osc1active->addListener(this);
	osc1active->setSize(20, 20);
	osc1active->setTopLeftPosition(20, 40);
	addAndMakeVisible(osc1active);

	osc1label = new Label();
	osc1label->setText("Oscilator 1", dontSendNotification);
	osc1label->setTopLeftPosition(40, 40);
	osc1label->setSize(100, 20);
	addAndMakeVisible(osc1label);

	osc1level = new Slider();
	osc1level->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	osc1level->addListener(this);
	osc1level->setRange(0, 1, 0.0001);
	osc1level->setValue(1);
	osc1level->setTopLeftPosition(10, 70);
	osc1level->setSize(180, 20);
	addAndMakeVisible(osc1level);

	// oscilator 2 controls
	osc2active = new ToggleButton();
	osc2active->addListener(this);
	osc2active->setSize(20, 20);
	osc2active->setTopLeftPosition(20, 190);
	addAndMakeVisible(osc2active);

	osc2label = new Label();
	osc2label->setText("Oscilator 2", dontSendNotification);
	osc2label->setTopLeftPosition(40, 190);
	osc2label->setSize(100, 20);
	addAndMakeVisible(osc2label);

	osc2level = new Slider();
	osc2level->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	osc2level->addListener(this);
	osc2level->setRange(0, 1, 0.0001);
	osc2level->setValue(1);
	osc2level->setTopLeftPosition(10, 220);
	osc2level->setSize(180, 20);
	addAndMakeVisible(osc2level);

	// oscilator 3 controls
	osc3active = new ToggleButton();
	osc3active->addListener(this);
	osc3active->setSize(20, 20);
	osc3active->setTopLeftPosition(20, 340);
	addAndMakeVisible(osc3active);

	osc3label = new Label();
	osc3label->setText("Oscilator 3", dontSendNotification);
	osc3label->setTopLeftPosition(40, 340);
	osc3label->setSize(100, 20);
	addAndMakeVisible(osc3label);

	osc3level = new Slider();
	osc3level->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	osc3level->addListener(this);
	osc3level->setRange(0, 1, 0.0001);
	osc3level->setValue(1);
	osc3level->setTopLeftPosition(10, 370);
	osc3level->setSize(180, 20);
	addAndMakeVisible(osc3level);

	// group outline
	groupOutline = new GroupComponent(name, label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	addAndMakeVisible(groupOutline);
	groupOutline->setTopLeftPosition(0, 0);
	groupOutline->setSize(getWidth(), getHeight());
}

MixerControlGroup::~MixerControlGroup() {
	// take no action
}

void MixerControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == osc1level) {
		baseMixer->setRelativeLevel(0, osc1level->getValue());
	} else if (changed == osc2level) {
		baseMixer->setRelativeLevel(1, osc2level->getValue());
	} else if (changed == osc3level) {
		baseMixer->setRelativeLevel(2, osc3level->getValue());
	}
}

void MixerControlGroup::buttonClicked(Button* clicked) {
	if (clicked == osc1active) {
		baseMixer->setOscilatorIsActive(0, osc1active->getToggleState());
	} else if (clicked == osc2active) {
		baseMixer->setOscilatorIsActive(1, osc2active->getToggleState());
	} else if (clicked == osc3active) {
		baseMixer->setOscilatorIsActive(2, osc3active->getToggleState());
	}
}

void MixerControlGroup::resized() {

}

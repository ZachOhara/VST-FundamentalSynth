#include "MasterVolumeControlGroup.h"

MasterVolumeControlGroup::MasterVolumeControlGroup(MasterVolumeProcessor* processor) {
	setSize(WIDTH, HEIGHT);
	volumeProcessor = processor;

	label = new Label();
	label->setText("Master Volume", dontSendNotification);
	label->setTopLeftPosition(50, 30);
	label->setSize(100, 20);
	addAndMakeVisible(label);

	slider = new Slider();
	slider->setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	slider->addListener(this);
	slider->setRange(0, 1, 0);
	slider->setValue(1);
	slider->setTopLeftPosition(10, 60);
	slider->setSize(180, 20);
	addAndMakeVisible(slider);
}

void MasterVolumeControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == slider) { // of course it does
		volumeProcessor->setMasterVolume(slider->getValue());
	}
}

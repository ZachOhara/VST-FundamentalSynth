#include "FilterControlGroup.h"

FilterControlGroup::FilterControlGroup(Filter& processor) {
	setSize(WIDTH, HEIGHT);
	filterProcessor = &processor;

	filterEnabledButton = new ToggleButton();
	filterEnabledButton->addListener(this);
	filterEnabledButton->setSize(20, 20);
	filterEnabledButton->setTopLeftPosition(50, 25);
	addAndMakeVisible(filterEnabledButton);

	filterEnabledLabel = new Label();
	filterEnabledLabel->setText("Enabled", dontSendNotification);
	filterEnabledLabel->setSize(100, 20);
	filterEnabledLabel->setTopLeftPosition(70, 25);
	addAndMakeVisible(filterEnabledLabel);

	initializeControlSlider(cutoff, "Cutoff Frequency (KHz)", 50, 0.2, 25, 0.0001, 25);
	cutoff.slider->setSkewFactorFromMidPoint(1);
	initializeControlSlider(emphasis, "Emphasis", 100, 0, 10, 0.01, 10);
	initializeControlSlider(order, "Order", 150, 1, 3, 1, 1);

	// TODO better defaults
	buttonClicked(filterEnabledButton);
}

void FilterControlGroup::initializeControlSlider(ControlSlider & slider, String name,
	int yPos, double min, double max, double step, double start) {
	slider.label = new Label();
	slider.label->setText(name, dontSendNotification);
	slider.label->setSize(150, 20);
	slider.label->setTopLeftPosition(10, yPos);
	addAndMakeVisible(slider.label);

	slider.slider = new Slider();
	slider.slider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
	slider.slider->setTextValueSuffix("");
	slider.slider->setRange(min, max, step);
	//cutoffSlider->setSkewFactorFromMidPoint(0.5);
	slider.slider->addListener(this);
	slider.slider->setValue(start);
	slider.slider->setSize(180, 20);
	slider.slider->setTopLeftPosition(10, yPos + 20);
	addAndMakeVisible(slider.slider);

	// TODO better defaults
	sliderValueChanged(slider.slider);
}

void FilterControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == cutoff.slider) {
		filterProcessor->setCutoff(1000 * cutoff.slider->getValue());
	} else if (changed == emphasis.slider) {
		filterProcessor->setEmphasis(emphasis.slider->getValue() / 10);
	} else if (changed == order.slider) {
		filterProcessor->setOrder((int) order.slider->getValue());
	}
}

void FilterControlGroup::buttonClicked(Button* pressed) {
	if (pressed == filterEnabledButton) {
		filterProcessor->setIsEnabled(filterEnabledButton->getToggleState());
	}
}

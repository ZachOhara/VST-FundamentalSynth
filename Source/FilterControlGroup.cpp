#include "FilterControlGroup.h"

FilterControlGroup::FilterControlGroup(String name, String label, Filter& filter) {
	setSize(WIDTH, HEIGHT);

	filterProcessor = &filter;

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

	cutoffLabel = new Label();
	cutoffLabel->setText("Cutoff Frequency (KHz)", dontSendNotification);
	cutoffLabel->setSize(150, 20);
	cutoffLabel->setTopLeftPosition(10, 50);
	addAndMakeVisible(cutoffLabel);

	cutoffSlider = new Slider();
	cutoffSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
	cutoffSlider->setTextValueSuffix("");
	cutoffSlider->setRange(0.2, 20, 0.001);
	cutoffSlider->setSkewFactorFromMidPoint(0.5);
	cutoffSlider->addListener(this);
	cutoffSlider->setValue(20);
	cutoffSlider->setSize(180, 20);
	cutoffSlider->setTopLeftPosition(10, 70);
	addAndMakeVisible(cutoffSlider);

	emphasisLabel = new Label();
	emphasisLabel->setText("Emphasis", dontSendNotification);
	emphasisLabel->setSize(150, 20);
	emphasisLabel->setTopLeftPosition(10, 100);
	addAndMakeVisible(emphasisLabel);

	emphasisSlider = new Slider();
	emphasisSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
	emphasisSlider->setTextValueSuffix("");
	emphasisSlider->setRange(0, 10, 0.01);
	emphasisSlider->addListener(this);
	emphasisSlider->setValue(10);
	emphasisSlider->setSize(180, 20);
	emphasisSlider->setTopLeftPosition(10, 120);
	addAndMakeVisible(emphasisSlider);

	orderLabel = new Label();
	orderLabel->setText("Order", dontSendNotification);
	orderLabel->setSize(150, 20);
	orderLabel->setTopLeftPosition(10, 150);
	addAndMakeVisible(orderLabel);

	orderSlider = new Slider();
	orderSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
	orderSlider->setTextValueSuffix("");
	orderSlider->setRange(1, 3, 1);
	orderSlider->addListener(this);
	orderSlider->setValue(1);
	orderSlider->setSize(180, 20);
	orderSlider->setTopLeftPosition(10, 170);
	addAndMakeVisible(orderSlider);

	groupOutline = new GroupComponent(name, label);
	groupOutline->setTextLabelPosition(Justification::top);
	groupOutline->setColour(groupOutline->outlineColourId, Colours::black);
	addAndMakeVisible(groupOutline);
	groupOutline->setTopLeftPosition(0, 0);
	groupOutline->setSize(getWidth(), getHeight());

	// TODO better defaults
	sliderValueChanged(cutoffSlider);
	sliderValueChanged(emphasisSlider);
	sliderValueChanged(orderSlider);
}

FilterControlGroup::~FilterControlGroup() {

}

void FilterControlGroup::sliderValueChanged(Slider* changed) {
	if (changed == cutoffSlider) {
		filterProcessor->setCutoff(1000 * cutoffSlider->getValue());
	} else if (changed == emphasisSlider) {
		filterProcessor->setEmphasis(emphasisSlider->getValue() / 10);
	} else if (changed == orderSlider) {
		filterProcessor->setOrder((int) orderSlider->getValue());
	}
}

void FilterControlGroup::buttonClicked(Button* pressed) {
	if (pressed == filterEnabledButton) {
		filterProcessor->setIsEnabled(filterEnabledButton->getToggleState());
	}
}

void FilterControlGroup::resized() {

}

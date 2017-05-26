#include "RadioButtonSet.h"

RadioButtonSet::RadioButtonSet(RadioButtonSet::Listener* callback, String* buttonNames, int numNames) :
	buttons(numNames),
	buttonLabels(numNames) {
	updateCallback = callback;
	length = numNames;
	for (int i = 0; i < length; i++) {
		addAndMakeVisible(buttons[i]);
		buttons[i].addListener(this);
		buttons[i].setRadioGroupId(1, dontSendNotification);
		addAndMakeVisible(buttonLabels[i]);
		buttonLabels[i].setText(buttonNames[i], dontSendNotification);
	}

	buttons[0].triggerClick();
}

void RadioButtonSet::triggerClick(int index) {
	buttons[index].triggerClick();
}

void RadioButtonSet::buttonClicked(Button* button) {
	for (int i = 0; i < length; i++) {
		if (button == &buttons[i]) {
			updateCallback->selectionChanged(buttonLabels[i].getText());
		}
	}
}

int RadioButtonSet::getNecessaryHeight() {
	return radioButtonSpacing.buttonsTopOffset
		+ ((length - 1) * radioButtonSpacing.buttonsVerticalSpace)
		+ radioButtonSpacing.buttonsHeight;
}

void RadioButtonSet::paint(Graphics& g) {
	//g.fillAll(Colours::darkblue);
}

void RadioButtonSet::resized() {
	for (int i = 0; i < length; i++) {
		buttons[i].setTopLeftPosition(radioButtonSpacing.buttonsLeftOffset,
			radioButtonSpacing.buttonsTopOffset + (i * radioButtonSpacing.buttonsVerticalSpace));
		buttons[i].setSize(radioButtonSpacing.buttonsWidth, radioButtonSpacing.buttonsHeight);

		buttonLabels[i].setTopLeftPosition(radioButtonSpacing.buttonsLeftOffset + radioButtonSpacing.buttonsWidth,
			radioButtonSpacing.buttonsTopOffset + (i * radioButtonSpacing.buttonsVerticalSpace));
		buttonLabels[i].setSize(getWidth() - radioButtonSpacing.buttonsWidth
			- radioButtonSpacing.buttonsLeftOffset, radioButtonSpacing.buttonsHeight);
	}
}

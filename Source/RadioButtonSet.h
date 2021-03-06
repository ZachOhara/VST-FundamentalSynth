#ifndef RADIOBUTTONSET_H
#define RADIOBUTTONSET_H

#include "../JuceLibraryCode/JuceHeader.h"

static struct radioButtonSetSpacingConstants {
	static const int buttonsLeftOffset = 0;
	static const int buttonsTopOffset = 0;
	static const int buttonsVerticalSpace = 20;
	static const int buttonsWidth = 20;
	//static const int buttonLabelsWidth = 120;
	static const int buttonsHeight = 20;

} radioButtonSpacing;

class RadioButtonSet :
	public Component,
	Button::Listener {
public:
	class Listener {
	public:
		virtual void selectionChanged(String& newSelection) = 0;
	};

	RadioButtonSet(RadioButtonSet::Listener* callback, String* buttonNames, int numNames);

	void triggerClick(int index);

	void buttonClicked(Button* button) override;

	int getNecessaryHeight();

private:
	int length;

	Listener* updateCallback;

	std::vector<ToggleButton> buttons;
	std::vector<Label> buttonLabels;

	void resized() override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonSet)
};

#endif // RADIOBUTTONSET_H

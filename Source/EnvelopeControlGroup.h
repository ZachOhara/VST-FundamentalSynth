#ifndef ENVELOPECONTROLGROUP_H
#define ENVELOPECONTROLGROUP_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeProcessor.h"
#include "RadioButtonSet.h"

static struct envelopeControlSpacingConstants {
	static const int envelopeLeftOffset = 30;
	static const int envelopeTopOffset = 125;
	static const int envelopeSideSpace = 60;
	static const int envelopeFaderWidth = 50;
	static const int envelopeFaderHeight = 300;

	static const int modeLabelLeftOffset = 50;
	static const int modeLabelTopOffset = 40;
	static const int modeLabelWidth = 100;
	static const int modeLabelHeight = 30;

	static const int buttonsLeftOffset = 150;
	static const int buttonsTopOffset = 25;
	static const int buttonsVerticalSpace = 20;
	static const int buttonsWidth = 20;
	static const int buttonLabelsWidth = 120;
	static const int buttonsHeight = 20;

	static const int extraBottomSpace = 25;

	static const int necessaryTotalWidth = (2 * envelopeLeftOffset) + (3 * envelopeSideSpace) + envelopeFaderWidth;
	static const int necessaryTotalHeight = envelopeTopOffset + envelopeFaderHeight + extraBottomSpace;
} envelopeControlSpacing;

class EnvelopeControlGroup :
	public Component,
	Slider::Listener,
	RadioButtonSet::Listener {
public:
	EnvelopeControlGroup(String name, String label, EnvelopeProcessor* processor);
	~EnvelopeControlGroup();

	void resized() override;

private:
	EnvelopeProcessor* envelopeProcessor;

	GroupComponent* groupOutline;
	
	TimeFader envelopeAttackFader;
	TimeFader envelopeDecayFader;
	SustainFader envelopeSustainFader;
	TimeFader envelopeReleaseFader;

	Label envelopeAttackLabel;
	Label envelopeDecayLabel;
	Label envelopeSustainLabel;
	Label envelopeReleaseLabel;

	Label modeButtonsLabel;

	RadioButtonSet* modeButtonSet;

	void selectionChanged(String& newSelection) override;
	void sliderValueChanged(Slider* slider) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeControlGroup)
};

#endif // ENVELOPECONTROLGROUP_H

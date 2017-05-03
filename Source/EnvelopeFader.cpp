#include "EnvelopeFader.h"

EnvelopeFader::EnvelopeFader() {
	setSliderStyle(Slider::LinearBarVertical);
	setTextBoxStyle(Slider::TextBoxLeft, false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT);
}

EnvelopeFader::~EnvelopeFader() {
	// take no action
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitCrusherAudioProcessorEditor::BitCrusherAudioProcessorEditor (BitCrusherAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
	getLookAndFeel().setColour(Slider::trackColourId, Colours::orange);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::yellowgreen);

	// setup labels
	bitsLabel.setText("Bits", dontSendNotification);
	rateLabel.setText("Rate", dontSendNotification);
	noiseLabel.setText("Noise", dontSendNotification);
	mixLabel.setText("Mix", dontSendNotification);
	noiseTypeLabel.setText("Noise Type", dontSendNotification);
	multiplyModeLabel.setText("Algo", dontSendNotification);

	addAndMakeVisible(bitsLabel);
	addAndMakeVisible(rateLabel);
	addAndMakeVisible(noiseLabel);
	addAndMakeVisible(mixLabel);
	addAndMakeVisible(noiseTypeLabel);
	addAndMakeVisible(multiplyModeLabel);

	// setup noise type combobox
	addAndMakeVisible(noiseTypeMenu);
	noiseTypeMenu.addItem("White", 1);
	noiseTypeMenu.addItem("Simple", 2);
	noiseTypeMenuAttachment.reset(new ComboBoxAttachment(valueTreeState, "useWhiteNoise", noiseTypeMenu));

	// setup noise algo combobox
	addAndMakeVisible(multiplyModeMenu);
	multiplyModeMenu.addItem("Add", 1);
	multiplyModeMenu.addItem("Mul", 2);
	multiplyModeMenuAttachment.reset(new ComboBoxAttachment(valueTreeState, "multiplyMode", multiplyModeMenu));

	addAndMakeVisible(noiseSlider);
	noiseSliderAttachment.reset(new SliderAttachment(valueTreeState, "noise", noiseSlider));

	addAndMakeVisible(bitsSlider);
	bitsSliderAttachment.reset(new SliderAttachment(valueTreeState, "bits", bitsSlider));

	addAndMakeVisible(rateSlider);
	rateSliderAttachment.reset(new SliderAttachment(valueTreeState, "rate", rateSlider));

	addAndMakeVisible(mixSlider);
	mixSliderAttachment.reset(new SliderAttachment(valueTreeState, "mix", mixSlider));

	setResizable(true, true);
	setResizeLimits(400, 250, 800, 250);
}

BitCrusherAudioProcessorEditor::~BitCrusherAudioProcessorEditor()
{
}

//==============================================================================
void BitCrusherAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::darkslategrey.withMultipliedBrightness(.4));
}

void BitCrusherAudioProcessorEditor::resized()
{
	auto r = getLocalBounds();

	auto noiseRect = r.removeFromTop(paramControlHeight);
	noiseLabel.setBounds(noiseRect.removeFromLeft(paramLabelWidth));
	noiseSlider.setBounds(noiseRect);

	auto bitsRect = r.removeFromTop(paramControlHeight);
	bitsLabel.setBounds(bitsRect.removeFromLeft(paramLabelWidth));
	bitsSlider.setBounds(bitsRect);

	auto rateRect = r.removeFromTop(paramControlHeight);
	rateLabel.setBounds(rateRect.removeFromLeft(paramLabelWidth));
	rateSlider.setBounds(rateRect);

	auto mixRect = r.removeFromTop(paramControlHeight);
	mixLabel.setBounds(mixRect.removeFromLeft(paramLabelWidth));
	mixSlider.setBounds(mixRect);

	auto noiseTypeRect = r.removeFromTop(paramControlHeight);
	noiseTypeLabel.setBounds(noiseTypeRect.removeFromLeft(paramLabelWidth));
	noiseTypeMenu.setBounds(noiseTypeRect);

	auto noiseAlgoRect = r.removeFromTop(paramControlHeight);
	multiplyModeLabel.setBounds(noiseAlgoRect.removeFromLeft(paramLabelWidth));
	multiplyModeMenu.setBounds(noiseAlgoRect);
}
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
	/*getLookAndFeel().setColour(Slider::trackColourId, Colours::orange);
	getLookAndFeel().setColour(Slider::thumbColourId, Colours::yellowgreen);*/

	noiseSliderLookAndFeel.setColour(Slider::trackColourId, Colours::red);
	bitsSliderLookAndFeel.setColour(Slider::trackColourId, Colours::orange);
	rateSliderLookAndFeel.setColour(Slider::trackColourId, Colours::yellow);
	mixSliderLookAndFeel.setColour(Slider::trackColourId, Colours::green);
	gainSliderLookAndFeel.setColour(Slider::trackColourId, Colours::blue);


	// setup labels
	bitsLabel.setText("Bits", dontSendNotification);
	mixLabel.setText("Mix", dontSendNotification);
	rateLabel.setText("Rate", dontSendNotification);
	noiseLabel.setText("Noise", dontSendNotification);
	noiseTypeLabel.setText("Noise Type", dontSendNotification);
	multiplyModeLabel.setText("Noise Algo", dontSendNotification);
	gainLabel.setText("Gain", dontSendNotification);

	addAndMakeVisible(bitsLabel);
	addAndMakeVisible(rateLabel);
	addAndMakeVisible(noiseLabel);
	addAndMakeVisible(mixLabel);
	addAndMakeVisible(noiseTypeLabel);
	addAndMakeVisible(multiplyModeLabel);
	addAndMakeVisible(gainLabel);

	// setup noise type combobox
	addAndMakeVisible(noiseTypeMenu);
	noiseTypeMenu.addItem("White", 1);
	noiseTypeMenu.addItem("Simple", 2);
	noiseTypeMenuAttachment.reset(new ComboBoxAttachment(valueTreeState, "noiseType", noiseTypeMenu));

	// setup noise algo combobox
	addAndMakeVisible(multiplyModeMenu);
	multiplyModeMenu.addItem("Add", 1);
	multiplyModeMenu.addItem("Mul", 2);
	multiplyModeMenuAttachment.reset(new ComboBoxAttachment(valueTreeState, "noiseAlgo", multiplyModeMenu));

	addAndMakeVisible(noiseSlider);
	noiseSliderAttachment.reset(new SliderAttachment(valueTreeState, "noise", noiseSlider));
	noiseSlider.setLookAndFeel(&noiseSliderLookAndFeel);

	addAndMakeVisible(bitsSlider);
	bitsSliderAttachment.reset(new SliderAttachment(valueTreeState, "bits", bitsSlider));
	bitsSlider.setLookAndFeel(&bitsSliderLookAndFeel);

	addAndMakeVisible(rateSlider);
	rateSliderAttachment.reset(new SliderAttachment(valueTreeState, "rate", rateSlider));
	rateSlider.setLookAndFeel(&rateSliderLookAndFeel);

	addAndMakeVisible(mixSlider);
	mixSliderAttachment.reset(new SliderAttachment(valueTreeState, "mix", mixSlider));
	mixSlider.setLookAndFeel(&mixSliderLookAndFeel);

	addAndMakeVisible(gainSlider);
	gainSliderAttachment.reset(new SliderAttachment(valueTreeState, "gain", gainSlider));
	gainSlider.setLookAndFeel(&gainSliderLookAndFeel);

	setSize(400, 250); // TODO: use consts
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
	
	auto gainRect = r.removeFromTop(paramControlHeight);
	gainLabel.setBounds(gainRect.removeFromLeft(paramLabelWidth));
	gainSlider.setBounds(gainRect);

	auto menusRect = r.removeFromTop(paramControlHeight);

	auto noiseTypeRect = menusRect.removeFromLeft(200);
	noiseTypeLabel.setBounds(noiseTypeRect.removeFromLeft(paramLabelWidth));
	auto noiseTypeComboBoxRect = noiseTypeRect.removeFromLeft(comboBoxWidth);
	noiseTypeMenu.setBounds(
		noiseTypeComboBoxRect.withSize(noiseTypeComboBoxRect.getWidth() * 0.8,
			noiseTypeComboBoxRect.getHeight() * 0.8));

	auto noiseAlgoRect = menusRect.removeFromTop(paramControlHeight);
	multiplyModeLabel.setBounds(noiseAlgoRect.removeFromLeft(paramLabelWidth));
	auto noiseAlgoComboBoxRect = noiseAlgoRect.removeFromLeft(comboBoxWidth);
	multiplyModeMenu.setBounds(
		noiseAlgoComboBoxRect.withSize(noiseAlgoComboBoxRect.getWidth() * 0.8, 
			                           noiseAlgoComboBoxRect.getHeight() * 0.8));


}
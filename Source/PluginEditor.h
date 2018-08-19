/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BitCrusherAudioProcessorEditor  : public AudioProcessorEditor
{
public:

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
	
	// UI params
	enum
	{
		paramControlHeight = 40,
		paramLabelWidth = 60,
		paramSliderWidth = 300
	};

    BitCrusherAudioProcessorEditor (BitCrusherAudioProcessor&, AudioProcessorValueTreeState&);
    ~BitCrusherAudioProcessorEditor();

	//==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	AudioProcessorValueTreeState& valueTreeState;

	// sliders
	Label bitsLabel, 
		  rateLabel, 
		  noiseLabel, 
		  mixLabel;
	
	Slider bitsSlider, 
		   rateSlider, 
		   noiseSlider, 
		   mixSlider; 
	
	std::unique_ptr<SliderAttachment> bitsSliderAttachment, 
		                              rateSliderAttachment, 
		                              noiseSliderAttachment, 
		                              mixSliderAttachment;
	
	// buttons
	ToggleButton useWhiteNoiseButton, 
		         multiplyModeButton;
	std::unique_ptr<ButtonAttachment> useWhiteNoiseButtonAttachment, multiplyModeButtonAttachment;
	
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BitCrusherAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitCrusherAudioProcessorEditor)
};

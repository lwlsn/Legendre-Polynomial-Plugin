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
class Distortion1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Distortion1AudioProcessorEditor (Distortion1AudioProcessor&);
    ~Distortion1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    //create interface sliders
    
    ScopedPointer<Slider> driveSlider;
    ScopedPointer<Slider> rangeSlider;
    ScopedPointer<Slider> blendSlider;
    
    ScopedPointer<Slider> legendreGainSlider1;
    ScopedPointer<Slider> legendreGainSlider2;
    ScopedPointer<Slider> legendreGainSlider3;
    ScopedPointer<Slider> legendreGainSlider4;

    
    //create corresponding attachments to sliders
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment1;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment2;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment3;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainAttachment4;
    
    
    //create colour schemes for each of the legendre sliders
    LookAndFeel_V4 look1;
    LookAndFeel_V4 look2;
    LookAndFeel_V4 look3;
    LookAndFeel_V4 look4;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Distortion1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Distortion1AudioProcessorEditor)
};

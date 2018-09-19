/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Distortion1AudioProcessorEditor::Distortion1AudioProcessorEditor (Distortion1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    //Make sliders visible for the parameters to be edited within the plugin
    addAndMakeVisible(driveSlider = new Slider("Drive"));
    driveSlider->setSliderStyle(Slider::Rotary);
    driveSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    addAndMakeVisible(rangeSlider = new Slider ("Range"));
    rangeSlider->setSliderStyle(Slider::Rotary);
    rangeSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    addAndMakeVisible(blendSlider = new Slider("Blend"));
    blendSlider->setSliderStyle(Slider::Rotary);
    blendSlider->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    addAndMakeVisible(legendreGainSlider1 = new Slider("Legendre Gain 1"));
    legendreGainSlider1->setSliderStyle(Slider::Rotary);
    legendreGainSlider1->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    look1.setColour(Slider::thumbColourId, Colours::lavender);
    look1.setColour(Slider::rotarySliderFillColourId, Colours::lavender);
    legendreGainSlider1->setLookAndFeel(&look1);

    addAndMakeVisible(legendreGainSlider2 = new Slider("Legendre Gain 2"));
    legendreGainSlider2->setSliderStyle(Slider::Rotary);
    legendreGainSlider2->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    look2.setColour(Slider::thumbColourId, Colours::skyblue);
    look2.setColour(Slider::rotarySliderFillColourId, Colours::skyblue);
    legendreGainSlider2->setLookAndFeel(&look2);
    
    addAndMakeVisible(legendreGainSlider3 = new Slider("Legendre Gain 3"));
    legendreGainSlider3->setSliderStyle(Slider::Rotary);
    legendreGainSlider3->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    look3.setColour(Slider::thumbColourId, Colours::darkred);
    look3.setColour(Slider::rotarySliderFillColourId, Colours::darkred);
    legendreGainSlider3->setLookAndFeel(&look3);
    
    addAndMakeVisible(legendreGainSlider4 = new Slider("Legendre Gain 4"));
    legendreGainSlider4->setSliderStyle(Slider::Rotary);
    legendreGainSlider4->setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    
    look4.setColour(Slider::thumbColourId, Colours::lightgoldenrodyellow);
    look4.setColour(Slider::rotarySliderFillColourId, Colours::lightgoldenrodyellow);
    legendreGainSlider4->setLookAndFeel(&look4);
    
    //Attachments
    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveSlider);
    rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeSlider);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendSlider);
    gainAttachment1 = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "legendre gain 1", *legendreGainSlider1);
    gainAttachment2 = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "legendre gain 2", *legendreGainSlider2);
    gainAttachment3 = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "legendre gain 3", *legendreGainSlider3);
    gainAttachment4 = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "legendre gain 4", *legendreGainSlider4);

    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (550, 400);
}

Distortion1AudioProcessorEditor::~Distortion1AudioProcessorEditor()
{
}

//==============================================================================
void Distortion1AudioProcessorEditor::paint (Graphics& g)
{
    
    const int sliderWidth = 100;
    const int sliderHeight = 100;
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::salmon);
    g.setFont (15.0f);
    g.drawText("Legendre Waveshaping Distortion", 0, 0, getWidth() , 100, Justification::centred, 1);
    g.setColour(Colours::whitesmoke);
    g.drawText("Drive", ((getWidth() /4)*1) -(sliderWidth/2), (getHeight() /3) + 15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("Range", ((getWidth() /4)*2) -(sliderWidth/2), (getHeight() /3) + 15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("Dry/Wet", ((getWidth() /4)*3) -(sliderWidth/2), (getHeight() /3) + 15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("LegendreGain1", ((getWidth()/5)*1) -(sliderWidth/2), (getHeight() * 2/3) +15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("Legendre-Gain2", ((getWidth()/5)*2) -(sliderWidth/2), (getHeight() * 2/3) +15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("LegendreGain3", ((getWidth()/5)*3) -(sliderWidth/2), (getHeight() * 2/3) +15, sliderWidth, sliderHeight, Justification::centred, false);
    g.drawText("LegendreGain4", ((getWidth()/5)*4) -(sliderWidth/2), (getHeight() * 2/3) +15, sliderWidth, sliderHeight, Justification::centred, false);
}

void Distortion1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //Set all of the sliders to have equal width and height
    const int sliderWidth = 100;
    const int sliderHeight = 100;
 
    driveSlider->setBounds(((getWidth() /4)*1)-(sliderWidth/2),(getHeight() /3)-(sliderHeight/2) , sliderWidth, sliderHeight);
    rangeSlider->setBounds(((getWidth() /4)*2)-(sliderWidth/2),(getHeight() /3)-(sliderHeight/2) , sliderWidth, sliderHeight);
    blendSlider->setBounds(((getWidth() /4)*3)-(sliderWidth/2),(getHeight() / 3)-(sliderHeight/2) , sliderWidth, sliderHeight);

    legendreGainSlider1->setBounds(((getWidth() /5)*1)-(sliderWidth/2),(getHeight() * 2/3)-(sliderHeight/2) , sliderWidth, sliderHeight);
    legendreGainSlider2->setBounds(((getWidth() /5)*2)-(sliderWidth/2),(getHeight() * 2/3)-(sliderHeight/2) , sliderWidth, sliderHeight);
    legendreGainSlider3->setBounds(((getWidth() /5)*3)-(sliderWidth/2),(getHeight() * 2/3)-(sliderHeight/2) , sliderWidth, sliderHeight);
    legendreGainSlider4->setBounds(((getWidth() /5)*4)-(sliderWidth/2),(getHeight() * 2/3)-(sliderHeight/2) , sliderWidth, sliderHeight);
}

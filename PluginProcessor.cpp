/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Distortion1AudioProcessor::Distortion1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    state = new AudioProcessorValueTreeState(*this, nullptr);
    
    state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f,2.f,0.0001), 0.01, nullptr, nullptr);
    state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.f,3000.f,0.0001), 0.01, nullptr, nullptr);
    state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f,1.f,0.0001), 0.01, nullptr, nullptr);
    state->createAndAddParameter("legendre gain 1", "Legendre Gain 1", "Legendre Gain 1", NormalisableRange<float>(0.f, 2.f, 0.f), 0.5, nullptr, nullptr);
    state->createAndAddParameter("legendre gain 2", "Legendre Gain 2", "Legendre Gain 2", NormalisableRange<float>(0.f, 2.f, 0.f), 0.01, nullptr, nullptr);
    state->createAndAddParameter("legendre gain 3", "Legendre Gain 3", "Legendre Gain 3", NormalisableRange<float>(0.f, 2.f, 0.f), 0.01, nullptr, nullptr);
    state->createAndAddParameter("legendre gain 4", "Legendre Gain 4", "Legendre Gain 4", NormalisableRange<float>(0.f, 2.f, 0.f), 0.01, nullptr, nullptr);
    
    state-> state = ValueTree("drive");
    state-> state = ValueTree("range");
    state-> state = ValueTree("blend");
    state-> state = ValueTree("legendre gain 1");
    state-> state = ValueTree("legendre gain 2");
    state-> state = ValueTree("legendre gain 3");
    state-> state = ValueTree("legendre gain 4");
}

Distortion1AudioProcessor::~Distortion1AudioProcessor()
{
}

//==============================================================================
const String Distortion1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Distortion1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Distortion1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Distortion1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Distortion1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Distortion1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Distortion1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Distortion1AudioProcessor::setCurrentProgram (int index)
{
}

const String Distortion1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Distortion1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Distortion1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Distortion1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Distortion1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Distortion1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    float driveVal = *state->getRawParameterValue("drive");
    float rangeVal = *state->getRawParameterValue("range");
    float blendVal = *state->getRawParameterValue("blend");
    float legendreGainVal1 = *state->getRawParameterValue("legendre gain 1");
    float legendreGainVal2 = *state->getRawParameterValue("legendre gain 2");
    float legendreGainVal3 = *state->getRawParameterValue("legendre gain 3");
    float legendreGainVal4 = *state->getRawParameterValue("legendre gain 4");
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        //applying the distortion to the audio here
        for (int sample = 0; sample < buffer.getNumSamples(); sample++){
            
            float cleanSignal = *channelData; //save undistorted signal into a variable
            
            float legendre1Data = ((*channelData * blendVal)+ (cleanSignal * (1.f - blendVal))/2.f) ;
            float legendre2Data = (((3 * pow(*channelData, 2)-1) * blendVal) + (cleanSignal * (1.f - blendVal))/2.f);
            float legendre3Data = (((5*pow(*channelData, 3)- 3 * *channelData) * blendVal) + (cleanSignal * (1.f - blendVal))/2.f);
            float legendre4Data = ((0.25 * (35 * pow(*channelData, 4)- 30 * pow(*channelData, 2) + 3) * blendVal) + (cleanSignal*(1.f - blendVal))/2.f);
            
            
            *channelData *= driveVal * rangeVal;
            
            *channelData = jlimit(-1.f, 1.f, (legendre1Data*legendreGainVal1)+(legendre2Data*legendreGainVal2)+(legendre3Data*legendreGainVal3)+(legendre4Data*legendreGainVal4));
            
            
    
            //introduce distortion function dependent on the legendre polynomials
//
//            if (legendreVal == 0.0){
////                if (*channelData > 1 || *channelData > -1){
////                    *channelData = 1;
////                }
////                else {
////                    *channelData = ((*channelData* blendVal)+ (cleanSignal*(1.f - blendVal))/2.f)*gainVal;
////                }
//                *channelData = *channelData * gainVal;
//
////            *channelData = ((((2.f/float_Pi) * sin(*channelData)* blendVal)+ (cleanSignal*(1.f - blendVal))/2.f)*gainVal);
//            }
//
//            else if (legendreVal == 1.0) {
//                *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//                *channelData = jlimit(-1.f, 1.f, ((*channelData * blendVal)+ (cleanSignal * (1.f - blendVal))/2.f) * gainVal);
//            }
//
//            else if (legendreVal == 2.0) {
//                *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//
//                float legendre2Data = ((0.5 * (3 * pow(*channelData, 2)-1) * blendVal) + (cleanSignal * (1.f - blendVal))/2.f) * gainVal;
//                *channelData = jlimit(-1.f, 1.f, legendre2Data);
//            }
//
//            else if (legendreVal == 3.0) {
//                *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//                float legendre3Data = ((0.5*(5*pow(*channelData, 3)- 3 * *channelData) * blendVal) + (cleanSignal * (1.f - blendVal))/2.f) * gainVal;
//                *channelData = jlimit(-1.f, 1.f, legendre3Data);
//
//            }
//
//            else if (legendreVal == 4.0) {
//                    *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//                    float legendre4Data = ((1/8 * (35 * pow(*channelData, 4)- 30 * pow(*channelData, 2) + 3) * blendVal) + (cleanSignal*(1.f - blendVal))/2.f)*gainVal;
//                    *channelData = jlimit(-1.f, 1.f, legendre4Data);
//
//                }
//
//            else if (legendreVal == 5.0) {
//                *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//                float legendre5Data = ((1/8 * (63 * pow(*channelData, 5)- 70 *pow(*channelData, 3) + 15 * *channelData)*blendVal) + (cleanSignal*(1.f - blendVal))/2.f)*gainVal;
//                *channelData = jlimit(-1.f, 1.f, legendre5Data);
//            }
//
//            else if (legendreVal == 6.0) {
//                *channelData *= driveVal * rangeVal; //increase the audio by the value from the drive slider
//                float legendre6Data = ((1/16*(231* pow(*channelData, 6)- 315 * pow(*channelData, 4) + 105 * pow(*channelData,2) - 5)*blendVal) + (cleanSignal*(1.f - blendVal))/2.f)*gainVal;
//                *channelData = jlimit(-1.f, 1.f, legendre6Data);
//            }
            
            //increment the pointer so that it points to the next bit of channel data
            channelData++;
        }
    }
}



//==============================================================================

AudioProcessorValueTreeState& Distortion1AudioProcessor::getState() {
    return *state;
}

//==============================================================================
bool Distortion1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Distortion1AudioProcessor::createEditor()
{
    return new Distortion1AudioProcessorEditor (*this);
}

//==============================================================================
void Distortion1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream stream(destData,false);
    state->state.writeToStream(stream);
}

void Distortion1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Distortion1AudioProcessor();
}

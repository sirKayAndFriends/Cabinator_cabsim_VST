/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CabinatorAudioProcessor::CabinatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

CabinatorAudioProcessor::~CabinatorAudioProcessor()
{
}

//==============================================================================
const juce::String CabinatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CabinatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CabinatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CabinatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CabinatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CabinatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CabinatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CabinatorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CabinatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void CabinatorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CabinatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    newParams = cabSim->getParams();
    newParams->sampleRate = getSampleRate();
    updateParameters();
    cabSim->update();
}

void CabinatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CabinatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void CabinatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    updateParameters();

    buffer.copyFrom(1, 0, buffer.getReadPointer(0), buffer.getNumSamples());
    auto inputBlock = juce::dsp::AudioBlock<float>(buffer);

    inputBlock = cabSim->process(inputBlock);

}

void CabinatorAudioProcessor::updateParameters()
{
    newParams->hpFreq = apvts.getRawParameterValue("HIGHPASS")->load() * 175.0 + 25.0;

    newParams->lpFreq = (1.0 - apvts.getRawParameterValue("LOWPASS")->load()) * 3000.0 + 2000.0;

    newParams->peak1Freq = apvts.getRawParameterValue("PEAK1VOICE")->load() * 300.0 + 200.0;
    newParams->peak2Freq = apvts.getRawParameterValue("PEAK2VOICE")->load() * 1000.0 + 1000.0;
    newParams->peak1Gain = apvts.getRawParameterValue("PEAK1GAIN")->load() * 48.0 - 24.0;
    newParams->peak2Gain = apvts.getRawParameterValue("PEAK2GAIN")->load() * 48.0 - 24.0;
    newParams->makeupGain = 1.0;

    cabSim->update();
}


juce::AudioProcessorValueTreeState::ParameterLayout CabinatorAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOWPASS", "lowpass", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGHPASS", "highpass", 0.0f, 1.0f, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAK1VOICE", "peak1voice", 0.0f, 1.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAK1GAIN", "peak1gain", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAK2VOICE", "peak2voice", 0.0f, 1.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PEAK2GAIN", "peak2gain", 0.0f, 1.0f, 0.5f));

    return { params.begin(), params.end() };
}

std::shared_ptr<roomParams> CabinatorAudioProcessor::getGuiParams()
{
    return newParams;
}

//==============================================================================
bool CabinatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CabinatorAudioProcessor::createEditor()
{
    return new CabinatorAudioProcessorEditor (*this);
}

//==============================================================================
void CabinatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CabinatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CabinatorAudioProcessor();
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "skClasses/cab.h"

//==============================================================================
/**
*/
class CabinatorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    CabinatorAudioProcessor();
    ~CabinatorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void updateParameters();

    std::shared_ptr<roomParams> getGuiParams();

    juce::AudioProcessorValueTreeState apvts;

    std::vector<juce::String> attachmentNames
    {
        "PEAK1GAIN",
        "PEAK2GAIN",
        "PEAK1VOICE",
        "PEAK2VOICE",
        "HIGHPASS",
        "LOWPASS"        
    };

private:
    //==============================================================================

    std::unique_ptr<Room> cabSim = std::make_unique<Room>();
    std::shared_ptr<roomParams> newParams = std::make_shared<roomParams>();

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabinatorAudioProcessor)
};

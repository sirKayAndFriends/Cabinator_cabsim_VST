/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "skClasses/skVibes.h"

const int numParams = 6;

//==============================================================================
/**
*/
class CabinatorAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener
{
public:
    CabinatorAudioProcessorEditor (CabinatorAudioProcessor&);
    ~CabinatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

    void updateSlider(juce::Slider* slider);

private:

    SKVibes skVibes;
    SKLayout layout;

    std::shared_ptr<SKLayout::windowParams> layoutParams = std::make_shared<SKLayout::windowParams>();

    //SLIDERS
    std::vector<std::shared_ptr<SKVibes::sliderData>> sliderInfos; //slider gui parameters
    
    //ATTACHMENTS
    std::vector <std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> attachments;

    //TITLE
    std::shared_ptr<SKVibes::titleData> titleParams;

    CabinatorAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabinatorAudioProcessorEditor)
};

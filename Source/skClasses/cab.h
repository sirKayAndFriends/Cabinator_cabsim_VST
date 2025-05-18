/*
  ==============================================================================

    cab.h
    Created: 7 May 2025 10:47:17am
    Author:  jwh93

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "skFilters.h"

struct roomParams
{
    double lpFreq;
    double hpFreq;

    double outputFreq;

    double peak1Gain;
    double peak2Gain;

    double peak1Freq;
    double peak2Freq;

    double peakQ;

    double makeupGain;

    double sampleRate;
};

class Room
{
public:

    Room();

    void update();

    std::shared_ptr<roomParams> getParams();

    juce::dsp::AudioBlock<float> process(juce::dsp::AudioBlock<float> block);

private:
    std::unique_ptr<skFilters> cabLP = std::make_unique<skFilters>(lowpass);
    std::unique_ptr<skFilters> peak1 = std::make_unique<skFilters>(peak);
    std::unique_ptr<skFilters> peak2 = std::make_unique<skFilters>(peak);
    std::unique_ptr<skFilters> cabHP = std::make_unique<skFilters>(highpass);

    std::unique_ptr<skFilters> outputLP = std::make_unique<skFilters>(lowpass);

    std::shared_ptr<roomParams> params = std::make_shared<roomParams>();
};
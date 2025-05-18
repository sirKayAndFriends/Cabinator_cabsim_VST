/*
  ==============================================================================

    cab.cpp
    Created: 7 May 2025 10:47:22am
    Author:  jwh93

  ==============================================================================
*/

#include "cab.h"

Room::Room()
{
    params->hpFreq = 100.0;
    params->lpFreq = 5000.0;

    params->outputFreq = 5000.0;

    params->peak1Freq = 400.0;
    params->peak1Gain = 1.0;

    params->peak2Freq = 1000.0;
    params->peak2Gain = 1.0;

    params->peakQ = 0.707;

    params->sampleRate = 44100.0;

    params->makeupGain = 1.0;

    update();
}

void Room::update()
{
    cabHP->calc(params->hpFreq, 1.0, 0.707, params->sampleRate);
    cabLP->calc(params->lpFreq, 1.0, 0.707, params->sampleRate);
    peak1->calc(params->peak1Freq, params->peak1Gain, params->peakQ, params->sampleRate);
    peak2->calc(params->peak2Freq, params->peak2Gain, params->peakQ, params->sampleRate);

    outputLP->calc(params->outputFreq, 1.0, 0.707, params->sampleRate);
}

std::shared_ptr<roomParams> Room::getParams()
{
    return params;
}

juce::dsp::AudioBlock<float> Room::process(juce::dsp::AudioBlock<float> block)
{
    for (int sample = 0; sample < block.getNumSamples(); sample++)
    {   
        for (int channel = 0; channel < block.getNumChannels(); channel++)
        {
            float* chunk = block.getChannelPointer(channel);

            chunk[sample] = cabHP->process(chunk[sample]);
            chunk[sample] = cabLP->process(chunk[sample]);
            chunk[sample] = peak1->process(chunk[sample]);
            chunk[sample] = peak2->process(chunk[sample]);

            chunk[sample] = outputLP->process(chunk[sample]);

            chunk[sample] *= params->makeupGain;
        }
    }
    return block;
}
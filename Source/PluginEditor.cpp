/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CabinatorAudioProcessorEditor::CabinatorAudioProcessorEditor (CabinatorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setLookAndFeel(&skVibes);

    layoutParams = layout.setupLayout(50.0, 16, 9, 2, 1);
    setSize(layoutParams->width, layoutParams->height);
    layout.createDivisions();
    skVibes.setLayoutParams(layoutParams);

    sliderInfos = skVibes.setupSKRadioSliders(2, 2, 2);

    for (int i = 0; i < numParams; i++)
    {
        attachments.push_back(std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.apvts, processor.attachmentNames[i], *sliderInfos[i]->slider));
        sliderInfos[i]->slider->addListener(this);
        addAndMakeVisible(*sliderInfos[i]->slider);
        addAndMakeVisible(*sliderInfos[i]->label);
    }

    //MID GAIN SLIDERS
    sliderInfos[0]->pos = layout.getGridTopLeft(6, 3);
    sliderInfos[1]->pos = layout.getGridTopLeft(6, 3);

    //MID VOICE SLIDERS
    sliderInfos[2]->pos = juce::Point<float>(layout.getGridCentreX(4, 2), layout.getGridTopLeft(4, 1).y);   
    sliderInfos[3]->pos = juce::Point<float>(layout.getGridCentreX(8, 2), layout.getGridTopLeft(8, 1).y);
    sliderInfos[2]->offsetGUIvalue = 200;
    sliderInfos[2]->GUIrange = 300;
    sliderInfos[3]->offsetGUIvalue = 1000;
    sliderInfos[3]->GUIrange = 1000;

    //TREBLE AND BASS CUT SLIDERS
    sliderInfos[4]->pos = layout.getGridTopLeft(1, 3);
    sliderInfos[5]->pos = juce::Point<float>(layout.getGridCentreX(12, 3), layout.getGridY(3));
   
    sliderInfos[4]->offsetGUIvalue = 25;
    sliderInfos[4]->GUIrange = 175;
    sliderInfos[5]->offsetGUIvalue = 2000;
    sliderInfos[5]->GUIrange = 3000;

    titleParams = skVibes.setupSKTitle();
    titleParams->pos = layout.drawCentreX(titleParams->numUnitsX, 8);
    addAndMakeVisible(*titleParams->title);
}

CabinatorAudioProcessorEditor::~CabinatorAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void CabinatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillRect(0.0, 0.0, getWidth(), getHeight());

    skVibes.drawCabVisual(g, juce::Point<float>(layout.getGridX(1), layout.getGridY(2)));

    //only voice and cut sliders!
    //gain pos set in updateSlider()
    for (int i = 2; i < numParams; i++)
    {
        sliderInfos[i]->slider->setBounds(sliderInfos[i]->pos.x, sliderInfos[i]->pos.y, sliderInfos[i]->width, sliderInfos[i]->height);  
        updateSlider(sliderInfos[i]->slider.get());
    }

    skVibes.drawTitle();
}

void CabinatorAudioProcessorEditor::updateSlider(juce::Slider* slider)
{
    double sliderVal = slider->getValue();

    std::shared_ptr<SKVibes::sliderData> thisSlider;

    for (int i = 0; i < numParams; i++)
    {
        if (slider == sliderInfos[i]->slider.get())
        {
            thisSlider = sliderInfos[i];

            if (thisSlider->index == 2 || thisSlider->index == 3)
            {
                sliderInfos[i - 2]->slider->setBounds(sliderInfos[i]->pointerPos.x + sliderInfos[i]->pos.x - sliderInfos[i - 2]->width / 2.0, sliderInfos[i - 2]->pos.y, sliderInfos[i - 2]->width, sliderInfos[i - 2]->height);
                sliderInfos[i - 2]->pos = juce::Point<float>(sliderInfos[i]->pointerPos.x + sliderInfos[i]->pos.x - sliderInfos[i - 2]->width / 2.0, sliderInfos[i - 2]->pos.y);
            }

            else if (thisSlider->index == 5)
            {
                sliderVal = 1.0 - sliderVal;
            }

            std::string valueConverted = thisSlider->convert(sliderVal);

            thisSlider->text = valueConverted;

            break;
        }
    }
    repaint();
}

void CabinatorAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    updateSlider(slider);
}

void CabinatorAudioProcessorEditor::resized()
{
}

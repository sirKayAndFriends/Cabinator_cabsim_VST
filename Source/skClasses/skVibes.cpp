#pragma once
#include "JuceHeader.h"
#include "skVibes.h"

void SKVibes::setLayoutParams(std::shared_ptr<SKLayout::windowParams> params)
{
    basicParams = params;
}

std::vector<std::shared_ptr<SKVibes::sliderData>> SKVibes::setupSKRadioSliders(int numBoost, int numVoice, int numCut)
{
    int vecIndex = 0;

    for (int i = 0; i < numBoost; i++)
    {
        std::shared_ptr<sliderData> info = std::make_shared<sliderData>();
        info->slider = std::make_shared<juce::Slider>();
        info->label = std::make_shared<juce::Label>();

        info->slider->setSliderStyle(juce::Slider::LinearBarVertical);
        info->slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        info->slider->setSize(basicParams->unit * 1.0, basicParams->unit * 3.0);
        info->slider->setRange(0.0, 1.0, 0.01);
        info->slider->setDoubleClickReturnValue(true, 0.5);

        info->type = info->boost;
        info->orientation = info->forward;

        info->label->setFont(SKVibes::getPluginFont().withHeight(16.0f));
        info->label->setJustificationType(juce::Justification::centred);
        info->label->setColour(juce::Label::ColourIds::textColourId, juce::Colour(juce::Colours::white));
        info->label->setSize(basicParams->unit * 3.0, basicParams->unit * 1.0);

        info->width = info->slider->getWidth();
        info->height = info->slider->getHeight();
        info->labelWidth = info->label->getWidth();
        info->labelHeight = info->label->getHeight();
        info->index = vecIndex;

        info->offsetGUIvalue = -24.0;
        info->GUIrange = 48.0;
        info->guiUnit = "dB";

        sliders.push_back(info);

        vecIndex += 1;
    }

    for (int i = 0; i < numVoice; i++)
    {
        std::shared_ptr<sliderData> info = std::make_shared<sliderData>();
        info->slider = std::make_shared<juce::Slider>();
        info->label = std::make_shared<juce::Label>();

        info->slider->setSliderStyle(juce::Slider::LinearHorizontal);
        info->slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        info->slider->setSize(basicParams->unit * 3.0, basicParams->unit * 1.0);
        info->slider->setRange(0.0, 1.0, 0.01);

        info->type = info->voice;
        info->orientation = info->forward;

        info->label->setFont(SKVibes::getPluginFont().withHeight(16.0f));
        info->label->setJustificationType(juce::Justification::centred);
        info->label->setColour(juce::Label::ColourIds::textColourId, juce::Colour(juce::Colours::white));
        info->label->setSize(basicParams->unit * 3.0, basicParams->unit * 1.0);

        info->width = info->slider->getWidth();
        info->height = info->slider->getHeight();
        info->labelWidth = info->label->getWidth();
        info->labelHeight = info->label->getHeight();
        info->index = vecIndex;

        info->guiUnit = "Hz";

        sliders.push_back(info);

        vecIndex += 1;
    }

    for (int i = 0; i < numCut; i++)
    {
        std::shared_ptr<sliderData> info = std::make_shared<sliderData>();
        info->slider = std::make_shared<juce::Slider>();
        info->label = std::make_shared<juce::Label>();

        info->slider->setSliderStyle(juce::Slider::LinearHorizontal);
        info->slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        info->slider->setSize(basicParams->unit * 3.0, basicParams->unit * 3.0);
        info->slider->setRange(0.0, 1.0, 0.01);

        info->label->setFont(SKVibes::getPluginFont().withHeight(16.0f));
        info->label->setJustificationType(juce::Justification::centred);
        info->label->setColour(juce::Label::ColourIds::textColourId, juce::Colour(juce::Colours::white));
        info->label->setSize(basicParams->unit * 2.0, basicParams->unit * 1.0);

        info->type = info->cut;

        if (i % 2 == 0)
        {
            info->orientation = info->forward;
        }

        else
        {
            info->orientation = info->reverse;
        }

        info->width = info->slider->getWidth();
        info->height = info->slider->getHeight();
        info->labelWidth = info->label->getWidth();
        info->labelHeight = info->label->getHeight();
        info->index = vecIndex;

        info->guiUnit = "Hz";

        sliders.push_back(info);

        vecIndex += 1;
    }

    return sliders;
}

std::shared_ptr<SKVibes::titleData> SKVibes::setupSKTitle()
{
    titleParams->title = std::make_shared<juce::Label>();

    titleParams->title->setSize(basicParams->unit * 6, basicParams->unit * 2);
    titleParams->title->setFont(SKVibes::getPluginFont().withHeight(38.0f));
    titleParams->title->setJustificationType(juce::Justification::centred);
    titleParams->title->setColour(juce::Label::ColourIds::textColourId, juce::Colour(juce::Colours::white));

    titleParams->width = basicParams->unit * 6;
    titleParams->height = basicParams->unit * 1;
    titleParams->numUnitsX = 6;
    titleParams->numUnitsY = 1;

    titleParams->text = "Sweet Cabs 4 Cuties";
    titleParams->title->setText(titleParams->text, juce::NotificationType::dontSendNotification);

    return titleParams;
}

void SKVibes::drawTitle()
{
    titleParams->title->setBounds(titleParams->pos.x, titleParams->pos.y, titleParams->width, titleParams->height);
}

void SKVibes::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos,
    float minSliderPos,
    float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    std::shared_ptr<sliderData> thisSlider;

    for (int i = 0; i < sliders.size(); i++)
    {
        if (&slider == sliders[i]->slider.get())
        {
            thisSlider = sliders[i];
        }
    }

    float dotWidth = 2.0f;
    float levelWidth = 2.0f;
    float barWidth = 5.0f;

    juce::Point<float> centre(thisSlider->slider->getX() + width / 2.0, thisSlider->slider->getY() + height / 2.0);

    g.setColour(juce::Colours::white);

    if (thisSlider->type == thisSlider->boost)
    {
        int numPoints = 12;
        double t = 0.0;
        double delta = 1.0 / numPoints;

        g.setColour(juce::Colours::black);
        juce::Rectangle<float> bounds(x, y, slider.getWidth(), slider.getHeight());
        g.fillRect(bounds);
        g.setColour(juce::Colours::white);

        //nice dots
        for (int i = 0; i < numPoints; i++)
        {
            juce::Rectangle<float> point((x + width / 2.0) - dotWidth / 2.0, skLerp(y, y + height, t), dotWidth, dotWidth);
            t += delta;
            g.fillEllipse(point);
        }

        float linePos = skScale(slider.getValue(), y - levelWidth, y + height, reverse);
        float levelPos;

        if (sliderPos >= y + height - levelWidth)
        {
            levelPos = y + height - levelWidth;
        }

        else
        {
            levelPos = linePos;
        }

        //slider and point
        juce::Line<float> line(x + width / 2.0, y + height, x + width / 2.0, linePos);
        juce::Line<float> level(x, levelPos, x + width, levelPos);
        juce::Line<float> leftBracket(x, y + height * 0.25, x, y + height * 0.75);
        juce::Line<float> rightBracket(x + width, y + height * 0.25, x + width, y + height * 0.75);

        g.drawLine(line, barWidth);
        g.drawLine(level, levelWidth);
        g.drawLine(leftBracket, levelWidth);
        g.drawLine(rightBracket, levelWidth);

        thisSlider->label->setBounds(centre.x - thisSlider->labelWidth / 2.0, thisSlider->pos.y + height, thisSlider->labelWidth, thisSlider->labelHeight);
        thisSlider->label->setText(thisSlider->text, juce::NotificationType::dontSendNotification);
    }

    else if (thisSlider->type == thisSlider->voice)
    {
        //HORIZONTAL VOICE SLIDER
        juce::Path path;
        juce::Point<float> point1, point2, point3;

        point1.setXY(sliderPos, y + height);//tip
        point2.setXY(sliderPos - basicParams->unit * 0.2, (y + height) - basicParams->unit * 0.3);
        point3.setXY(sliderPos + basicParams->unit * 0.2, (y + height) - basicParams->unit * 0.3);

        path.addTriangle(point1, point2, point3);
        g.fillPath(path);

        thisSlider->pointerPos = point1;

        int labelPosX = sliderPos + thisSlider->pos.x - thisSlider->labelWidth / 2.0;

        thisSlider->labelPos = juce::Rectangle<int>(labelPosX, y + height * 2.0, thisSlider->labelWidth, thisSlider->labelHeight);
        thisSlider->label->setBounds(thisSlider->labelPos);
        thisSlider->label->setText(thisSlider->text, juce::NotificationType::dontSendNotification);
    }

    else if (thisSlider->type == thisSlider->cut)
    {
        float arrowOffset = 10.0f;
        float boundaryHeight = basicParams->unit * 3.0;
        float posY = y + height / 2.0;

        juce::AffineTransform sliderOrient;

        if (thisSlider->orientation == thisSlider->reverse)
        {
            sliderOrient = juce::AffineTransform::rotation(juce::MathConstants<float>::pi, centre.x, centre.y);
        }

        else
        {
            sliderOrient = juce::AffineTransform::rotation(juce::MathConstants<float>::twoPi, centre.x, centre.y);
        }

        juce::Path arrow;

        juce::Point<float> arrowStart(x - arrowOffset, posY);
        juce::Point<float> arrowEnd(sliderPos, posY);

        juce::Point<float> triTop(sliderPos - basicParams->unit * 0.3, posY - basicParams->unit * 0.2);
        juce::Point<float> triBottom(sliderPos - basicParams->unit * 0.3, posY + basicParams->unit * 0.2);

        juce::Point<float> boundaryTop(sliderPos + dotWidth, y - boundaryHeight);
        juce::Point<float> boundaryBottom(sliderPos + dotWidth, y + boundaryHeight);

        arrow.addTriangle(arrowEnd, triTop, triBottom);
        g.fillPath(arrow);

        arrow.startNewSubPath(arrowStart);
        arrow.lineTo(arrowEnd);
        g.strokePath(arrow, juce::PathStrokeType(barWidth));

        arrow.startNewSubPath(boundaryTop);
        arrow.lineTo(boundaryBottom);
        g.strokePath(arrow, juce::PathStrokeType(levelWidth));

        slider.setTransform(sliderOrient);

        thisSlider->labelPos = juce::Rectangle<int>(thisSlider->pos.x, thisSlider->pos.y - basicParams->unit, thisSlider->labelWidth, thisSlider->labelHeight);
        thisSlider->label->setBounds(thisSlider->labelPos);
        thisSlider->label->setText(thisSlider->text, juce::NotificationType::dontSendNotification);

        thisSlider->pointerPos = juce::Point<float>(sliderPos, posY);
    }

}

void SKVibes::drawCabVisual(juce::Graphics& g, juce::Point<float> pos)
{
    g.setColour(juce::Colours::white);

    juce::Rectangle<float> bounds(pos.x, pos.y, basicParams->unit * 14.0, basicParams->unit * 5.0);

    juce::Line<float> line(bounds.getX(), bounds.getCentreY(), bounds.getRight(), bounds.getCentreY());

    g.drawRect(bounds, 1.0f);
    g.drawLine(line, 1.0f);
}
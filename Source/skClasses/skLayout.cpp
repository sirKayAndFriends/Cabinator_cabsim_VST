/*
  ==============================================================================

    skLayout.cpp
    Created: 10 May 2025 6:00:57pm
    Author:  jwh93

  ==============================================================================
*/

#include "skLayout.h"

std::shared_ptr<SKLayout::windowParams> SKLayout::setupLayout(double unitSize, int numX, int numY, int numSliders, int numButtons)
{
    basicParams->width = unitSize * numX;
    basicParams->height = unitSize * numY;

    basicParams->unitsNumX = numX;
    basicParams->unit = unitSize;
    basicParams->unitsNumY = numY;

    basicParams->numSliders = numSliders;
    basicParams->numButtons = numButtons;

    return basicParams;
}

void SKLayout::createDivisions()
{
    float startX = 0.0f;
    float startY = 0.0f;

    for (int j = 0; j < basicParams->unitsNumY; j++)
    {
        for (int i = 0; i < basicParams->unitsNumX; i++)
        {
            basicParams->gridSquare.push_back(juce::Rectangle<float>(startX, startY, basicParams->unit, basicParams->unit));
            startX += basicParams->unit;
        }
        startX = 0.0;
        startY += basicParams->unit;
    }
}

std::vector<juce::Rectangle<float>>& SKLayout::getGrid()
{
    return basicParams->gridSquare;
}

juce::Point<float>& SKLayout::getGridPoint(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getX(), basicParams->gridSquare[index].getY());
}

juce::Point<float>& SKLayout::getCentrePoint(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getCentre();
}

juce::Rectangle<float>& SKLayout::getGridRect(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index];
}

juce::Point<float> SKLayout::getGridBottomLeft(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getBottomLeft();
}

juce::Point<float> SKLayout::getGridBottomRight(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getBottomRight();
}

juce::Point<float> SKLayout::getGridTopLeft(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getTopLeft();
}

juce::Point<float> SKLayout::getGridTopRight(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getTopRight();
}

float SKLayout::getGridCentreX(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getCentreX();
}

float SKLayout::getGridCentreY(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return basicParams->gridSquare[index].getCentreY();
}

float SKLayout::getGridX(int col)
{
    return basicParams->gridSquare[col].getX();
}

float SKLayout::getGridY(int row)
{
    int index = row * basicParams->unitsNumY;
    return basicParams->gridSquare[row].getX();
}

juce::Point<float> SKLayout::drawOnIntersection(int row, int col, juce::Component* object)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getX() - object->getWidth() / 2.0, basicParams->gridSquare[index].getY() - object->getHeight() / 2.0);
}

juce::Point<float> SKLayout::drawOnIntersection(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getX(), basicParams->gridSquare[index].getY());
}

juce::Point<float> SKLayout::drawOnCentre(int row, int col, juce::Component* object)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX() - object->getWidth() / 2.0, basicParams->gridSquare[index].getCentreY() - object->getHeight() / 2.0);
}

juce::Point<float> SKLayout::drawOnCentre(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX(), basicParams->gridSquare[index].getCentreY());
}

juce::Point<float> SKLayout::drawFromIntersection(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getX(), basicParams->gridSquare[index].getY());
}

juce::Point<float> SKLayout::drawFromCentre(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX(), basicParams->gridSquare[index].getCentreY());
}

juce::Point<float> SKLayout::drawOnHorizontal(int row, int col, juce::Component* object)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX() - object->getWidth() / 2.0, basicParams->gridSquare[index].getY() - object->getHeight() / 2.0);
}

juce::Point<float> SKLayout::drawOnHorizontal(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX(), basicParams->gridSquare[index].getY());
}

juce::Point<float> SKLayout::drawOnVertical(int row, int col, juce::Component* object)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getX() - object->getWidth() / 2.0, basicParams->gridSquare[index].getCentreY() - object->getHeight() / 2.0);
}

juce::Point<float> SKLayout::drawOnVertical(int row, int col)
{
    int index = (col * basicParams->unitsNumX) + row;
    return juce::Point<float>(basicParams->gridSquare[index].getCentreX(), basicParams->gridSquare[index].getY());
}

juce::Point<float> SKLayout::drawCentreX(int numUnitWidth, int row)
{
    int index = 0;
    int numMargin;
    float returnX, returnY = 0.0f;

    numMargin = (basicParams->unitsNumX - numUnitWidth) / 2;        //width of margin
    index = (row * basicParams->unitsNumX) + numMargin;       //y * unitsX + index

    if (basicParams->unitsNumX % 2 == 0)
    {
        returnX = basicParams->gridSquare[index].getX();
        returnY = basicParams->gridSquare[index].getY();
    }

    else if (basicParams->unitsNumX % 2 == 1)
    {
        returnX = basicParams->gridSquare[index].getCentreX();
        returnY = basicParams->gridSquare[index].getY();
    }

    return juce::Point<float>(returnX, returnY);
}

juce::Point<float> SKLayout::drawCentreY(int numUnitHeight, int col)
{
    int index = 0;
    int numMargin;
    float returnX, returnY = 0.0f;

    numMargin = (basicParams->unitsNumY - numUnitHeight) / 2;  //width of margin
    index = (numMargin * basicParams->unitsNumX) + col;       //y * unitsX + index

    if (basicParams->unitsNumY % 2 == 0)
    {
        returnX = basicParams->gridSquare[index].getX();
        returnY = basicParams->gridSquare[index].getY();
    }

    else if (basicParams->unitsNumY % 2 == 1)
    {
        returnX = basicParams->gridSquare[index].getX();
        returnY = basicParams->gridSquare[index].getCentreY();
    }

    return juce::Point<float>(returnX, returnY);
}
/*
  ==============================================================================

    skLayout.h
    Created: 10 May 2025 6:01:10pm
    Author:  jwh93

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SKLayout
{
public:

    struct windowParams
    {
        double width;
        double height;
        double unit;
        int unitsNumX;
        int unitsNumY;
        int numSliders;
        int numButtons;

        float buttonWidth, buttonHeight;
        float sliderWidth, sliderHeight;

        std::vector<juce::Rectangle<float>> gridSquare;
    };


    //returns second axis size from inputted first axis and aspect ratio! 
    std::shared_ptr<windowParams> setupLayout(double unitSize, int numX, int numY, int numSliders, int numButtons);

    //create a grid of squares
    void createDivisions();

    //return grid
    std::vector<juce::Rectangle<float>>& getGrid();

    //return a single corner point in row/column (0 index)
    juce::Point<float>& getGridPoint(int row, int col);

    //return single centre point in row/column (0 index)
    juce::Point<float>& getCentrePoint(int row, int col);

    //return a single rectangle from grid
    juce::Rectangle<float>& getGridRect(int row, int col);

    //return XY value of bottom left corner of selected rectangle
    juce::Point<float> getGridBottomLeft(int row, int col);

    //return XY value of bottom right corner of selected rectangle
    juce::Point<float> getGridBottomRight(int row, int col);

    //return XY value of top left of selected rectangle
    juce::Point<float> getGridTopLeft(int row, int col);

    //return XY value of top right of selected rectangle
    juce::Point<float> getGridTopRight(int row, int col);

    //return X value of centre of rect
    float getGridCentreX(int row, int col);

    //return Y value of centre of rect
    float getGridCentreY(int row, int col);

    //return X of grid square
    float getGridX(int col);

    //return Y of grid square
    float getGridY(int row);

    //returns coordinate for centering on intersections of grid
    juce::Point<float> drawOnIntersection(int row, int col, juce::Component* object);

    //returns coordinate for centering on intersections of grid
    juce::Point<float> drawOnIntersection(int row, int col);

    //returns coordinate for centering object on centre of grid square
    juce::Point<float> drawOnCentre(int row, int col, juce::Component* object);

    //returns coordinate for centering object on centre of grid square
    juce::Point<float> drawOnCentre(int row, int col);

    //coordinate for drawing top left corner from intersection
    juce::Point<float> drawFromIntersection(int row, int col);

    //coordinate for drawing top left corner from centre of square
    juce::Point<float> drawFromCentre(int row, int col);

    //x = square centre, y = bottom edge
    juce::Point<float> drawOnHorizontal(int row, int col, juce::Component* object);

    juce::Point<float> drawOnHorizontal(int row, int col);

    //x = left edge, y = square centre
    juce::Point<float> drawOnVertical(int row, int col, juce::Component* object);

    juce::Point<float> drawOnVertical(int row, int col);

    //centres component in X direction
    juce::Point<float> drawCentreX(int numUnitWidth, int row);

    //centres component in Y direction
    juce::Point<float> drawCentreY(int numUnitHeight, int col);

private:

    std::shared_ptr<windowParams> basicParams = std::make_shared<windowParams>();

};



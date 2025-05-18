/*
  ==============================================================================

    usefulFunctions.h
    Created: 18 May 2025 12:37:07pm
    Author:  jwh93

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

enum scaleDirections
{
    forward,
    reverse
};

inline float skLerp(float x, float y, float t)
{
    return x + (y - x) * t;
}

inline float skScale(float x, float min, float max, int direction)
{
    float scaled;

    switch (direction)
    {
    case forward:
    {
        scaled = x * max + min;
        break;
    }

    case reverse:
    {
        scaled = max - (x * max + min);
        break;
    }

    }
    return scaled;
}

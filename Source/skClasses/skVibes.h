#pragma once
#include "JuceHeader.h"
#include "skLayout.h"
#include "usefulFunctions.h"

class SKVibes : public juce::LookAndFeel_V4
{
public:

    enum skColours {
        skLavendar = 0xffaa46d8,
        skLightBlue = 0xff00c3ff,
        skPaleCyan = 0xff00eaff,
        skIBMcyan = 0xFF6CFAFF,
        skIBMcyanAlpha = 0x806CFAFF,
        skDaisyYellow = 0xfffff700,
        skPaleYellow = 0xffffff4d,
        skCream = 0xffffff90,
        skTomato = 0xffff0000,
        skSeville = 0xffffaf00,
        skPsychOrange = 0xffc54f00,
        skMauve = 0xffbb00c0,
        skPalePurple = 0xffbb56ff,
        skPsychPurple = 0xff9c39ff,
        skPlum = 0xff6a008b,
        skIBMlavendar = 0xFF7369FF,
        skIBMLavendarAlpha = 0x7F925EFF,
        skPeach = 0xffffbaae,
        skBerryPink = 0xffd800a5,
        skPrincessPink = 0xffff38c3,
        skStrawbYog = 0xffffcfff,
        skRaspberryAlpha = 0x7DFF7CA9,
        skRaspberry = 0xffff0064,
        skMintGreen = 0xff5cfff9,
        skBarleyGreen = 0xff3ee8bb,
        skForestGreen = 0xff00e500,
        skDuckEgg = 0xff3ee1ff,
        skCocoa = 0xff550030,
        skClear = 0x00ffffff,
        skWhite = 0xffffffff,
        skBlack = 0xff000000
    };

    struct sliderData
    {
        enum types
        {
            boost,
            voice,
            cut
        };

        enum direction
        {
            forward,
            reverse
        };

        std::shared_ptr<juce::Slider> slider;
        std::shared_ptr<juce::Label> label;
        juce::Point<float> pos;

        juce::Rectangle<int> labelPos;
        float labelWidth, labelHeight;
        juce::String text;

        juce::Point<float> pointerPos;

        float width, height;

        int index;

        int type;

        int orientation;

        int offsetGUIvalue, GUIrange;
        std::string guiUnit;

        std::string convert(double value)
        {
            int numPlaces = 0;
            double scaled = value * GUIrange + offsetGUIvalue;
            int scaledInt;
            std::string displayValue;

            if (scaled >= 100.0)
            {
                scaledInt = static_cast<int>(scaled);
                displayValue = std::to_string(scaledInt);
            }
            
            else
            {
                displayValue = std::to_string(scaled);
            }

            if (scaled < -10.0)
            {
                numPlaces = 5;
            }

            else if (scaled >= 0.0 && scaled < 10.0)
            {
                numPlaces = 3;
            }

            else
            {
                numPlaces = 4;
            }

            displayValue = displayValue.substr(0, numPlaces) + guiUnit;

            return displayValue;
        }
    };

    struct titleData
    {
        float width, height;
        juce::Point<float> pos;

        std::shared_ptr<juce::Label> title;

        juce::String text;

        int numUnitsX, numUnitsY;
    };

    static const juce::Font& getPluginFont()
    {
        static juce::Font quicksand(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::DOS_JPN19_ttf,
            BinaryData::DOS_JPN19_ttfSize)));

        return quicksand;
    };

    void setLayoutParams(std::shared_ptr<SKLayout::windowParams> params);

    std::vector<std::shared_ptr<SKVibes::sliderData>> SKVibes::setupSKRadioSliders(int numBoost, int numvoice, int numCut);

    std::shared_ptr<titleData> setupSKTitle();

    void drawTitle();

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos,
        float minSliderPos,
        float maxSliderPos,
        const juce::Slider::SliderStyle style, juce::Slider& slider) override;

    void drawCabVisual(juce::Graphics& g, juce::Point<float> pos);

private:
    
    std::shared_ptr<SKLayout::windowParams> basicParams;

    std::vector<std::shared_ptr<sliderData>> sliders;

    std::shared_ptr<titleData> titleParams = std::make_shared<titleData>();
};
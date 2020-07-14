/*
  ==============================================================================

    SynthSound.h
    Created: 12 Jul 2020 8:36:26am
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};

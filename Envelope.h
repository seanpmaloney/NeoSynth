/*
  ==============================================================================

    Envelope.h
    Created: 12 Jul 2020 9:57:02pm
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope  : public juce::Component
{
public:
    Envelope(SynthFrameworkAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> attackTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> decayTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> sustainTree;
    juce::ScopedPointer <juce::AudioProcessorValueTreeState::SliderAttachment> releaseTree;
    SynthFrameworkAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};

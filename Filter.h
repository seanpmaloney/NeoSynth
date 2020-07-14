/*
  ==============================================================================

    Filter.h
    Created: 12 Jul 2020 10:25:03pm
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(SynthFrameworkAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider filterCutoff;
    juce::Slider filterRes;
    
    juce::ComboBox filterMenu;
    
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> filterVal;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> resVal;
    SynthFrameworkAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

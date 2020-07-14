/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 Jul 2020 9:08:23pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) :
audioProcessor(p)
{
    setSize(200, 200);
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    
    waveSelection = new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wavetype", oscMenu);
    

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillator One", titleArea, juce::Justification::centredTop);
    
    juce::Rectangle<float> area (25, 25, 150, 150);
    g.setColour(juce::Colours::seagreen);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{
    
}

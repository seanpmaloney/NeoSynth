/*
  ==============================================================================

    Envelope.cpp
    Created: 12 Jul 2020 9:57:02pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"
#include "PluginProcessor.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) :
audioProcessor(p)
{
    
    setSize(200, 200);
    
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f); //5000 ms
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 20);
    addAndMakeVisible(&attackSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 2000.0f); //2000 ms
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 20);
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 1.0f); //5000 ms
    sustainSlider.setValue(0.1f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 20);
    addAndMakeVisible(&sustainSlider);
    
    
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 20);
    addAndMakeVisible(&releaseSlider);
    
    //linking with processor:
    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "attack", attackSlider);
    decayTree = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "decay", decaySlider);
    sustainTree = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "sustain", sustainSlider);
    releaseTree = new juce::AudioProcessorValueTreeState::SliderAttachment (audioProcessor.tree, "release", releaseSlider);
    
}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll(juce::Colours::lightgrey);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope", titleArea, juce::Justification::centredTop);
    
    //should make dynamic later
    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);
    
    juce::Rectangle<float> area (25, 25, 150, 150);
    
    g.setColour(juce::Colours::seagreen);
    g.drawRoundedRectangle(area, 20.f, 2.0f);
}

void Envelope::resized()
{
    
    //Use a rectangle so we can resize easily later
    juce::Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}


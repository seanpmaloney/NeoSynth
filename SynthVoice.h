/*
  ==============================================================================

    SynthVoice.h
    Created: 12 Jul 2020 8:36:37am
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    
    bool canPlaySound (juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr; //trying to cast sound as synthsound, if successful, return true
    }
    
    //===========================================================================
    
    void getOscType(float* selection)
    {
        theWave = *selection;
    }
    
    //===========================================================================
    
    double setOscType()
    {
        if(theWave == 0)
        {
            return osc1.sinewave(frequency);
        }
        if(theWave == 1)
        {
            return osc1.saw(frequency);
        }
        if(theWave == 2)
        {
            return osc1.square(frequency);
        }
        else
        {
            return osc1.sinewave(frequency);
        }
    }
    
    //===========================================================================
    
    void getParam (float* attack, float* decay, float* sustain, float* release)
       {
           env1.setAttack(double(*attack));
           env1.setDecay(double(*decay));
           //usually between 0 and 1
           env1.setSustain(double(*sustain));
           env1.setRelease(double(*release));
           
       }
       
    //===========================================================================
    
    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    //===========================================================================
    
    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes)
    {
        filterChoice = *filterType;
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    
    //===========================================================================
    
    double setFilter()
    {
        if (filterChoice == 0)
        {
            return filter1.lores(setEnvelope(), cutoff, resonance);
        }
        
        if (filterChoice == 1)
        {
            return filter1.hires(setEnvelope(), cutoff, resonance);
        }
        
        if (filterChoice == 2)
        {
            return filter1.bandpass(setEnvelope(), cutoff, resonance);
        }
        else
        {
            return filter1.lores(setEnvelope(), cutoff, resonance); 
        }
    }
    
    
    //===========================================================================
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        //what happens when we hit a key on the keyboard
        //correlate the key you hit with the intended frequency
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
    }
    
    //===========================================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if(velocity == 0)
            clearCurrentNote();
    }
    
    //===========================================================================
    
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    }
    
    //===========================================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    }
    
    //===========================================================================
    
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        
        for(int sample = 0; sample < numSamples; sample++)
        {
            for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                
                outputBuffer.addSample(channel, startSample, setFilter() * 0.3);
            }
            startSample++;
        }
    }
    
    //===========================================================================
    
private:
    double level;
    double frequency;
    int theWave;
    
    int filterChoice;
    float cutoff;
    float resonance;
    
    
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter;
    maxiFilter filter1;
};

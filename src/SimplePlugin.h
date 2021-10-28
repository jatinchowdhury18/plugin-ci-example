#pragma once

#include <pch.h>

class SimplePlugin : public chowdsp::PluginBase<SimplePlugin>
{
public:
    SimplePlugin();

    static void addParameters (Parameters& params);
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processAudioBlock (AudioBuffer<float>& buffer) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplePlugin)
};

#pragma once

#include <pch.h>

class ModulatableParameter;
class SimplePlugin : public chowdsp::PluginBase<SimplePlugin>
{
public:
    SimplePlugin();

    static void addParameters (Parameters& params);

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processAudioBlock (AudioBuffer<float>& buffer) override;

    //#if HAS_CLAP_JUCE_EXTENSIONS
    //    bool supportsDirectProcess() override
    //    {
    //        return true;
    //    }
    //    clap_process_status clap_direct_process (const clap_process* process) noexcept override;
    //    void process_clap_event (const clap_event_header_t* e);
    //#endif

    AudioProcessorEditor* createEditor() override;

private:
    chowdsp::FloatParameter* gainParam = nullptr;

    dsp::Gain<float> gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimplePlugin)
};

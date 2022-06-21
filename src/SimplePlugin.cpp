#include "SimplePlugin.h"

namespace
{
const String gainParamTag = "gain";
}

SimplePlugin::SimplePlugin()
{
    gainParam = dynamic_cast<chowdsp::FloatParameter*> (vts.getParameter (gainParamTag));
}

void SimplePlugin::addParameters (Parameters& params)
{
    using namespace chowdsp::ParamUtils;
    createGainDBParameter (params, gainParamTag, "Gain", -12.0f, 12.0f, 0.0f);
}

void SimplePlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    gain.prepare ({ sampleRate, (uint32) samplesPerBlock, (uint32) getMainBusNumInputChannels() });
    gain.setRampDurationSeconds (0.05);
}

void SimplePlugin::releaseResources()
{
}

void SimplePlugin::processAudioBlock (AudioBuffer<float>& buffer)
{
    gain.setGainDecibels (gainParam->getCurrentValue());

    dsp::AudioBlock<float> block { buffer };
    dsp::ProcessContextReplacing<float> context { block };
    gain.process (context);
}

//clap_process_status SimplePlugin::clap_direct_process (const clap_process* process) noexcept
//{
//    if (process->audio_outputs_count == 0 || process->audio_outputs_count > 3)
//        return CLAP_PROCESS_ERROR;
//    if (process->audio_outputs[0].channel_count > 2 || process->audio_outputs[0].channel_count == 0)
//        return CLAP_PROCESS_ERROR;
//
//    auto events = process->in_events;
//    auto numEvents = (int) events->size (events);
//    int currentEvent = 0;
//    int nextEventTime = -1;
//
//    if (numEvents > 0)
//    {
//        auto event = events->get (events, 0);
//        nextEventTime = (int) event->time;
//    }
//
//    // We process in place so
//    static constexpr uint32_t maxBuses = 128;
//    std::array<float*, maxBuses> busses {};
//    busses.fill (nullptr);
//    MidiBuffer midiBuffer; // no midi in this plugin...
//
//    static constexpr int smallBlockSize = 64;
//    const auto numSamples = (int) process->frames_count;
//    for (int n = 0; n < numSamples; n += smallBlockSize)
//    {
//        const auto numSamplesToProcess = jmin (smallBlockSize, numSamples - n);
//
//        while (nextEventTime >= 0 && nextEventTime < n + numSamplesToProcess && currentEvent < numEvents)
//        {
//            auto event = events->get (events, (uint32_t) currentEvent);
//            process_clap_event (event);
//
//            currentEvent++;
//            nextEventTime = (currentEvent < numEvents) ? (int) events->get (events, (uint32_t) currentEvent)->time : -1;
//        }
//
//        uint32_t outChannels = 0;
//        for (uint32_t idx = 0; idx < process->audio_outputs_count && outChannels < maxBuses; ++idx)
//        {
//            for (uint32_t ch = 0; ch < process->audio_outputs[idx].channel_count; ++ch)
//            {
//                busses[outChannels] = process->audio_outputs[idx].data32[ch] + n;
//                outChannels++;
//            }
//        }
//
//        uint32_t inputChannels = 0;
//        for (uint32_t idx = 0; idx < process->audio_inputs_count && inputChannels < maxBuses; ++idx)
//        {
//            for (uint32_t ch = 0; ch < process->audio_inputs[idx].channel_count; ++ch)
//            {
//                auto* ic = process->audio_inputs[idx].data32[ch] + n;
//                if (inputChannels < outChannels)
//                {
//                    if (ic == busses[inputChannels])
//                    {
//                        // The buffers overlap - no need to do anything
//                    }
//                    else
//                    {
//                        juce::FloatVectorOperations::copy (busses[inputChannels], ic, (int) process->frames_count);
//                    }
//                }
//                else
//                {
//                    busses[inputChannels] = ic;
//                }
//                inputChannels++;
//            }
//        }
//
//        auto totalChans = std::max (inputChannels, inputChannels);
//        juce::AudioBuffer<float> buffer (busses.data(), (int) totalChans, (int) process->frames_count);
//
//        processBlock (buffer, midiBuffer);
//    }
//
//    // process any leftover events
//    for (; currentEvent < numEvents; ++currentEvent)
//    {
//        auto event = events->get (events, (uint32_t) currentEvent);
//        process_clap_event (event);
//    }
//
//    return CLAP_PROCESS_CONTINUE;
//}
//
//void SimplePlugin::process_clap_event (const clap_event_header_t* event)
//{
//    if (event->space_id != CLAP_CORE_EVENT_SPACE_ID)
//        return;
//
//    switch (event->type)
//    {
//        case CLAP_EVENT_PARAM_VALUE:
//        {
//            auto paramEvent = reinterpret_cast<const clap_event_param_value*> (event);
//            auto juceParameter = static_cast<juce::AudioProcessorParameter*> (paramEvent->cookie);
//
//            if (juceParameter->getValue() == (float) paramEvent->value)
//                return;
//
//            juceParameter->setValueNotifyingHost ((float) paramEvent->value);
//        }
//        break;
//        case CLAP_EVENT_PARAM_MOD:
//        {
//            auto paramModEvent = reinterpret_cast<const clap_event_param_mod*> (event);
//            auto modulatableParameter = static_cast<chowdsp::ParamUtils::ModParameterMixin*> (paramModEvent->cookie);
//
//            if (paramModEvent->note_id >= 0)
//            {
//                // no polyphonic modulation for now
//            }
//            else
//            {
//                if (modulatableParameter->supportsMonophonicModulation())
//                    modulatableParameter->applyMonophonicModulation (paramModEvent->amount);
//            }
//        }
//        break;
//        default:
//            break;
//    }
//}

AudioProcessorEditor* SimplePlugin::createEditor()
{
    auto builder = chowdsp::createGUIBuilder (magicState);
    auto editor = new foleys::MagicPluginEditor (magicState, BinaryData::gui_xml, BinaryData::gui_xmlSize, std::move (builder));

    // we need to set resize limits for StandalonePluginHolder
    editor->setResizeLimits (10, 10, 2000, 2000);

    return editor;
}

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimplePlugin();
}

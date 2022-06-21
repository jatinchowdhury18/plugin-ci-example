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

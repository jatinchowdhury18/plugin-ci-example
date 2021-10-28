#include "SimplePlugin.h"

SimplePlugin::SimplePlugin()
{
}

void SimplePlugin::addParameters (Parameters& params)
{
}

void SimplePlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void SimplePlugin::releaseResources()
{
}

void SimplePlugin::processAudioBlock (AudioBuffer<float>& buffer)
{
}

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimplePlugin();
}

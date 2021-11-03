#include "UnitTests.h"

class GainTest : public UnitTest
{
public:
    GainTest() : UnitTest ("Gain Test")
    {
    }

    void runTest() override
    {
        beginTest ("Gain Test");
        auto* proc = createPluginFilterOfType (AudioProcessor::WrapperType::wrapperType_Standalone);
        std::unique_ptr<SimplePlugin> plugin (dynamic_cast<SimplePlugin*> (proc));

        constexpr int nSamples = 8192;
        proc->prepareToPlay (48000.0, nSamples);

        MidiBuffer midiBuffer;
        AudioBuffer<float> testBuffer (1, nSamples);
        auto* testData = testBuffer.getWritePointer (0);
        
        auto processBuffer = [&] (int numBlocks)
        {
            for (int i = 0; i < numBlocks; ++i)
            {
                FloatVectorOperations::fill (testData, 1.0f, nSamples);
                proc->processBlock (testBuffer, midiBuffer);
            }

            return testData[nSamples - 1];
        };

        constexpr float maxError = 0.2f;
        proc->getParameters()[0]->setValue (0.0f); // -12 dB
        expectWithinAbsoluteError (processBuffer (10), 0.25f, maxError, "-12dB value is incorrect!");
        
        proc->getParameters()[0]->setValue (1.0f); // +12 dB
        expectWithinAbsoluteError (processBuffer (10), 4.0f, maxError, "+12dB value is incorrect!");
        
        proc->getParameters()[0]->setValue (0.5f); // 0 dB
        expectWithinAbsoluteError (processBuffer (10), 1.0f, maxError, "0dB value is incorrect!");
    }
};

static GainTest gainTest;

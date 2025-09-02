#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
HighpassAudioProcessor::HighpassAudioProcessor()
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParameterLayout())
{
    auto* cutoffParam = apvts.getRawParameterValue("cutoff");
    auto* qParam = apvts.getRawParameterValue("q");

    cutoffSmoothed.reset(currentSampleRate, smoothingSeconds);
    qSmoothed.reset(currentSampleRate, smoothingSeconds);

    cutoffSmoothed.setCurrentAndTargetValue(*cutoffParam);
    qSmoothed.setCurrentAndTargetValue(*qParam);
}

HighpassAudioProcessor::~HighpassAudioProcessor() {}

AudioProcessorValueTreeState::ParameterLayout HighpassAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(
        "cutoff", "Cutoff",
        NormalisableRange<float>(20.0f, 20000.0f, 0.01f, 0.3f), 200.0f));

    params.push_back(std::make_unique<AudioParameterFloat>(
        "q", "Resonance",
        NormalisableRange<float>(0.1f, 10.0f, 0.01f), 0.707f));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String HighpassAudioProcessor::getName() const { return JucePlugin_Name; }
bool HighpassAudioProcessor::acceptsMidi() const { return false; }
bool HighpassAudioProcessor::producesMidi() const { return false; }
bool HighpassAudioProcessor::isMidiEffect() const { return false; }
double HighpassAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int HighpassAudioProcessor::getNumPrograms() { return 1; }
int HighpassAudioProcessor::getCurrentProgram() { return 0; }
void HighpassAudioProcessor::setCurrentProgram(int) {}
const juce::String HighpassAudioProcessor::getProgramName(int) { return {}; }
void HighpassAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
void HighpassAudioProcessor::prepareToPlay(double sampleRate, int)
{
    currentSampleRate = sampleRate;

    filterL.reset();
    filterR.reset();

    cutoffSmoothed.reset(currentSampleRate, smoothingSeconds);
    qSmoothed.reset(currentSampleRate, smoothingSeconds);

    auto* cutoffParam = apvts.getRawParameterValue("cutoff");
    auto* qParam = apvts.getRawParameterValue("q");

    cutoffSmoothed.setCurrentAndTargetValue(*cutoffParam);
    qSmoothed.setCurrentAndTargetValue(*qParam);
}

void HighpassAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HighpassAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}
#endif

void HighpassAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const int numSamples = buffer.getNumSamples();

    const float targetCutoff = apvts.getRawParameterValue("cutoff")->load();
    const float targetQ = apvts.getRawParameterValue("q")->load();

    cutoffSmoothed.setTargetValue(targetCutoff);
    qSmoothed.setTargetValue(targetQ);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        const float curCutoff = cutoffSmoothed.getNextValue();
        const float curQ = qSmoothed.getNextValue();

        auto coeffs = juce::IIRCoefficients::makeHighPass(currentSampleRate, curCutoff, curQ);
        filterL.setCoefficients(coeffs);
        filterR.setCoefficients(coeffs);

        if (buffer.getNumChannels() > 0)
            buffer.setSample(0, sample, filterL.processSingleSampleRaw(buffer.getSample(0, sample)));

        if (buffer.getNumChannels() > 1)
            buffer.setSample(1, sample, filterR.processSingleSampleRaw(buffer.getSample(1, sample)));
    }
}

//==============================================================================
bool HighpassAudioProcessor::hasEditor() const { return true; }
AudioProcessorEditor* HighpassAudioProcessor::createEditor() { return new HighpassAudioProcessorEditor(*this); }

//==============================================================================
void HighpassAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = apvts.state.createXml())
        copyXmlToBinary(*xml, destData);
}

void HighpassAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        apvts.state = juce::ValueTree::fromXml(*xml);
}

// Factory
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HighpassAudioProcessor();
}

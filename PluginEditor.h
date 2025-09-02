#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class HighpassAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    HighpassAudioProcessorEditor(HighpassAudioProcessor&);
    ~HighpassAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    HighpassAudioProcessor& processorRef;

    juce::Slider cutoffSlider;
    juce::Slider qSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> cutoffAttachment;
    std::unique_ptr<Attachment> qAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HighpassAudioProcessorEditor)
};

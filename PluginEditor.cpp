#include "PluginEditor.h"

//==============================================================================
HighpassAudioProcessorEditor::HighpassAudioProcessorEditor(HighpassAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    // Cutoff knob
    cutoffSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    cutoffSlider.setPopupDisplayEnabled(true, false, this);
    cutoffSlider.setSkewFactorFromMidPoint(1000.0); // perceptual scaling
    addAndMakeVisible(cutoffSlider);

    // Resonance knob
    qSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    qSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    qSlider.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(qSlider);

    // Attach parameters
    cutoffAttachment = std::make_unique<Attachment>(processorRef.apvts, "cutoff", cutoffSlider);
    qAttachment = std::make_unique<Attachment>(processorRef.apvts, "q", qSlider);

    setSize(360, 200);
}

HighpassAudioProcessorEditor::~HighpassAudioProcessorEditor() {}

//==============================================================================
void HighpassAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkslategrey);

    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("Highpass Filter", getLocalBounds().removeFromTop(30),
        juce::Justification::centred, 1);
}

void HighpassAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto knobArea = area.removeFromTop(area.getHeight() / 2);

    cutoffSlider.setBounds(knobArea.removeFromLeft(knobArea.getWidth() / 2).reduced(10));
    qSlider.setBounds(knobArea.reduced(10));
}

HighPass Alpha VST3 Plugin

Version: 1.0
License: GPL-3.0

HighPass Alpha is a stereo high-pass filter VST3 plugin built with JUCE 8. It allows precise control over cutoff frequency and resonance, designed for music production, sound design, and mixing.

Features

High-pass filtering on stereo signals

Adjustable cutoff frequency (20 Hz – 20 kHz)

Adjustable resonance (Q) (0.1 – 10)

Smooth parameter automation using juce::SmoothedValue

Supports standard VST3 hosts (Cubase, FL Studio, Reaper, etc.) (Only Tested in FL Studio)

Built-in real-time GUI with rotary knobs

Human-friendly perceptual scaling on the cutoff knob

 

Build Instructions
Requirements

Operating System: Windows 10/11  

IDE: Visual Studio 2022 (Windows)  

JUCE Framework: Version 8 or higher

VST3 SDK: Steinberg VST3 SDK 3.7 or newer

Steps

Clone the repository:

git clone https://github.com/WilliamAshley/HighPassAlpha.git
cd HighPassAlpha


Open HighPassAlpha.jucer in Projucer.

Make sure VST3 format is enabled in the Projucer exporter.

Save the project and open the generated IDE project (Visual Studio / Xcode).

Build the project (Debug/Release) for your target platform.

Copy the generated .vst3 file to your host’s plugin folder:

Windows: C:\Program Files\Common Files\VST3\

 

Usage

Load HighPass Alpha in your DAW as a VST3 plugin.

Use the Cutoff knob to set the high-pass frequency.

Use the Resonance (Q) knob to adjust the peak of the filter.

Automate parameters via your DAW for dynamic filtering effects.

License and Open Source Compliance

HighPass Alpha is released under the GNU General Public License v3 (GPL-3.0). You may use, modify, and redistribute the plugin under the GPL terms.

GPL Requirements

Source Code: Must remain open and accessible.

Derivative Works: Must also be licensed under GPL-3.0.

Attribution: Include this README and license file with any redistributed copies.

No Tivoization: You may not impose additional restrictions on modifying the plugin.

The VST3 SDK from Steinberg is used for plugin development. Under Steinberg's license:

You may develop and distribute VST3 plugins using the SDK.

Do not redistribute the VST3 SDK itself; users must download it separately if required.

The JUCE framework is used under its GPLv3 license in this project. This project complies fully with JUCE GPL requirements.

Contributing

Contributions are welcome! Please fork the repository, make changes, and submit a pull request. Ensure all changes comply with GPLv3 licensing.

Contact

Website: https://12264447666william.wixsite.com/williamashley

GitHub: https://github.com/WilliamAshley


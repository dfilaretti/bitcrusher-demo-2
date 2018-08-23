/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static Array<float> getSimpleNoise(int numSamples)
{
	Random r = Random::getSystemRandom();
	Array<float> noise;

	for (int s = 0; s < numSamples; s++)
	{
		noise.add((r.nextFloat() - .5) * 2);
	}

	return noise;

}

static Array<float> getWhiteNoise(int numSamples) 
{
	Array<float> noise;

	float z0 = 0;
	float z1 = 0;
	bool generate = false;

	float mu = 0; // center (0)
	float sigma = 1; // spread -1 <-> 1

	float output = 0;
	float u1 = 0;
	float u2 = 0;

	Random r = Random::getSystemRandom();
	r.setSeed(Time::getCurrentTime().getMilliseconds());
	const float epsilon = std::numeric_limits<float>::min();

	for (int s = 0; s < numSamples; s++)
	{

		// GENERATE ::::
		// using box muller method
		// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
		generate = !generate;

		if (!generate)
			output = z1 * sigma + mu;
		else
		{
			do
			{
				u1 = r.nextFloat();
				u2 = r.nextFloat();
			} while (u1 <= epsilon);

			z0 = sqrtf(-2.0 * logf(u1)) * cosf(2 * float(double_Pi) * u2);
			z1 = sqrtf(-2.0 * logf(u1)) * sinf(2 * float(double_Pi) * u2);

			output = z0 * sigma + mu;
		}

		// NAN check ...
		jassert(output == output);
		jassert(output > -50 && output < 50);

		//
		noise.add(output);

	}
	return noise;
}

//==============================================================================
BitCrusherAudioProcessor::BitCrusherAudioProcessor() 
	: parameters(*this, nullptr)
#ifndef JucePlugin_PreferredChannelConfigurations
    , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	// ----- Init params
	parameters.createAndAddParameter("noise",                                // parameter ID
		                             "Noise",                                // parameter name
		                             String(),                               // parameter label (suffix)
		                             NormalisableRange<float>(0.0f, 100.0f), // range
		                             0.0f,                                   // default value
		                             nullptr,
		                             nullptr);

	parameters.createAndAddParameter("rate",
		                             "Rate",                                 // parameter name
		                             String(),                               // parameter label (suffix)
		                             NormalisableRange<float>(1.0f, 50.0f),  // range
		                             1.0f,                                   // default value
		                             nullptr,
		                             nullptr);

	parameters.createAndAddParameter("bits",                                 // parameter ID
		                             "Bits",                                 // parameter name
		                             String(),                               // parameter label (suffix)
	 	                             NormalisableRange<float>(1.0f, 32.0f, 1.0f),  // range
		                             32.0f,                                  // default value
		                             nullptr,
		                             nullptr);

	parameters.createAndAddParameter("mix",                                   // parameter ID
		                             "Mix",                                   // parameter name
		                              String(),                               // parameter label (suffix)
		                              NormalisableRange<float>(0.0f, 1.0f),   // range
		                              1.0f,                                   // default value
		                              nullptr,
		                              nullptr);

	parameters.createAndAddParameter("gain",
		"Gain",
		{},
		NormalisableRange<float>(0, 2),
		1,
		nullptr,
		nullptr);

	parameters.createAndAddParameter("noiseType", 
		                             "Noise Type", 
		                             {},
		                             NormalisableRange<float>(1, 2, 1), 
		                             1,
		                             nullptr,
									 nullptr);
	
	parameters.createAndAddParameter("noiseAlgo",
									 "Noise Algo",
									 {},
									 NormalisableRange<float>(1, 2, 1),
									 1,
									 nullptr,
									 nullptr);


	parameters.state = ValueTree(Identifier("BitCrusher"));

	noiseParam = parameters.getRawParameterValue("noise");
	rateParam = parameters.getRawParameterValue("rate");
	bitsParam = parameters.getRawParameterValue("bits");
	mixParam = parameters.getRawParameterValue("mix");
	gainParam = parameters.getRawParameterValue("gain");
	noiseTypeParam = parameters.getRawParameterValue("noiseType");
	noiseAlgoParam = parameters.getRawParameterValue("noiseAlgo");
}

BitCrusherAudioProcessor::~BitCrusherAudioProcessor()
{
}

//==============================================================================
const String BitCrusherAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitCrusherAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BitCrusherAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BitCrusherAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BitCrusherAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BitCrusherAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BitCrusherAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BitCrusherAudioProcessor::setCurrentProgram (int index)
{
}

const String BitCrusherAudioProcessor::getProgramName (int index)
{
    return {};
}

void BitCrusherAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BitCrusherAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BitCrusherAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BitCrusherAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BitCrusherAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	// get buffer length
	int numSamples = buffer.getNumSamples();
	
	// get params
	float noiseAmt = -120 + 120 * (*noiseParam / 100); // dB
	noiseAmt = jlimit<float>(-120, 0, noiseAmt);       // limit (?)
	noiseAmt = Decibels::decibelsToGain(noiseAmt);     // dB to gain
	float bitDepth = *bitsParam;
	int rateDivide = *rateParam;
	float mix      = *mixParam;
	float gain     = *gainParam;
	int noiseType  = *noiseTypeParam;
	int noiseAlgo  = *noiseAlgoParam;

	// SAFETY CHECK :::: since some hosts will change buffer sizes without calling prepToPlay (Bitwig)
	// NB: seems not just BitWig related - if not present, it always crash
	if (noiseBuffer.getNumSamples() != numSamples)
	{
		noiseBuffer.setSize(2, numSamples, false, true, true); // clears
		currentOutputBuffer.setSize(2, numSamples, false, true, true); // clears
	}

	// Make a copy of the current buffer, to use for processing
	currentOutputBuffer.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
	
	if (buffer.getNumChannels() > 1) 
		currentOutputBuffer.copyFrom(1, 0, buffer.getReadPointer(1), numSamples);

	// BUILD NOISE ::::::
	{
		noiseBuffer.clear();

		Array<float> noise; // TODO: do NOT init here!

		// select noise type
		// TODO: specify the numbers below as consts or enum
		//       then use those instead of the magic numbers. 
		//       NB: this should also affect `createAndAddParameter`
		switch (noiseType) 
		{
			case 1:  // WHITE noise
				noise = getWhiteNoise(numSamples);
				break;
			case 2:  // SIMPLE noise
				noise = getSimpleNoise(numSamples);
				break;
			default: // use WHITE noise by default
				noise = getWhiteNoise(numSamples);
		}

		// range bound
		noiseAmt = jlimit<float>(0, 1, noiseAmt);

		// MAKE the noise ...
		FloatVectorOperations::multiply(noise.getRawDataPointer(), noiseAmt, numSamples);
		FloatVectorOperations::add(noiseBuffer.getWritePointer(0), noise.getRawDataPointer(), numSamples);
		FloatVectorOperations::add(noiseBuffer.getWritePointer(1), noise.getRawDataPointer(), numSamples); // STEREO

		// apply noise algo
		// TODO: as for the Noise Type, use consts/enums instead of those ints!
		switch (noiseAlgo)
		{
		case 1:  // ADD - nothing to do
			break;
		case 2:  // MUL - Multiply noise by signal (i.e. 0 signal -> 0 noise)
			FloatVectorOperations::multiply(noiseBuffer.getWritePointer(0), currentOutputBuffer.getWritePointer(0), numSamples);
			FloatVectorOperations::multiply(noiseBuffer.getWritePointer(1), currentOutputBuffer.getWritePointer(1), numSamples);
		default: // use ADD as default (i.e. do nothing!) 
			break;
		}
	}

	// ADD NOISE to the incoming AUDIO ::::
	currentOutputBuffer.addFrom(0, 0, noiseBuffer.getReadPointer(0), numSamples);
	currentOutputBuffer.addFrom(1, 0, noiseBuffer.getReadPointer(1), numSamples);

	// RESAMPLE AS NEEDED :::::
	for (int chan = 0; chan < currentOutputBuffer.getNumChannels(); chan++)
	{
		float* data = currentOutputBuffer.getWritePointer(chan);

		for (int i = 0; i < numSamples; i++)
		{
			// REDUCE BIT DEPTH :::::
			float totalQLevels = powf(2, bitDepth);
			float val = data[i];
			float remainder = fmodf(val, 1 / totalQLevels);

			// Quantize ...
			data[i] = val - remainder;

			if (rateDivide > 1)
			{
				if (i%rateDivide != 0) 
					data[i] = data[i - i % rateDivide];
			}
		}
	}

	// MIX dry and wet signals :::::
	{
		float wet = mix;
		float dry = 1 - mix;

		FloatVectorOperations::multiply(buffer.getWritePointer(0), dry, numSamples);
		FloatVectorOperations::multiply(buffer.getWritePointer(1), dry, numSamples);

		FloatVectorOperations::multiply(currentOutputBuffer.getWritePointer(0), wet, numSamples);
		FloatVectorOperations::multiply(currentOutputBuffer.getWritePointer(1), wet, numSamples);

		FloatVectorOperations::add(buffer.getWritePointer(0), currentOutputBuffer.getReadPointer(0), numSamples);
		FloatVectorOperations::add(buffer.getWritePointer(1), currentOutputBuffer.getReadPointer(1), numSamples);
	}

	// Apply final GAIN
	FloatVectorOperations::multiply(buffer.getWritePointer(0), gain, numSamples);
	FloatVectorOperations::multiply(buffer.getWritePointer(1), gain, numSamples);

}

//==============================================================================
bool BitCrusherAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BitCrusherAudioProcessor::createEditor()
{
    return new BitCrusherAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BitCrusherAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = parameters.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void BitCrusherAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(parameters.state.getType()))
			parameters.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitCrusherAudioProcessor();
}

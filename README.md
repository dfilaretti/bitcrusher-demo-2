# bitcrusher-tutorial-v2
simple bitcrusher plugin written in JUCE

## Improvements and additions over initial tutorial 

* use `AudioProcessorValueTreeState` to manage plugin state (considerably reducing code size and potential errors) 
* make use of `getStateInformation` and `getStateInformation` so that plugin state can be saved/restored by DAWs (e.g. when saving project then quiting and reloading)
* added a "mix" slider, controlling dry/wet ratio 
* added a "noise type" selector
* added a "noise algorith" selector, to chose whether noise is added or multiplied with the original signal
* use `removeFromTop`, `removeFromLeft` & friend to build the GUI instead of fixed positions

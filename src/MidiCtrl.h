#ifndef OFX_MIDI_CTRL
#define OFX_MIDI_CTRL

#include "constParameter.h"
#include "ofxMidi.h"

class MidiCtrl : public ofxMidiListener
{
public:
	MidiCtrl();
	~MidiCtrl();
	
	void newMidiMessage(ofxMidiMessage& eventArgs) override;
private:
	ofxMidiIn		_midiIn;
	ofxMidiMessage	_midiMessage;
};


#endif // !OFX_MIDI_CTRL

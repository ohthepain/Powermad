// DinMidiController

#include "MidiEvent.h"
#include "MidiManager.h"
#include "DinMidiController.h"
#include <MIDI.h>
#include <Arduino.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

namespace Atomic
{
	DinMidiController* DinMidiController::mInstance = nullptr;

	DinMidiController::DinMidiController()
	{
		Atomic::MidiManager::GetInstance()->RegisterMidiOutput(MidiSourceId::MidiPort, this);

		MIDI.begin(MIDI_CHANNEL_OMNI);
		
		mEventController = EventController::GetInstance();
	}

	DinMidiController::~DinMidiController()
	{
	}

	void DinMidiController::DinMidiController::Init()
	{
		mInstance = new DinMidiController();
	}

	void DinMidiController::DinMidiController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void DinMidiController::SendNoteOn(int note, int velocity, int channel)
	{
		Serial.print("Note on: note "); Serial.print(note); Serial.print(", velocity "); Serial.print(velocity); Serial.print(", channel "); Serial.println(channel);
		MIDI.sendNoteOn(note, velocity, channel);
	}
	
	void DinMidiController::SendNoteOff(int note, int velocity, int channel)
	{
		Serial.print("Note off: note "); Serial.print(note); Serial.print(", velocity "); Serial.print(velocity); Serial.print(", channel "); Serial.println(channel);
		MIDI.sendNoteOff(note, velocity, channel);
	}
	
	void DinMidiController::SendAfterTouchPoly(int note, int pressure, int channel)
	{
		MIDI.sendPolyPressure(note, pressure, channel);
	}
	
	void DinMidiController::SendControlChange(int control, int value, int channel)
	{
		MIDI.sendControlChange(control, value, channel);
	}
	
	void DinMidiController::SendProgramChange(int program, int channel)
	{
		MIDI.sendProgramChange(program, channel);
	}
	
	void DinMidiController::SendAfterTouch(int pressure, int channel)
	{
		MIDI.sendAfterTouch(pressure, channel);
	}
	
	void DinMidiController::SendPitchBend(int value, int channel)
	{
		MIDI.sendPitchBend(value, channel);
	}
	
	void DinMidiController::SendSysEx(int length, const uint8_t *data, bool hasTerm)
	{
	}
	
	void DinMidiController::SendTimeCodeQuarterFrame(int index, int value)
	{
	}
	
	void DinMidiController::SendSongPosition(int beats)
	{
	}
	
	void DinMidiController::SendSongSelect(int song)
	{
	}
	
	void DinMidiController::SendTuneRequest()
	{
	}
	
	void DinMidiController::SendClock()
	{
	}
	
	void DinMidiController::SendStart()
	{
	}
	
	void DinMidiController::SendContinue()
	{
	}
	
	void DinMidiController::SendStop()
	{
	}
	
	void DinMidiController::SendActiveSensing()
	{
	}
	
	void DinMidiController::SendSystemReset()
	{
	}	
}

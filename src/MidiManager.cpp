// MidiManager

#include "MidiManager.h"

namespace Atomic
{
	MidiManager* MidiManager::mInstance = nullptr;

	void MidiManager::MidiManager::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new MidiManager();
	}
	void MidiManager::MidiManager::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	MidiManager::MidiManager()
	{
		for (int i=0; i<NUM_MIDI_OUTPUTS; i++)
		{
			mMidiOutput[i] = 0;
		}
	}

	void MidiManager::RegisterMidiOutput(MidiSourceId midiSourceId, MidiOutput* midiOutput)
	{
		int n = static_cast<int>(midiSourceId);
		myassert(n < NUM_MIDI_OUTPUTS);
		myassert(mMidiOutput[n] == nullptr);
		mMidiOutput[n] = midiOutput;
	}

	MidiOutput* MidiManager::GetMidiOutput(MidiSourceId midiSourceId)
	{
		int n = static_cast<int>(midiSourceId);
		myassert(n < NUM_MIDI_OUTPUTS);
		myassert(mMidiOutput[n] != nullptr);
		return mMidiOutput[n];
	}

	void MidiManager::SendNoteOn(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity)
	{
		GetMidiOutput(midiSourceId)->SendNoteOn(note, velocity, channel);
	}

	void MidiManager::SendNoteOff(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity)
	{
		GetMidiOutput(midiSourceId)->SendNoteOff(note, velocity, channel);
	}

	void MidiManager::SendAfterTouchPoly(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity)
	{
	}

	void MidiManager::SendControlChange(MidiSourceId midiSourceId, uint8_t channel, uint8_t control, uint8_t value)
	{
	}

	void MidiManager::SendProgramChange(MidiSourceId midiSourceId, uint8_t channel, uint8_t program)
	{
	}

	void MidiManager::SendAfterTouch(MidiSourceId midiSourceId, uint8_t channel, uint8_t pressure)
	{
	}

	void MidiManager::SendPitchChange(MidiSourceId midiSourceId, uint8_t channel, int pitch)
	{
	}

	void MidiManager::SendSystemExclusiveChunk(MidiSourceId midiSourceId, const uint8_t *data, uint16_t length, bool last)
	{
	}

	void MidiManager::SendSystemExclusive(MidiSourceId midiSourceId, uint8_t *data, bool hasTerm)
	{
	}

	void MidiManager::SendTimeCodeQuarterFrame(MidiSourceId midiSourceId, uint8_t data)
	{
	}

	void MidiManager::SendSongPosition(MidiSourceId midiSourceId, uint16_t beats)
	{
	}

	void MidiManager::SendSongSelect(MidiSourceId midiSourceId, uint8_t songNumber)
	{
	}

	void MidiManager::SendTuneRequest()
	{
	}

	void MidiManager::SendClock()
	{
	}

	void MidiManager::SendStart()
	{
	}

	void MidiManager::SendContinue()
	{
	}

	void MidiManager::SendStop()
	{
	}

	void MidiManager::SendActiveSensing()
	{
	}

	void MidiManager::SendSystemReset()
	{
	}
	//void SendRealTimeSystem(uint8_t realtimebyte);
}

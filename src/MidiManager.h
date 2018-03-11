// MidiManager

#pragma once

#include <myassert.h>
#include "MidiEvent.h"

class EventController;

namespace Atomic
{
	class MidiOutput
	{
	public:
		virtual void SendNoteOn(int note, int velocity, int channel) =0;
		virtual void SendNoteOff(int note, int velocity, int channel) =0;
		virtual void SendAfterTouchPoly(int note, int pressure, int channel) =0;
		virtual void SendControlChange(int control, int value, int channel) =0;
		virtual void SendProgramChange(int program, int channel) =0;
		virtual void SendAfterTouch(int pressure, int channel) =0;
		virtual void SendPitchBend(int value, int channel) =0;
		virtual void SendSysEx(int length, const uint8_t* data, bool hasTerm) =0;
		virtual void SendTimeCodeQuarterFrame(int index, int value) =0;
		virtual void SendSongPosition(int beats) =0;
		virtual void SendSongSelect(int song) =0;
		virtual void SendTuneRequest() =0;
		virtual void SendClock() =0;
		virtual void SendStart() =0;
		virtual void SendContinue() =0;
		virtual void SendStop() =0;
		virtual void SendActiveSensing() =0;
		virtual void SendSystemReset() =0;
	};

	class MidiInput
	{
	public:
		void HandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
		void HandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
		void HandleAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity);
		void HandleControlChange(uint8_t channel, uint8_t control, uint8_t value);
		void HandleProgramChange(uint8_t channel, uint8_t program);
		void HandleAfterTouch(uint8_t channel, uint8_t pressure);
		void HandlePitchChange(uint8_t channel, int pitch);
		void HandleSystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last);
		void HandleSystemExclusive(uint8_t *data, unsigned int length);
		void HandleTimeCodeQuarterFrame(uint8_t data);
		void HandleSongPosition(uint16_t beats);
		void HandleSongSelect(uint8_t songNumber);
		void HandleTuneRequest();
		void HandleClock();
		void HandleStart();
		void HandleContinue();
		void HandleStop();
		void HandleActiveSensing();
		void HandleSystemReset();
	};

	#define NUM_MIDI_OUTPUTS 4

	class MidiManager
	{
	public:
		static void Init();
		static void Shutdown();
		static MidiManager* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		void RegisterMidiOutput(MidiSourceId midiSourceId, MidiOutput* midiOutput);
		MidiOutput* GetMidiOutput(MidiSourceId midiSourceId);

		void SendNoteOn(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity);
		void SendNoteOff(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity);
		void SendAfterTouchPoly(MidiSourceId midiSourceId, uint8_t channel, uint8_t note, uint8_t velocity);
		void SendControlChange(MidiSourceId midiSourceId, uint8_t channel, uint8_t control, uint8_t value);
		void SendProgramChange(MidiSourceId midiSourceId, uint8_t channel, uint8_t program);
		void SendAfterTouch(MidiSourceId midiSourceId, uint8_t channel, uint8_t pressure);
		void SendPitchChange(MidiSourceId midiSourceId, uint8_t channel, int pitch);
		void SendSystemExclusiveChunk(MidiSourceId midiSourceId, const uint8_t *data, uint16_t length, bool last);
		void SendSystemExclusive(MidiSourceId midiSourceId, uint8_t *data, bool hasTerm);
		void SendTimeCodeQuarterFrame(MidiSourceId midiSourceId, uint8_t data);
		void SendSongPosition(MidiSourceId midiSourceId, uint16_t beats);
		void SendSongSelect(MidiSourceId midiSourceId, uint8_t songNumber);
		void SendTuneRequest();
		void SendClock();
		void SendStart();
		void SendContinue();
		void SendStop();
		void SendActiveSensing();
		void SendSystemReset();
		//void SendRealTimeSystem(uint8_t realtimebyte);

	private:
		MidiManager();
		virtual ~MidiManager() {}
		static MidiManager* mInstance;
		MidiOutput* mMidiOutput[NUM_MIDI_OUTPUTS];
	};
}

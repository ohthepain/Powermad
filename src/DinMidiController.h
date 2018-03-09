// DinMidiController

#pragma once

#include <myassert.h>
#include "MidiManager.h"

class EventController;

namespace Atomic
{
	class DinMidiController : public MidiOutput
	{
	public:
		static void Init();
		static void Shutdown();
		static DinMidiController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

	private:
		DinMidiController();
		virtual ~DinMidiController();

		void HandleMillisecondTimer();

		static DinMidiController* mInstance;
	
		EventController* mEventController;
		
		void SendNoteOn(int note, int velocity, int channel);
		void SendNoteOff(int note, int velocity, int channel);
		void SendAfterTouchPoly(int note, int pressure, int channel);
		void SendControlChange(int control, int value, int channel);
		void SendProgramChange(int program, int channel);
		void SendAfterTouch(int pressure, int channel);
		void SendPitchBend(int value, int channel);
		void SendSysEx(int length, const uint8_t* data, bool hasTerm);
		void SendTimeCodeQuarterFrame(int index, int value);
		void SendSongPosition(int beats);
		void SendSongSelect(int song);
		void SendTuneRequest();
		void SendClock();
		void SendStart();
		void SendContinue();
		void SendStop();
		void SendActiveSensing();
		void SendSystemReset();
	};
}

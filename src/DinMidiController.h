// DinMidiController

#pragma once

#include <myassert.h>
#include "MidiManager.h"

class EventController;

namespace Atomic
{
	class DinMidiController : public MidiOutput, public MidiInput
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
		void HandleRealTimeSystem(uint8_t realtimebyte);

	private:
		int mThreadId;
		static void myHandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myHandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myHandleAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myHandleControlChange(uint8_t channel, uint8_t control, uint8_t value);
		static void myHandleProgramChange(uint8_t channel, uint8_t program);
		static void myHandleAfterTouch(uint8_t channel, uint8_t pressure);
		static void myHandlePitchChange(uint8_t channel, int pitch);
		static void myHandleSystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last);
		static void myHandleSystemExclusive(uint8_t *data, unsigned int length);
		static void myHandleTimeCodeQuarterFrame(uint8_t data);
		static void myHandleSongPosition(unsigned beats);
		static void myHandleSongSelect(uint8_t songNumber);
		static void myHandleTuneRequest();
		static void myHandleClock();
		static void myHandleStart();
		static void myHandleContinue();
		static void myHandleStop();
		static void myHandleActiveSensing();
		static void myHandleSystemReset();
		static void myHandleRealTimeSystem(uint8_t realtimebyte);
	};
}

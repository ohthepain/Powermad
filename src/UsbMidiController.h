// UsbMidiController.h

#pragma once

#ifdef USB_MIDI

#include <myassert.h>
#include "MidiManager.h"

class UsbMidiController;
class EventController;

namespace Atomic
{
	class UsbMidiController : public MidiOutput
	{
	public:
		static void Init();
		static void Shutdown();
		static UsbMidiController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

	private:
		UsbMidiController();
		virtual ~UsbMidiController();

		void HandleMillisecondTimer();

		static UsbMidiController* mInstance;
	
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

		static void myNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity);
		static void myControlChange(uint8_t channel, uint8_t control, uint8_t value);
		static void myProgramChange(uint8_t channel, uint8_t program);
		static void myAfterTouch(uint8_t channel, uint8_t pressure);
		static void myPitchChange(uint8_t channel, int pitch);
		static void mySystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last);
		static void mySystemExclusive(uint8_t *data, unsigned int length);
		static void myTimeCodeQuarterFrame(uint8_t data);
		static void mySongPosition(uint16_t beats);
		static void mySongSelect(uint8_t songNumber);
		static void myTuneRequest();
		static void myClock();
		static void myStart();
		static void myContinue();
		static void myStop();
		static void myActiveSensing();
		static void mySystemReset();
		static void myRealTimeSystem(uint8_t realtimebyte);
	};
}

#endif

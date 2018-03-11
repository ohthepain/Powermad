// DinMidiController

#include "MidiEvent.h"
#include "MidiManager.h"
#include "DinMidiController.h"
#include <MIDI.h>
#include <Arduino.h>
#include "TeensyThreads.h"
#include "myassert.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial5, MIDI);

void blinkthread()
{
	while (true)
	{
		threads.delay(1);
		while(MIDI.read())
		{
		}
	}
}

namespace Atomic
{
	DinMidiController* DinMidiController::mInstance = nullptr;

	DinMidiController::DinMidiController()
	: mThreadId(0)
	{
		MIDI.setHandleNoteOff(myHandleNoteOff);
		MIDI.setHandleNoteOn(myHandleNoteOn);
		MIDI.setHandleAfterTouchPoly(myHandleAfterTouchPoly);
		MIDI.setHandleControlChange(myHandleControlChange);
		MIDI.setHandleProgramChange(myHandleProgramChange);
		MIDI.setHandleAfterTouchChannel(myHandleAfterTouch);
		MIDI.setHandlePitchBend(myHandlePitchChange);
		MIDI.setHandleSystemExclusive(myHandleSystemExclusive);
		MIDI.setHandleTimeCodeQuarterFrame(myHandleTimeCodeQuarterFrame);
		MIDI.setHandleSongPosition(myHandleSongPosition);
		MIDI.setHandleSongSelect(myHandleSongSelect);
		MIDI.setHandleTuneRequest(myHandleTuneRequest);
		MIDI.setHandleClock(myHandleClock);
		MIDI.setHandleStart(myHandleStart);
		MIDI.setHandleContinue(myHandleContinue);
		MIDI.setHandleStop(myHandleStop);
		MIDI.setHandleActiveSensing(myHandleActiveSensing);
		MIDI.setHandleSystemReset(myHandleSystemReset);

		Atomic::MidiManager::GetInstance()->RegisterMidiOutput(MidiSourceId::MidiPort, this);

		mEventController = EventController::GetInstance();
		EventController::EventHandler handler = [&](const Event& event) { this->HandleMillisecondTimer(); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MillisecondClock, handler);

		MIDI.begin(MIDI_CHANNEL_OMNI);

		//mThreadId = threads.addThread(blinkthread);		
	}

	void DinMidiController::HandleMillisecondTimer()
	{
		while (MIDI.read())
		{
			// Doesnt seem like this is ignoring messags. Seems like it's
			//Serial.println("DinMidiController: ignored MIDI message");
  		}
	}
	
	void DinMidiController::HandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::NoteOn, MidiSourceId::MidiPort, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}

	void DinMidiController::HandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::NoteOff, MidiSourceId::MidiPort, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandleAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::AfterTouchPoly, MidiSourceId::MidiPort, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandleControlChange(uint8_t channel, uint8_t control, uint8_t value)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::ControlChange, MidiSourceId::MidiPort, channel, control, value);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandleProgramChange(uint8_t channel, uint8_t program)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::ProgramChange, MidiSourceId::MidiPort, channel, program, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandleAfterTouch(uint8_t channel, uint8_t pressure)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::AfterTouchChannel, MidiSourceId::MidiPort, channel, pressure, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandlePitchChange(uint8_t channel, int pitch)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::PitchBend, MidiSourceId::MidiPort, channel, pitch, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void DinMidiController::HandleSystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last)
	{
	}
	
	void DinMidiController::HandleSystemExclusive(uint8_t *data, unsigned int length)
	{
	}
	
	void DinMidiController::HandleTimeCodeQuarterFrame(uint8_t data)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::MidiTimeCodeQuarterFrame, MidiSourceId::MidiPort, data);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void DinMidiController::HandleSongPosition(uint16_t beats)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::SongPositionPointer, MidiSourceId::MidiPort, beats);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void DinMidiController::HandleSongSelect(uint8_t songNumber)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::SongSelect, MidiSourceId::MidiPort, songNumber);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void DinMidiController::HandleTuneRequest()
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::TuneRequest, MidiSourceId::MidiPort, 0  );
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void DinMidiController::HandleClock()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::TimingClock, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void DinMidiController::HandleStart()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Start, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void DinMidiController::HandleContinue()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Continue, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void DinMidiController::HandleStop()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Stop, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);		
	}
	
	void DinMidiController::HandleActiveSensing()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::ActiveSensing, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void DinMidiController::HandleSystemReset()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::SystemReset, MidiSourceId::MidiPort);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);		
	}
	
	void DinMidiController::HandleRealTimeSystem(uint8_t realtimebyte)
	{
		// idk what this is for - we already have start, stop etc
	}

	void DinMidiController::myHandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		DinMidiController::GetInstance()->HandleNoteOn(channel, note, velocity);
	}
	void DinMidiController::myHandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		DinMidiController::GetInstance()->HandleNoteOff(channel, note, velocity);
	}
	void DinMidiController::myHandleAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		DinMidiController::GetInstance()->HandleAfterTouchPoly(channel, note, velocity);
	}
	void DinMidiController::myHandleControlChange(uint8_t channel, uint8_t control, uint8_t value)
	{
		DinMidiController::GetInstance()->HandleControlChange(channel, control, value);
	}
	void DinMidiController::myHandleProgramChange(uint8_t channel, uint8_t program)
	{
		DinMidiController::GetInstance()->HandleProgramChange(channel, program);
	}
	void DinMidiController::myHandleAfterTouch(uint8_t channel, uint8_t pressure)
	{
		DinMidiController::GetInstance()->HandleAfterTouch(channel, pressure);
	}
	void DinMidiController::myHandlePitchChange(uint8_t channel, int pitch)
	{
		DinMidiController::GetInstance()->HandlePitchChange(channel, pitch);
	}
	void DinMidiController::myHandleSystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last)
	{
		DinMidiController::GetInstance()->HandleSystemExclusiveChunk(data, length, last);
	}
	void DinMidiController::myHandleSystemExclusive(uint8_t *data, unsigned int length)
	{
		DinMidiController::GetInstance()->HandleSystemExclusive(data, length);
	}
	void DinMidiController::myHandleTimeCodeQuarterFrame(uint8_t data)
	{
		DinMidiController::GetInstance()->HandleTimeCodeQuarterFrame(data);
	}
	void DinMidiController::myHandleSongPosition(unsigned beats)
	{
		DinMidiController::GetInstance()->HandleSongPosition(beats);
	}
	void DinMidiController::myHandleSongSelect(uint8_t songNumber)
	{
		DinMidiController::GetInstance()->HandleSongSelect(songNumber);
	}
	void DinMidiController::myHandleTuneRequest()
	{
		DinMidiController::GetInstance()->HandleTuneRequest();
	}
	void DinMidiController::myHandleClock()
	{
		DinMidiController::GetInstance()->HandleClock();
	}
	void DinMidiController::myHandleStart()
	{
		DinMidiController::GetInstance()->HandleStart();
	}
	void DinMidiController::myHandleContinue()
	{
		DinMidiController::GetInstance()->HandleContinue();
	}
	void DinMidiController::myHandleStop()
	{
		DinMidiController::GetInstance()->HandleStop();
	}
	void DinMidiController::myHandleActiveSensing()
	{
		DinMidiController::GetInstance()->HandleActiveSensing();
	}
	void DinMidiController::myHandleSystemReset()
	{
		DinMidiController::GetInstance()->HandleSystemReset();
	}
	void DinMidiController::myHandleRealTimeSystem(uint8_t realtimebyte)
	{
		DinMidiController::GetInstance()->HandleRealTimeSystem(realtimebyte);
	}

	DinMidiController::~DinMidiController()
	{
		if (mThreadId != 0)
		{
			threads.kill(mThreadId);
			mThreadId = 0;
		}
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
		//MIDI.sendPolyPressure(note, pressure, channel);
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

// UsbMidiController.cpp

#ifdef USB_MIDI

#include "MidiEvent.h"
#include "MidiManager.h"
#include "UsbMidiController.h"
#include <Arduino.h>

#include <usb_midi.h>

namespace Atomic
{
	UsbMidiController* UsbMidiController::mInstance = nullptr;

	UsbMidiController::UsbMidiController()
	{
		usbMIDI.setHandleNoteOff(myNoteOff);
		usbMIDI.setHandleNoteOn(myNoteOn);
		usbMIDI.setHandleAfterTouchPoly(myAfterTouchPoly);
		usbMIDI.setHandleControlChange(myControlChange);
		usbMIDI.setHandleProgramChange(myProgramChange);
		usbMIDI.setHandleAfterTouch(myAfterTouch);
		usbMIDI.setHandlePitchChange(myPitchChange);
		usbMIDI.setHandleSystemExclusive(mySystemExclusiveChunk);
		usbMIDI.setHandleTimeCodeQuarterFrame(myTimeCodeQuarterFrame);
		usbMIDI.setHandleSongPosition(mySongPosition);
		usbMIDI.setHandleSongSelect(mySongSelect);
		usbMIDI.setHandleTuneRequest(myTuneRequest);
		usbMIDI.setHandleClock(myClock);
		usbMIDI.setHandleStart(myStart);
		usbMIDI.setHandleContinue(myContinue);
		usbMIDI.setHandleStop(myStop);
		usbMIDI.setHandleActiveSensing(myActiveSensing);
		usbMIDI.setHandleSystemReset(mySystemReset);
		usbMIDI.setHandleRealTimeSystem(myRealTimeSystem);

		Atomic::MidiManager::GetInstance()->RegisterMidiOutput(MidiSourceId::USB, this);
		
		mEventController = EventController::GetInstance();
		EventController::EventHandler handler = [&](const Event& event) { this->HandleMillisecondTimer(); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MillisecondClock, handler);
	}

	UsbMidiController::~UsbMidiController()
	{
	}

	void UsbMidiController::UsbMidiController::Init()
	{
		mInstance = new UsbMidiController();
	}

	void UsbMidiController::UsbMidiController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void UsbMidiController::HandleMillisecondTimer()
	{
		while (usbMIDI.read())
		{
		    Serial.println("UsbMidiController: ignored MIDI message");
  		}
	}

	void UsbMidiController::HandleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::NoteOn, MidiSourceId::USB, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}

	void UsbMidiController::HandleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::NoteOff, MidiSourceId::USB, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandleAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::AfterTouchPoly, MidiSourceId::USB, channel, note, velocity);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandleControlChange(uint8_t channel, uint8_t control, uint8_t value)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::ControlChange, MidiSourceId::USB, channel, control, value);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandleProgramChange(uint8_t channel, uint8_t program)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::ProgramChange, MidiSourceId::USB, channel, program, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandleAfterTouch(uint8_t channel, uint8_t pressure)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::AfterTouchChannel, MidiSourceId::USB, channel, pressure, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandlePitchChange(uint8_t channel, int pitch)
	{
		MidiChannelMessageEvent midiChannelMessageEvent(MidiChannelMessageEventId::PitchBend, MidiSourceId::USB, channel, pitch, 0);
		EventController::GetInstance()->BroadcastEvent(midiChannelMessageEvent);
	}
	
	void UsbMidiController::HandleSystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last)
	{
	}
	
	void UsbMidiController::HandleSystemExclusive(uint8_t *data, unsigned int length)
	{
	}
	
	void UsbMidiController::HandleTimeCodeQuarterFrame(uint8_t data)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::MidiTimeCodeQuarterFrame, MidiSourceId::USB, data);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void UsbMidiController::HandleSongPosition(uint16_t beats)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::SongPositionPointer, MidiSourceId::USB, beats);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void UsbMidiController::HandleSongSelect(uint8_t songNumber)
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::SongSelect, MidiSourceId::USB, songNumber);
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void UsbMidiController::HandleTuneRequest()
	{
		MidiSystemCommonMessageEvent midiSystemCommonMessageEvent(MidiSystemCommonMessageId::TuneRequest, MidiSourceId::USB, 0  );
		EventController::GetInstance()->BroadcastEvent(midiSystemCommonMessageEvent);
	}
	
	void UsbMidiController::HandleClock()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::TimingClock, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void UsbMidiController::HandleStart()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Start, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void UsbMidiController::HandleContinue()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Continue, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void UsbMidiController::HandleStop()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Stop, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);		
	}
	
	void UsbMidiController::HandleActiveSensing()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::ActiveSensing, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
	}
	
	void UsbMidiController::HandleSystemReset()
	{
		static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::SystemReset, MidiSourceId::USB);
		EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);		
	}
	
	void UsbMidiController::HandleRealTimeSystem(uint8_t realtimebyte)
	{
		// idk what this is for - we already have start, stop etc
	}
	
	void UsbMidiController::myNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
	{	
		UsbMidiController::GetInstance()->HandleNoteOn(channel, note, velocity);
	}
	void UsbMidiController::myNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
	{	
		UsbMidiController::GetInstance()->HandleNoteOff(channel, note, velocity);
	}
	void UsbMidiController::myAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t velocity)
	{	
		UsbMidiController::GetInstance()->HandleAfterTouchPoly(channel, note, velocity);
	}
	void UsbMidiController::myControlChange(uint8_t channel, uint8_t control, uint8_t value)
	{	
		UsbMidiController::GetInstance()->HandleControlChange(channel, control, value);
	}
	void UsbMidiController::myProgramChange(uint8_t channel, uint8_t program)
	{	
		UsbMidiController::GetInstance()->HandleProgramChange(channel, program);
	}
	void UsbMidiController::myAfterTouch(uint8_t channel, uint8_t pressure)
	{	
		UsbMidiController::GetInstance()->HandleAfterTouch(channel, pressure);
	}
	void UsbMidiController::myPitchChange(uint8_t channel, int pitch)
	{	
		UsbMidiController::GetInstance()->HandlePitchChange(channel, pitch);
	}
	void UsbMidiController::mySystemExclusiveChunk(const uint8_t *data, uint16_t length, bool last)
	{	
		UsbMidiController::GetInstance()->HandleSystemExclusiveChunk(data, length, last);
	}
	void UsbMidiController::mySystemExclusive(uint8_t *data, unsigned int length)
	{	
		UsbMidiController::GetInstance()->HandleSystemExclusive(data, length);
	}
	void UsbMidiController::myTimeCodeQuarterFrame(uint8_t data)
	{	
		UsbMidiController::GetInstance()->HandleTimeCodeQuarterFrame(data);
	}
	void UsbMidiController::mySongPosition(uint16_t beats)
	{	
		UsbMidiController::GetInstance()->HandleSongPosition(beats);
	}
	void UsbMidiController::mySongSelect(uint8_t songNumber)
	{	
		UsbMidiController::GetInstance()->HandleSongSelect(songNumber);
	}
	void UsbMidiController::myTuneRequest()
	{	
		UsbMidiController::GetInstance()->HandleTuneRequest();
	}
	void UsbMidiController::myClock()
	{	
		UsbMidiController::GetInstance()->HandleClock();
	}
	void UsbMidiController::myStart()
	{	
		UsbMidiController::GetInstance()->HandleStart();
	}
	void UsbMidiController::myContinue()
	{	
		UsbMidiController::GetInstance()->HandleContinue();
	}
	void UsbMidiController::myStop()
	{	
		UsbMidiController::GetInstance()->HandleStop();
	}
	void UsbMidiController::myActiveSensing()
	{	
		UsbMidiController::GetInstance()->HandleActiveSensing();
	}
	void UsbMidiController::mySystemReset()
	{	
		UsbMidiController::GetInstance()->HandleSystemReset();
	}
	void UsbMidiController::myRealTimeSystem(uint8_t realtimebyte)
	{	
		UsbMidiController::GetInstance()->HandleRealTimeSystem(realtimebyte);
	}

	void UsbMidiController::SendNoteOn(int note, int velocity, int channel)
	{
		usbMIDI.sendNoteOn(note, velocity, channel);
	}
	
	void UsbMidiController::SendNoteOff(int note, int velocity, int channel)
	{
		usbMIDI.sendNoteOff(note, velocity, channel);
	}
	
	void UsbMidiController::SendAfterTouchPoly(int note, int pressure, int channel)
	{
		usbMIDI.sendAfterTouchPoly(note, pressure, channel);
	}
	
	void UsbMidiController::SendControlChange(int control, int value, int channel)
	{
		usbMIDI.sendControlChange(control, value, channel);
	}
	
	void UsbMidiController::SendProgramChange(int program, int channel)
	{
		usbMIDI.sendProgramChange(program, channel);
	}
	
	void UsbMidiController::SendAfterTouch(int pressure, int channel)
	{
		usbMIDI.sendAfterTouch(pressure, channel);
	}
	
	void UsbMidiController::SendPitchBend(int value, int channel)
	{
		usbMIDI.sendPitchBend(value, channel);
	}
	
	void UsbMidiController::SendSysEx(int length, const uint8_t *data, bool hasTerm)
	{
		usbMIDI.sendSysEx(length, data, hasTerm);
	}
	
	void UsbMidiController::SendTimeCodeQuarterFrame(int index, int value)
	{
		usbMIDI.sendTimeCodeQuarterFrame(index, value);
	}
	
	void UsbMidiController::SendSongPosition(int beats)
	{
		usbMIDI.sendSongPosition(beats);
	}
	
	void UsbMidiController::SendSongSelect(int song)
	{
		usbMIDI.sendSongSelect(song);
	}
	
	void UsbMidiController::SendTuneRequest()
	{
		usbMIDI.sendTuneRequest();
	}
	
	void UsbMidiController::SendClock()
	{
		usbMIDI.sendRealTime(usbMIDI.Clock);
	}
	
	void UsbMidiController::SendStart()
	{
		usbMIDI.sendRealTime(usbMIDI.Start);
	}
	
	void UsbMidiController::SendContinue()
	{
		usbMIDI.sendRealTime(usbMIDI.Continue);
	}
	
	void UsbMidiController::SendStop()
	{
		usbMIDI.sendRealTime(usbMIDI.Stop);
	}
	
	void UsbMidiController::SendActiveSensing()
	{
		usbMIDI.sendRealTime(usbMIDI.ActiveSensing);
	}
	
	void UsbMidiController::SendSystemReset()
	{
		usbMIDI.sendRealTime(usbMIDI.SystemReset);
	}	
}

#endif

// MidiEvent

#pragma once

#include "Event.h"

namespace Atomic
{
	enum class MidiSourceId {
		Internal,
		USB,
		MidiPort,
	};

	typedef uint8_t MidiChannel;

	class MidiEvent : public Event
	{
	public:
		MidiEvent(MidiSourceId midiSourceId) : mMidiSourceId(midiSourceId) {}
		virtual ~MidiEvent() {}
		MidiSourceId GetMidiSourceId() const { return mMidiSourceId; }
	private:
		MidiSourceId mMidiSourceId;
	};

	enum class MidiSystemCommonMessageId {
		SongSelect,
		SongPositionPointer,
		MidiTimeCodeQuarterFrame,
		TuneRequest,
		EOX,
	};

	class MidiSystemCommonMessageEvent : public MidiEvent
	{
	public:
		MidiSystemCommonMessageEvent(MidiSystemCommonMessageId systemCommonMessageId, MidiSourceId midiSourceId, int value) 
			: MidiEvent(midiSourceId)
			, mMidiSystemCommonMessageId(systemCommonMessageId)
			, mValue(value) {}
		EventType GetEventType() const { return EventType::MidiSystemRealTimeMessage; }
		MidiSystemCommonMessageId GetMidiSystemCommonMessageId() const { return mMidiSystemCommonMessageId; }
		int GetValue() const { return mValue; }
	private:
		MidiSystemCommonMessageId mMidiSystemCommonMessageId;
		int mValue;
	};

	enum class MidiSystemRealTimeMessageId {
		// Timing Clock F8H 
		TimingClock,
		// Start FAH
		Start, 
		// Continue FBH 
		Continue,
		// Stop FCH 
		Stop,
		// Active Sensing FEH 
		ActiveSensing,
		// System Reset FFH
		SystemReset,
	};

	class MidiSystemRealTimeMessage : public MidiEvent
	{
	public:
		MidiSystemRealTimeMessage(MidiSystemRealTimeMessageId systemRealTimeMessageId, MidiSourceId midiSourceId) 
			: MidiEvent(midiSourceId)
			, mSystemRealTimeMessageId(systemRealTimeMessageId) {}
		EventType GetEventType() const { return EventType::MidiSystemRealTimeMessage; }
		MidiSystemRealTimeMessageId GetSystemRealTimeMessageId() const { return mSystemRealTimeMessageId; }
	private:
		MidiSystemRealTimeMessageId mSystemRealTimeMessageId;
	};

	enum class MidiChannelMessageEventId
	{
		NoteOn,
		NoteOff,
		ControlChange,
		AfterTouchPoly,
		ProgramChange,
		AfterTouchChannel,
		PitchBend,
	};

	class MidiChannelMessageEvent : public MidiEvent
	{
		// Channel Voice Messages - note on, note off, cc, program change, after touch, pitch bend
		// Channel Mode Message (mono/poly, omni on/off)
		// cc 8 - balance
		// cc 10 - pan
		// cc 11/20 - bank select
		// cc 72 - attack
		// cc 73 - release
		// cc 54 - portamento
		// status:
		// All Sound Off 120 
		// Reset All Controllers 121 
		// Local Control 122 
		// All Notes Off 123 
		// Omni Off 124 Omni On 125 Mono On (Poly Off) 126 Poly On (Mono Off) 127
		// ? pitch bend, aftertouch, program change
	public:
		MidiChannelMessageEvent(MidiChannelMessageEventId midiChannelMessageEventId, MidiSourceId midiSourceId, int channel, int byte1, int byte2)
		: MidiEvent(midiSourceId)
		, mMidiChannelMessageEventId(midiChannelMessageEventId) 
		, mChannel(channel)
		, mValue1(byte1)
		, mValue2(byte2)
		{}
		EventType GetEventType() const { return EventType::MidiChannelMessage; }
		MidiChannelMessageEventId GetMidiChannelMessageEventId() const { return mMidiChannelMessageEventId; }
		int GetChannel() const { return mChannel; }
		int GetValue1() const { return mValue1; }
		int GetValue2() const { return mValue2; }
	private:
		MidiChannelMessageEventId mMidiChannelMessageEventId;
		MidiSourceId mMidiSourceId;
		int mChannel;
		int mValue1;
		int mValue2;
	};

	class MidiSystemMessageEvent : public MidiEvent
	{
		// System Common:
		// MIDI Time Code Quarter Frame F1H 
		// 	Quarter Frame message communicates the Frame, Seconds, Minutes and Hours Count in an 8-message sequence
		//	There is also an MTC FULL FRAME message which is a MIDI System Exclusive Message

		// Song Position Pointer F2H
		//	A sequencer's Song Position (SP) is the number of MIDI beats (1 beat = 6 MIDI clocks) that have elapsed 
		// 	from the start of the song and is used to begin playback of a sequence from a position other than the beginning of the song. 
		// 	It is normally set to 0 when the START button is pressed to start sequence playback from the very beginning. 
		// 	It is incremented every sixth MIDI clock until STOP is pressed. If CONTINUE is pressed, it continues to increment from its current value. 
		//	The current Song Position can be communicated via the Song Position Pointer message and can be changed in a receiver 
		//	by an incoming Song Position Pointer message. This message should only be recognized if the receiver is set to MIDI sync (external) mode.

		// Song Select F3H
		// Tune Request F6H 
		// EOX (End of Exclusive) F7H
		// MidiSystemMessageEvent - System Exclusive Message, System Real Time Message
		// All other messages (status, data byte, data byte)
	};
}
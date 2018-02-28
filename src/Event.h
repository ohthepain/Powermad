// Event.h

#include <stdint.h>
#include <functional>
#include <stdlib.h>

namespace std {
    void __throw_bad_function_call();
}

namespace Atomic
{
  template<class T> class Vector
  {
      public:
        Vector();
        ~Vector();

        void Add(T value);
        void Remove(T value);
        T& operator[](int index);
        void Clear();
        size_t GetSize() { return mSize; }

      private:
        T* mNodes;
        size_t mSize;
        size_t mCapacity;
  };
  
	class Event
	{
		public:
			typedef enum {
				MidiNote,
				MidiPlay,
				MidiStop,
				MidiContinue,
				MillisecondClock,
				MidiClock,
        KeyPress,
        RawKey,
        ArraySize,
			} EventType;

      typedef enum {
        Illegal,
        Sequence,
        TopLeft,
        Note6,
        Note4,
        Note3,
        Note2,
        Note1,
        Seq,
        Note0,
        SecondFromTopLeft,
        IdkLeft,
        Release,
        Attack,
        Button13,
        Note7,
        Shift,
        Note8,
        Gate,
        Button18,
        Button19,
        Button20,
        A,
        Play,
        Stop,
        IdkRight,
        Chase,
        Button26,
      } KeyId;
		
			typedef enum {
				PriorityMax = 0,
				High = 10,
				Medium = 100,
				Low = 1000,
			} Priority;

			Event() {}
			virtual ~Event() {}

			virtual EventType GetEventType() const = 0;
	};

  class MillisecondClockEvent : public Event
  {
    EventType GetEventType() const { return Event::MillisecondClock; }
  };

  class KeyPressEvent : public Event
  {
    public:
      KeyPressEvent(KeyId keyId, uint8_t modifiers) : mKeyId(keyId), mModifiers(modifiers) {}
      EventType GetEventType() const { return Event::MillisecondClock; }
      KeyId GetKeyId() const { return mKeyId; }
      uint8_t GetModifiers() const { return mModifiers; }
    private:
      KeyId mKeyId;
      uint8_t mModifiers;
  };
	
	class EventController
	{
    public:
      typedef std::function<int()> EventHandler;

		public:
			static void Init();
			static void Shutdown();
			static EventController* GetInstance() { return mInstance; }

			void AddEventHandler(Event::EventType type, Event::Priority priority, EventHandler eventHandler);
      void BroadcastEvent(const Event& event);

		private:
			EventController();
			virtual ~EventController();

			static EventController* mInstance;

			bool mBusy;

      typedef Atomic::Vector<EventHandler> EventHandlerList;
      EventHandlerList* mHandlerMap;
      EventHandlerList* mHandlerAddQueue;
      EventHandlerList* mHandlerRemoveQueue;
	};

	class MidiNoteEvent : public Event
	{
		public:
			EventType GetEventType() const { return MidiNote; }

		private:
			uint16_t mDuration;
			uint8_t mNote;
			uint8_t mVelocity;
	};

	class MidiEvent : public Event
	{
		public:
			MidiEvent(EventType eventType) { mEventType=eventType; }
			virtual ~MidiEvent() {}

		private:
			EventType mEventType;
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

		// SYSTEM REAL TIME MESSAGES
		// Timing Clock F8H 
		// Start FAH 
		// Continue FBH 
		// Stop FCH 
		// Active Sensing FEH 
		// System Reset FFH
	};

	class MidiSystemExclusiveMessageEvent : public MidiEvent
	{
		// System Exclusive Message (status, data bytes, EOX)
	};

	class MidiSongPositionPointer
	{
		
	};

	class NavigationEvent : public Event
	{
		MidiSongPositionPointer mSpp;
	};
}

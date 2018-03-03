// Event.h

#pragma once

#include <stdint.h>
#include <functional>
#include <myassert.h>

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

	enum class EventType {
		MillisecondClock,
		SecondClock,
		MidiChannelMessage,
		MidiSystemRealTimeMessage,
		MidiSystemCommonMessage,
		KeyPress,
		SetView,
		RawKey,
		ArraySize,
	};

	class Event
	{
	public:
		typedef enum {
			IllegalAnalogInput,
			LeftJoystickX,
			LeftJoystickY,
			RightJoystickX,
			RightJoystickY,
			NumAnalogInputs,
		} AnalogInputId;

		typedef enum {
			Illegal = 0,
			Sequence,
			TopLeft,
			Note6,
			Note5,
			Note4,
			Note3,
			Note2,
			Note1,
			Arp,
			SecondFromTopLeft,
			IdkLeft,
			Release,
			Attack,
			Note7,
			Shift,
			Note8,
			Gate,
			Button18,
			Button19,
			B,
			A,
			Play,
			Stop,
			IdkRight,
			Chase,
			Song,
			LeftJoystickButton,
			RightJoystickButton,
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

	class SecondClockEvent : public Event
	{
		EventType GetEventType() const { return EventType::SecondClock; }
	};

	class MillisecondClockEvent : public Event
	{
		EventType GetEventType() const { return EventType::MillisecondClock; }
	};

	class RawKeyEvent : public Event
	{
	public:
		RawKeyEvent(KeyId keyId, bool up) : mKeyId(keyId), mUp(up) {}
		EventType GetEventType() const { return EventType::RawKey; }
		KeyId GetKeyId() const { return mKeyId; }
		bool GetUp() const { return mUp; }
	private:
		KeyId mKeyId;
		bool mUp;		
	};

	class KeyPressEvent : public Event
	{
	public:
		KeyPressEvent(KeyId keyId, uint8_t modifiers) : mKeyId(keyId), mModifiers(modifiers) {}
		EventType GetEventType() const { return EventType::KeyPress; }
		KeyId GetKeyId() const { return mKeyId; }
		uint8_t GetModifiers() const { return mModifiers; }
	private:
		KeyId mKeyId;
		uint8_t mModifiers;
	};
	
	class EventController
	{
	public:
		typedef std::function<int(const Event&)> EventHandler;

		static void Init();
		static void Shutdown();
		static EventController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		void AddEventHandler(EventType type, EventHandler eventHandler);
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
}

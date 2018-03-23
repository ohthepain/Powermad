// JoystickManager.h

#pragma once

#include "Event.h"
#include <stdint.h>
#include <myassert.h>

namespace Atomic
{
	enum class JoystickAxisId {
		LeftX,
		LeftY,
		RightX,
		RightY,
	};

	class JoystickAxisEvent : public Event
	{
	public:
		JoystickAxisEvent(JoystickAxisId joystickAxisId, int value, size_t divisor) 
			: mJoystickAxisId(joystickAxisId), mValue(value), mDivisor(divisor) {}
		virtual ~JoystickAxisEvent() {}

		EventType GetEventType() const { return EventType::JoystickAxis; }
		JoystickAxisId GetJoystickAxisId() const { return mJoystickAxisId; }
		int GetValue() const { return mValue; }
		size_t GetDivisor() const { return mDivisor; }
		
	private:
		JoystickAxisId mJoystickAxisId;
		int mValue;
		uint32_t mDivisor;
	};

	class JoystickManager
	{
	public:
		static void Init();
		static void Shutdown();
		static JoystickManager* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		void AddJoytickAxis(JoystickAxisId joystickAxisId, AnalogInputId analogInputId);

	private:
		typedef struct {
			JoystickAxisId joystickAxisId;
			AnalogInputId analogInputId;
			int centerValue;
			uint32_t lastMessageTime[4];
		} tJoystick;

		Vector<tJoystick> mJoysticks;

		static JoystickManager* mInstance;
		JoystickManager();
		virtual ~JoystickManager();

		void HandleMidiSystemRealTimeMessage(const Event& event);
		void HandleMidiTimingClock();

		void CheckJoystickAxis(size_t n);
	};
}

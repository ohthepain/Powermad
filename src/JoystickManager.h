// JoystickManager.h

#pragma once

#include "Event.h"
#include <stdint.h>
#include <myassert.h>

namespace Atomic
{
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
			uint32_t lastMessageTime;
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

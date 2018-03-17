// InputPinManager.h

#pragma once

#include "Event.h"
#include <stdint.h>
#include <myassert.h>

namespace Atomic
{
	typedef struct {
		KeyId keyId;
		uint8_t pinNumber;
	} tPinToKeyAssigment;

	typedef struct {
		AnalogInputId analogInputId;
		uint8_t pinNumber;
	} tPinToAnalogInputAssigment;

	class InputPinManager
	{
	public:
		static void Init();
		static void Shutdown();
		static InputPinManager* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		void AddDigitalInputPin(int pinNumber, KeyId rawButtonNumber);
		void AddAnalogInputPin(int pinNumber, AnalogInputId analogInputId);
		float ReadAnalogInputValue(AnalogInputId analogInputId);

	private:
		static InputPinManager* mInstance;
		InputPinManager();
		virtual ~InputPinManager();

		void HandleMillisecondClock();
		void HandleMidiSystemRealTimeMessage(const Event& event);
		void HandleMidiTimingClock();

		uint32_t mSavedKeyState;
		uint32_t mTimeLastKeyStateChange;
		uint32_t mTempKeyState;

		const size_t kMaxPinToKeyAssignments = 8;
		const size_t kMaxPinToAnalogInputAssignments = 8;
		size_t mNumPinToKeyAssigments;
		size_t mNumPinToAnalogInputAssigments;
		tPinToKeyAssigment* mPinToKeyAssignments;
		tPinToAnalogInputAssigment* mPinToAnalogInputAssigments;
	};
}

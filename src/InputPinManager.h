// InputPinManager.h

#pragma once

#include "Event.h"
#include <stdint.h>
#include <myassert.h>

namespace Atomic
{
	typedef uint8_t tAnalogInputId;

	typedef struct {
		Event::KeyId keyId;
		uint8_t pinNumber;
	} tPinToKeyAssigment;

	typedef struct {
		tAnalogInputId analogInputId;
		uint8_t pinNumber;
	} tPinToAnalogInputAssigment;

	class InputPinManager
	{
	public:
		static void Init();
		static void Shutdown();
		static InputPinManager* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		void AddDigitalInputPin(int pinNumber, Event::KeyId rawButtonNumber);
		void AddAnalogInputPin(int pinNumber, tAnalogInputId analogInputId);
		float GetAnalogInputValue(tAnalogInputId analogInputId);

	private:
		static InputPinManager* mInstance;
		InputPinManager();
		virtual ~InputPinManager();

		void HandleMillisecondClock();

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

// InputPinManager.cpp

#include "InputPinManager.h"
#include <Arduino.h>

namespace Atomic
{
	InputPinManager* InputPinManager::mInstance = nullptr;

	InputPinManager::InputPinManager()
	: mSavedKeyState(0)
	, mTimeLastKeyStateChange(0)
	, mTempKeyState(0)
	, mNumPinToKeyAssigments(0)
	, mNumPinToAnalogInputAssigments(0)
	{
		mPinToKeyAssignments = new tPinToKeyAssigment[kMaxPinToKeyAssignments];
		mPinToAnalogInputAssigments = new tPinToAnalogInputAssigment[kMaxPinToAnalogInputAssignments];

		EventController::EventHandler myFunction = [&](const Event& event) { this->HandleMillisecondClock(); return 0; };
    	EventController::GetInstance()->AddEventHandler(Event::MillisecondClock, myFunction);
	}

	InputPinManager::~InputPinManager()
	{
		delete [] mPinToKeyAssignments;
		mPinToKeyAssignments = nullptr;
		delete [] mPinToAnalogInputAssigments;
		mPinToAnalogInputAssigments = nullptr;
	}

	void InputPinManager::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new InputPinManager();
	}

	void InputPinManager::Shutdown()
	{
		assert(mInstance == nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	void InputPinManager::AddDigitalInputPin(int pinNumber, Event::KeyId rawButtonNumber)
	{
		assert(mNumPinToKeyAssigments < kMaxPinToKeyAssignments);
		mPinToKeyAssignments[mNumPinToKeyAssigments].pinNumber = pinNumber;
		mPinToKeyAssignments[mNumPinToKeyAssigments].keyId = rawButtonNumber;
		++mNumPinToKeyAssigments;

		pinMode(pinNumber, INPUT_PULLUP);
	}

	void InputPinManager::AddAnalogInputPin(int pinNumber, tAnalogInputId analogInputId)
	{
		assert(mNumPinToAnalogInputAssigments < kMaxPinToAnalogInputAssignments);
		mPinToAnalogInputAssigments[mNumPinToAnalogInputAssigments].pinNumber = pinNumber;
		mPinToAnalogInputAssigments[mNumPinToAnalogInputAssigments].analogInputId = analogInputId;
		++mNumPinToAnalogInputAssigments;

		pinMode(pinNumber, INPUT);
	}

	float InputPinManager::GetAnalogInputValue(tAnalogInputId analogInputId)
	{
		for (size_t n=0; n<mNumPinToAnalogInputAssigments; n++)
		{
			if (mPinToAnalogInputAssigments[n].analogInputId == analogInputId)
			{
				float val = analogRead(mPinToAnalogInputAssigments[n].pinNumber);
				return val;
			}
		}
		assert(false && "unregistered analog input");
	}

	void InputPinManager::HandleMillisecondClock()
	{
		unsigned long keyState = 0;
		for (size_t n=0; n < mNumPinToKeyAssigments; n++)
		{
			int pinNumber = mPinToKeyAssignments[n].pinNumber;
			if (digitalRead(pinNumber) == LOW)
			{
				keyState = keyState | (1 << n);
			}
		}
		if (keyState != mTempKeyState)
		{
			mTempKeyState = keyState;
			mTimeLastKeyStateChange = millis();
		}
		if (mTimeLastKeyStateChange != 0)
		{
			if (millis() - mTimeLastKeyStateChange > 3)
			{
				mTimeLastKeyStateChange = 0;

				uint32_t keymask = 1;
				for (size_t i=0; i<mNumPinToKeyAssigments; i++)
				{
					if ((mSavedKeyState ^ keyState) & keymask)
					{
						bool up = (keyState & keymask) == 0;
						RawKeyEvent rawKeyEvent(mPinToKeyAssignments[i].keyId, up);
						EventController::GetInstance()->BroadcastEvent(rawKeyEvent);
					}
					keymask <<= 1;
				}
				mSavedKeyState = keyState;
			}
		}
	}
}

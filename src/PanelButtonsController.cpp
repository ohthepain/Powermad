// PanelButtonsController.cpp

#include "Event.h"
#include "PanelButtonsController.h"
#include <Arduino.h>

namespace Atomic
{
	PanelButtonsController* PanelButtonsController::mInstance = nullptr;

	void PanelButtonsController::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new PanelButtonsController();
	}

	void PanelButtonsController::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	PanelButtonsController::PanelButtonsController()
	: mSavedKeyState(0)
	, mTimeLastKeyStateChange(0)
	, mTempKeyState(0)
	{
		pinMode(kClockPin, OUTPUT);
		pinMode(kDataPin, OUTPUT);
		pinMode(kInputPin, INPUT);

    EventController::EventHandler myFunction = [&](const Event& event) { this->Update(); return 0; };
    EventController::GetInstance()->AddEventHandler(Event::MillisecondClock, myFunction);
		EventController::EventHandler myFunction2 = [&](const Event& event) { this->HandleRawKeyEvent(event); return 0; };
    EventController::GetInstance()->AddEventHandler(Event::RawKey, myFunction2);
	}

  int PanelButtonsController::HandleTimer()
  {
    return 0;
  }

	uint32_t PanelButtonsController::ScanKeys()
	{
		uint32_t keyStates = 0;
		digitalWrite(kDataPin, HIGH);
		digitalWrite(kClockPin, HIGH);
		digitalWrite(kClockPin, LOW);
		digitalWrite(kDataPin, LOW);
		uint32_t keymask = 1;

		for (int i=0; i<32; i++)
		{
			digitalWrite(kClockPin, HIGH);
			digitalWrite(kClockPin, LOW);
			int keyState = digitalRead(kInputPin);
			if (keyState == HIGH)
			{
				keyStates |= keymask;
			}
			keymask <<= 1;
		}
		return keyStates;
	}

  static uint8_t ButtonInfo = {
    
  };

  void PanelButtonsController::HandleRawKeyEvent(const Event& event)
  {
		static bool shift = false;
		const RawKeyEvent& rawKeyEvent = static_cast<const RawKeyEvent&>(event);

		if (rawKeyEvent.GetKeyId() == Event::Shift)
		{
			shift = !rawKeyEvent.GetUp();
		}
		else if (!rawKeyEvent.GetUp())
		{
			uint8_t modifiers = 0;
			if (shift)
			{
				modifiers |= 0x01;
			}
			//Serial.print("key press: "); Serial.print(rawKeyEvent.GetKeyId()); Serial.print(" modifiers: "); Serial.println(modifiers);
	    KeyPressEvent keyPressEvent((Event::KeyId)1, modifiers);
  	  EventController::GetInstance()->BroadcastEvent(keyPressEvent);
		}
  }

	void PanelButtonsController::Update() 
	{
		unsigned long keyState = ScanKeys();
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
        for (int i=1; i<=32; i++)
        {
          if ((mSavedKeyState ^ keyState) & keymask)
          {
						//Serial.print("mSavedKeyState: "); Serial.print(mSavedKeyState); Serial.print(", keyState: "); Serial.print(keyState); Serial.print(", keymask: "); Serial.println(keymask);
						//Serial.print("mSavedKeyState and keymask: "); Serial.print(mSavedKeyState & keymask); Serial.print(", keyState and keymask: "); Serial.println(keyState & keymask); 

						bool up = (keyState & keymask) == 0;
						RawKeyEvent rawKeyEvent((Event::KeyId)i, up);
            EventController::GetInstance()->BroadcastEvent(rawKeyEvent);
          }
          keymask <<= 1;
        }
				mSavedKeyState = keyState;
			}
		}
	}
}

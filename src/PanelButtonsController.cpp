// PanelButtonsController.cpp

#include "Event.h"
#include "PanelButtonsController.h"
#include <Arduino.h>

namespace Atomic
{
	TimerController* TimerController::mInstance = nullptr;
	PanelButtonsController* PanelButtonsController::mInstance = nullptr;

	TimerController::TimerController()
	{
		mEventController = EventController::GetInstance();
		assert(mEventController != nullptr);

    Serial.println("Start timer");
		mTimer = new IntervalTimer();
		mTimer->begin(TimerController::HandleTimer, 1000);
	}

	TimerController::~TimerController()
	{
		mTimer->end();
		delete mTimer;
		mTimer = nullptr;
	}

	void TimerController::Init()
	{
		mInstance = new TimerController();
	}

	void TimerController::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	//	Timer
	void TimerController::HandleTimer()
	{
		static int n = 0;
		if (++n > 1000)
		{
			Serial.println("handleTimer: second");
			n = 0;
		}
    static MillisecondClockEvent millisecondClockEvent;
    EventController::GetInstance()->BroadcastEvent(millisecondClockEvent);
	}

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

    EventController::EventHandler myFunction = [&]() { this->Update(); return 0; };
    EventController::GetInstance()->AddEventHandler(Event::MillisecondClock, Event::PriorityMax, myFunction);
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

  void PanelButtonsController::HandleRawKeyPress(int keynum)
  {
    Serial.print("HandleRawKeyPress: "); Serial.println(keynum);
  }

	void PanelButtonsController::Update() 
	{
		unsigned long keyState = ScanKeys();
		if (keyState != mTempKeyState)
		{
      Serial.print("RAW key state change: "); Serial.println(keyState);
			mTempKeyState = keyState;
			mTimeLastKeyStateChange = millis();
		}
		if (mTimeLastKeyStateChange != 0)
		{
			if (millis() - mTimeLastKeyStateChange > 2)
			{
				Serial.print("key state change: "); Serial.println(keyState);
				mSavedKeyState = keyState;
				mTimeLastKeyStateChange = 0;

        uint32_t keymask = 1;
        for (int i=1; i<=32; i++)
        {
          if (keyState & keymask)
          {
            KeyPressEvent keyPressEvent((Event::KeyId)i, 0);
            EventController::GetInstance()->BroadcastEvent(keyPressEvent);
          }
          keymask <<= 1;
        }
			}
		}
	}
}

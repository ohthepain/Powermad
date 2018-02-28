// PanelButtonsController.cpp

#include "Event.h"
#include "TimerController.h"
#include <Arduino.h>

namespace Atomic
{
	TimerController* TimerController::mInstance = nullptr;

	TimerController::TimerController()
	{
		mEventController = EventController::GetInstance();

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
}

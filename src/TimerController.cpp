// TimerController.cpp

#include "Event.h"
#include "TimerController.h"
#include <Arduino.h>

namespace Atomic
{
	TimerController* TimerController::mInstance = nullptr;

	TimerController::TimerController()
	{
		mEventController = EventController::GetInstance();

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
		static MillisecondClockEvent millisecondClockEvent;
		EventController::GetInstance()->BroadcastEvent(millisecondClockEvent);
		static SecondClockEvent secondClockEvent;
		static uint32_t lastSecondTime = millis();
		if (millis() > lastSecondTime + 1000)
		{
			EventController::GetInstance()->BroadcastEvent(secondClockEvent);
			lastSecondTime = millis();
		}
	}
}

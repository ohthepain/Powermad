// InternalMidiClock.cpp

#include "InternalMidiClock.h"
#include <Arduino.h>
#include "NavigationController.h"
#include "Song.h"

#define LED_PIN 13

namespace Atomic
{
	InternalMidiClock* InternalMidiClock::mInstance = nullptr;

	InternalMidiClock::InternalMidiClock()
	{
	    Serial.println("Hi from InternalMidiClock");

		pinMode(LED_PIN, OUTPUT);

		mLastMidiPulseTime = (double)millis();

		EventController* eventController = EventController::GetInstance();
		EventController::EventHandler myFunction = [&](const Event& event) -> int { this->HandleMillisecondEvent(); return 0; };
		eventController->AddEventHandler(Event::MillisecondClock, myFunction);
	}

	void InternalMidiClock::Init()
	{
		mInstance = new InternalMidiClock();
	}

	void InternalMidiClock::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	//	Timer
	void InternalMidiClock::HandleMillisecondEvent()
	{
		static NavigationController* navigationController = NavigationController::GetInstance();
		double tempo = navigationController->GetSong()->GetTempo();
		// 16 pulses per quarter note
		double msecPerPulse = (tempo * (double) 1000) / 16 / 60 / 4;
		double currentTime = (double)millis();
		if (currentTime - mLastMidiPulseTime >= msecPerPulse)
		{
			mLastMidiPulseTime += msecPerPulse;
			static MidiClockEvent midiClockEvent;
			EventController::GetInstance()->BroadcastEvent(midiClockEvent);
		}
	}
}

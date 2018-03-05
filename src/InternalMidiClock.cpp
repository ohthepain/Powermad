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
		eventController->AddEventHandler(EventType::MillisecondClock, myFunction);
		EventController::EventHandler myFunction2 = [&](const Event& event) -> int { this->HandleKeyPress(event); return 0; };
		eventController->AddEventHandler(EventType::KeyPress, myFunction2);
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

	void InternalMidiClock::HandleKeyPress(const Event& event)
	{
		const KeyPressEvent& keyPressEvent = static_cast<const KeyPressEvent&>(event);
		switch (keyPressEvent.GetKeyId())
		{
			case Event::Play:
			{
				static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Continue, MidiSourceId::Internal);
				EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
				break;
			}
			case Event::Stop:
			{
				static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::Stop, MidiSourceId::Internal);
				EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);
				break;
			}
			default:
				break;
		}
	}

	void InternalMidiClock::HandleMillisecondEvent()
	{
		static NavigationController* navigationController = NavigationController::GetInstance();
		double tempo = navigationController->GetCurrentSong()->GetTempo();
		// 16 pulses per quarter note
		double msecPerPulse = (tempo * (double) 1000) / 16 / 60 / 4;
		double currentTime = (double)millis();
		if (currentTime - mLastMidiPulseTime >= msecPerPulse)
		{
			mLastMidiPulseTime += msecPerPulse;
			static MidiSystemRealTimeMessage systemRealTimeMessage(MidiSystemRealTimeMessageId::TimingClock, MidiSourceId::Internal);
			EventController::GetInstance()->BroadcastEvent(systemRealTimeMessage);	
		}
	}
}

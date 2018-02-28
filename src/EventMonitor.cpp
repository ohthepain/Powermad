// EventMonitor.cpp

#include "EventMonitor.h"
#include <Arduino.h>

namespace Atomic
{
	EventMonitor* EventMonitor::mInstance = nullptr;
	
	void EventMonitor::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new EventMonitor();
	}

	void EventMonitor::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	EventMonitor::EventMonitor()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(Event::MidiNote, handler);
		EventController::GetInstance()->AddEventHandler(Event::MidiPlay, handler);
		EventController::GetInstance()->AddEventHandler(Event::MidiStop, handler);
		EventController::GetInstance()->AddEventHandler(Event::MidiContinue, handler);
		//EventController::GetInstance()->AddEventHandler(Event::MillisecondClock, handler);
		//EventController::GetInstance()->AddEventHandler(Event::MidiClock, handler);
		EventController::GetInstance()->AddEventHandler(Event::KeyPress, handler);
		//EventController::GetInstance()->AddEventHandler(Event::RawKey, handler);
	}

	EventMonitor::~EventMonitor()
	{
	}

	void EventMonitor::HandleEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		case Event::MidiNote:
			Serial.println("Event: MidiNote");
			break;
		case Event::MidiPlay:
			Serial.println("Event: MidiPlay");
			break;
		case Event::MidiStop:
			Serial.println("Event: MidiStop");
			break;
		case Event::MidiContinue:
			Serial.println("Event: MidiContinue");
			break;
		case Event::MillisecondClock:
			Serial.println("Event: MillisecondClock");
			break;
		case Event::MidiClock:
			Serial.println("Event: MidiClock");
			break;
		case Event::KeyPress:
			Serial.println("Event: KeyPress");
			break;
		case Event::RawKey:
			Serial.println("Event: RawKey");
			break;
		default:
			assert(0 && "Illegal event type");
		}
	}
}

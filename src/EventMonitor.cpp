// EventMonitor.cpp

#include "EventMonitor.h"
#include <Arduino.h>

namespace Atomic
{
	EventMonitor* EventMonitor::mInstance = nullptr;
	
	void EventMonitor::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new EventMonitor();
	}

	void EventMonitor::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	EventMonitor::EventMonitor()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
		//EventController::GetInstance()->AddEventHandler(EventType::MillisecondClock, handler);
		//EventController::GetInstance()->AddEventHandler(EventType::MidiClock, handler);
		//EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::RawKey, handler);
	}

	EventMonitor::~EventMonitor()
	{
	}

	void EventMonitor::HandleEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
		case EventType::MidiSystemRealTimeMessage:
			//Serial.println("Event: MidiSystemRealTimeMessage");
			break;
		case EventType::MillisecondClock:
			Serial.println("Event: MillisecondClock");
			break;
		case EventType::KeyPress:
			Serial.println("Event: KeyPress");
			break;
		case EventType::RawKey:
		{
			//const RawKeyEvent& rawKeyEvent = static_cast<const RawKeyEvent&>(event);
			break;
		}
		default:
			myassert(0 && "Illegal event type");
		}
	}
}

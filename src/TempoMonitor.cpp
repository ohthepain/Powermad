// TempoMonitor.cpp

#include "TempoMonitor.h"
#include "NavigationController.h"
#include <Arduino.h>

#define LED_PIN 13

namespace Atomic
{
	TempoMonitor* TempoMonitor::mInstance = nullptr;

	TempoMonitor::TempoMonitor()
	{
	    Serial.println("Hi from TempoMonitor");

		pinMode(LED_PIN, OUTPUT);

		EventController* eventController = EventController::GetInstance();
		EventController::EventHandler myFunction = [&]() { this->HandleMidiClock(); return 0; };
		eventController->AddEventHandler(Event::MidiClock, myFunction);
	}

	void TempoMonitor::Init()
	{
		mInstance = new TempoMonitor();
	}

	void TempoMonitor::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	//	Timer
	void TempoMonitor::HandleMidiClock()
	{
		static int count = 0;
		switch (count++)
		{
			case 15                          :
				digitalWrite(LED_PIN, HIGH);
				break;
			case 16:
				digitalWrite(LED_PIN, LOW);
				count = 0;
		}
	}
}

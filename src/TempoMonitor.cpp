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
		EventController::EventHandler myFunction = [&](const Event& event) { this->HandleMidiSystemRealTimeMessage(event); return 0; };
		eventController->AddEventHandler(EventType::MidiSystemRealTimeMessage, myFunction);
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

	void TempoMonitor::HandleMidiSystemRealTimeMessage(const Event& event)
	{
		const MidiSystemRealTimeMessage& systemRealTimeMessage = static_cast<const MidiSystemRealTimeMessage&>(event);
		if (systemRealTimeMessage.GetSystemRealTimeMessageId() == MidiSystemRealTimeMessageId::TimingClock)
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
}

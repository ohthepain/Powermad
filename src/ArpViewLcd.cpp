// ArpViewLcd.cpp

#include "ArpViewLcd.h"
#include "LcdDisplayController.h"
#include <Arduino.h>

namespace Atomic
{
	ArpViewLcd* ArpViewLcd::mInstance = nullptr;
	
	void ArpViewLcd::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new ArpViewLcd();
	}

	void ArpViewLcd::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	ArpViewLcd::ArpViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::SystemRealTimeMessage, handler);
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::SetView, handler);
	}

	void ArpViewLcd::HandleActiveEvent(const Event& event)
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (event.GetEventType())
		{
		case EventType::SetView:
			lcdDisplayController->Clear();
			lcdDisplayController->WriteToScreen(0, 0, "Arp");
			break;
		case EventType::MidiNote:
			lcdDisplayController->WriteToScreen(19, 1, "N");
			break;
		case EventType::SystemRealTimeMessage:
		{
			const SystemRealTimeMessage& systemRealTimeMessage = static_cast<const SystemRealTimeMessage&>(event);
			SystemRealTimeMessageId systemRealTimeMessageId = systemRealTimeMessage.GetSystemRealTimeMessageId();
			switch (systemRealTimeMessageId)
			{
			case SystemRealTimeMessageId::TimingClock:
				HandleMidiClock();
				break;
			case SystemRealTimeMessageId::Start:
				lcdDisplayController->WriteToScreen(19, 0, "P");
				break;
			case SystemRealTimeMessageId::Stop:
				lcdDisplayController->WriteToScreen(19, 1, "S");
				Serial.println("Event: MidiStop");
				break;
			case SystemRealTimeMessageId::Continue:
				lcdDisplayController->WriteToScreen(19, 1, "C");
				Serial.println("Event: MidiContinue");
				break;
			default:
				// Active Sensing or System Reset
				break;
			}
		}
		case EventType::MillisecondClock:
			//Serial.println("Event: MillisecondClock");
			break;
		case EventType::KeyPress:
			//Serial.println("Event: KeyPress");
			break;
		default:
			assert(0 && "ArpViewLcd: unhandled event");
		}
	}

	void ArpViewLcd::HandleMidiClock()
	{
	}
}

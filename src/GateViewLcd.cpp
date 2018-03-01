// GateViewLcd.cpp

#include "GateViewLcd.h"
#include "LcdDisplayController.h"
#include <Arduino.h>

namespace Atomic
{
	GateViewLcd* GateViewLcd::mInstance = nullptr;
	
	void GateViewLcd::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new GateViewLcd();
	}

	void GateViewLcd::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	GateViewLcd::GateViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::SystemRealTimeMessage, handler);
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::SetView, handler);
	}

	void GateViewLcd::HandleActiveEvent(const Event& event)
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (event.GetEventType())
		{
		case EventType::SetView:
			lcdDisplayController->Clear();
			lcdDisplayController->WriteToScreen(0, 0, "Gate");
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
			assert(0 && "GateViewLcd: unhandled event");
		}
	}

	void GateViewLcd::HandleMidiClock()
	{
	}
}

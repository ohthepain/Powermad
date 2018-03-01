// SongViewLcd.cpp

#include "SongViewLcd.h"
#include "LcdDisplayController.h"
#include <Arduino.h>

namespace Atomic
{
	SongViewLcd* SongViewLcd::mInstance = nullptr;
	
	void SongViewLcd::Init()
	{
		assert(mInstance == nullptr);
		mInstance = new SongViewLcd();
	}

	void SongViewLcd::Shutdown()
	{
		assert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	SongViewLcd::SongViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::SystemRealTimeMessage, handler);
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::SetView, handler);
	}

	void SongViewLcd::HandleActiveEvent(const Event& event)
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (event.GetEventType())
		{
		case EventType::SetView:
			lcdDisplayController->Clear();
			lcdDisplayController->WriteToScreen(0, 0, "Song");
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
			}
		}
		case EventType::MillisecondClock:
			//Serial.println("Event: MillisecondClock");
			break;
		case EventType::KeyPress:
			//Serial.println("Event: KeyPress");
			break;
		default:
			assert(0 && "SongViewLcd: unhandled event");
		}
	}

	void View::HandleEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
			case EventType::SetView:
			{
				const SetViewEvent& setViewEvent = static_cast<const SetViewEvent&>(event);
				ViewId viewId = setViewEvent.GetViewId();
				SetActive(viewId == GetViewId());
				break;
			}
			default:
				break;
		}

		if (IsActive())
		{
			HandleActiveEvent(event);
		}
	}
}

// GateViewLcd.cpp

#include "GateViewLcd.h"
#include "LcdDisplayController.h"
#include <Arduino.h>

namespace Atomic
{
	GateViewLcd* GateViewLcd::mInstance = nullptr;
	
	void GateViewLcd::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new GateViewLcd();
	}

	void GateViewLcd::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	GateViewLcd::GateViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
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
		case EventType::MidiChannelMessage:
		{
			const MidiChannelMessageEvent& midiChannelMessageEvent = static_cast<const MidiChannelMessageEvent&>(event);
			const char* s = "Z";
			switch (midiChannelMessageEvent.GetMidiChannelMessageEventId())
			{
				case MidiChannelMessageEventId::NoteOn:
					s = "N";
					break;
				case MidiChannelMessageEventId::NoteOff:
					s = "O";
					break;
				case MidiChannelMessageEventId::ControlChange:
					s = "C";
					break;
				case MidiChannelMessageEventId::AfterTouchPoly:
					s = "A";
					break;
				case MidiChannelMessageEventId::ProgramChange:
					s = "P";
					break;
				case MidiChannelMessageEventId::AfterTouchChannel:
					s = "X";
					break;
				case MidiChannelMessageEventId::PitchBend:
					s = "B";
					break;
			}
			lcdDisplayController->WriteToScreen(19, 1, s);
			break;
		}
		case EventType::MidiSystemRealTimeMessage:
		{
			const MidiSystemRealTimeMessage& systemRealTimeMessage = static_cast<const MidiSystemRealTimeMessage&>(event);
			MidiSystemRealTimeMessageId systemRealTimeMessageId = systemRealTimeMessage.GetSystemRealTimeMessageId();
			switch (systemRealTimeMessageId)
			{
			case MidiSystemRealTimeMessageId::TimingClock:
				HandleMidiClock();
				break;
			case MidiSystemRealTimeMessageId::Start:
				lcdDisplayController->WriteToScreen(19, 0, "P");
				break;
			case MidiSystemRealTimeMessageId::Stop:
				lcdDisplayController->WriteToScreen(19, 1, "S");
				Serial.println("Event: MidiStop");
				break;
			case MidiSystemRealTimeMessageId::Continue:
				lcdDisplayController->WriteToScreen(19, 1, "C");
				Serial.println("Event: MidiContinue");
				break;
			default:
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
			myassert(0 && "GateViewLcd: unhandled event");
		}
	}

	void GateViewLcd::HandleMidiClock()
	{
	}
}

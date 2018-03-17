// ArpViewLcd.cpp

#include "ArpViewLcd.h"
#include "LcdDisplayController.h"
#include "Song.h"
#include <Arduino.h>

namespace Atomic
{
	ArpViewLcd* ArpViewLcd::mInstance = nullptr;
	
	void ArpViewLcd::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new ArpViewLcd();
	}

	void ArpViewLcd::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	ArpViewLcd::ArpViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::SetView, handler);
	}

	int translateColumn[] = { 2, 7, 12 };

	void ArpViewLcd::SetCursor(int row, int column)
	{
		msg("ArpViewLcd::SetCursor: row: ", row, " column ", column);
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (row)
		{
			case 0:
			{
				lcdDisplayController->SetCursor(column * 2 + 1, 3);
				break;
			}
			case 1:
			{
				lcdDisplayController->SetCursor(translateColumn[column], 0);
				break;
			}
			default:
				msg("ArpViewLcd::SetCursor: Illegal row: ", row);
		}
	}

	void ArpViewLcd::DrawBar(int n, uint8_t value)
	{
		msg("ArpViewLcd::DrawBar: ", n, ", note ", value);
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		int x = n * 2 + 1;
		int offset = (int)value;
		if (offset > 36)
		{
			int val1 = std::min<int>(offset-36, 12);
			val1 = (val1 * 2) / 3;
			lcdDisplayController->WriteToScreen(x, 3, (char)val1);
		}
		if (offset > 48)
		{
			int val1 = std::min<int>(offset-24, 12);
			val1 = (val1 * 2) / 3;
			lcdDisplayController->WriteToScreen(x, 2, (char)val1);
		}
		if (offset > 60)
		{
			int val1 = std::min<int>(offset-24, 12);
			val1 = (val1 * 2) / 3;
			lcdDisplayController->WriteToScreen(x, 1, (char)val1);
		}
	}

	void ArpViewLcd::Refresh()
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		lcdDisplayController->Clear();
		lcdDisplayController->WriteToScreen(0, 0, "O:");
		lcdDisplayController->WriteToScreen(translateColumn[0], 0, mArp->GetOctaves());
		lcdDisplayController->WriteToScreen(5, 0, "P:");
		lcdDisplayController->WriteToScreen(translateColumn[1], 0, (int)mArp->GetPatternId());
		lcdDisplayController->WriteToScreen(10, 0, "L:");
		lcdDisplayController->WriteToScreen(translateColumn[2], 0, (int)mArp->GetLength());

		int32_t length = mArp->GetLength();
		msg("ArpViewLcd::Refresh: length ", length);
		for (int32_t n=0; n<length; n++)
		{
			DrawBar(n, mArp->GetNote(n));
		}

		lcdDisplayController->SetCursorEnabled(true);
		SetCursor(1, 1);
	}

	void ArpViewLcd::HandleActiveEvent(const Event& event)
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (event.GetEventType())
		{
		case EventType::SetView:
			Refresh();
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
			myassert(0 && "ArpViewLcd: unhandled event");
		}
	}

	void ArpViewLcd::HandleMidiClock()
	{
	}
}

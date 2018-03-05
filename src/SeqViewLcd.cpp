// SeqViewLcd.cpp

#include "SeqViewLcd.h"
#include "LcdDisplayController.h"
#include "MidiManager.h"
#include "Song.h"
#include "NavigationController.h"
#include <Arduino.h>

namespace Atomic
{
	SeqViewLcd* SeqViewLcd::mInstance = nullptr;
	
	void SeqViewLcd::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new SeqViewLcd();
	}

	void SeqViewLcd::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	SeqViewLcd::SeqViewLcd()
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
		//EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		EventController::GetInstance()->AddEventHandler(EventType::RawKey, handler);
		EventController::GetInstance()->AddEventHandler(EventType::SetView, handler);
	}

	void SeqViewLcd::HandleActiveEvent(const Event& event)
	{
		LcdDisplayController* lcdDisplayController = LcdDisplayController::GetInstance();
		switch (event.GetEventType())
		{
		case EventType::SetView:
			lcdDisplayController->Clear();
			lcdDisplayController->WriteToScreen(0, 0, "Seq");
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
		case EventType::RawKey:
		{
			const RawKeyEvent& rawKeyEvent = static_cast<const RawKeyEvent&>(event);
			Serial.print("SEq Event: RawKey: "); Serial.print(rawKeyEvent.GetKeyId());
			if (rawKeyEvent.GetUp())
			{
				Serial.print(" up");
			}
			Serial.println("");
			int keyId = rawKeyEvent.GetKeyId();
			bool up = rawKeyEvent.GetUp();
			int notenum = 0;
			switch (keyId)
			{
				case Event::Note1:
					notenum = 60;
					break;
				case Event::Note2:
					notenum = 61;
					break;
				case Event::Note3:
					notenum = 62;
					break;
				case Event::Note4:
					notenum = 63;
					break;
				case Event::Note5:
					notenum = 64;
					break;
				case Event::Note6:
					notenum = 65;
					break;
				case Event::Note7:
					notenum = 66;
					break;
				case Event::Note8:
					notenum = 67;
					break;
				default:
					break;
			}
			if (notenum != 0)
			{
				TrackId trackId = NavigationController::GetInstance()->GetCurrentTrackId();
				//const TrackPlayer* trackPlayer = SongPlayer::GetInstance()->GetTrackPlayer(trackId);
				//myassert(trackPlayer);
				Song* song = NavigationController::GetInstance()->GetCurrentSong();
				myassert(song);
				const Track* track = song->GetTrack(trackId);
				myassert(track);
				if (up)
				{
					MidiManager::GetInstance()->SendNoteOff(track->GetMidiSourceId(), track->GetMidiChannel(), notenum, 0);
				}
				else
				{
					MidiManager::GetInstance()->SendNoteOn(track->GetMidiSourceId(), track->GetMidiChannel(), notenum, 100);
				}
			}
			break;
		}
		default:
			myassert(0 && "SeqViewLcd: unhandled event");
		}
	}

	void SeqViewLcd::HandleMidiClock()
	{
	}
}

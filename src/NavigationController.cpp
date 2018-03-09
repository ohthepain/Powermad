// NavigationController.cpp

#include "View.h"
#include "NavigationController.h"
#include <Arduino.h>

namespace Atomic
{
	NavigationController* NavigationController::mInstance = nullptr;

	NavigationController::NavigationController()
	{
		Serial.println("NavigationController: Create song");
delay(500);
		mCurrentSong = new Song();
		Serial.println("NavigationController: set song");
delay(500);
		CreateSong();
		SongPlayer::GetInstance()->SetSong(mCurrentSong);
		Serial.println("NavigationController: set track id");
delay(500);
		mCurrentTrackId = 0;

		Serial.println("NavigationController: add keypress handler");
delay(500);
		EventController::EventHandler handler = [&](const Event& event) { this->HandleKeyPressEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
		Serial.println("NavigationController: bye");
delay(500);
	}

	NavigationController::~NavigationController()
	{
		delete mCurrentSong;
		mCurrentSong = nullptr;
	}

	void NavigationController::Init()
	{
		mInstance = new NavigationController();
	}

	void NavigationController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void NavigationController::CreateSong()
	{
		const int kNumTracksDefault = 8;
		Song* song = new Song();
		for (int i=0; i<kNumTracksDefault; i++)
		{
			song->AddGate(new Gate(i));
			song->AddArp(new Arp(i));
			song->AddSequence(new Sequence(i));
			song->AddTrack(new Track(i));

			song->GetArp(i)->SetGateId(i);
			song->GetSequence(i)->SetArpId(i);
			song->GetTrack(i)->SetSequenceId(i);
			song->GetTrack(i)->SetMidiChannel(i + 1);
		}
		mCurrentSong = song;
	}

	void NavigationController::HandleKeyPressEvent(const Event& event)
	{
		const KeyPressEvent& keyPressEvent = static_cast<const KeyPressEvent&>(event);
		switch (keyPressEvent.GetKeyId())
		{
			case Event::Song:
				Serial.println("NavigationController::HandleKeyPressEvent: Song");
				static const SetViewEvent setViewSong(ViewId::Song);
				EventController::GetInstance()->BroadcastEvent(setViewSong);
				break;
			case Event::Sequence:
				Serial.println("NavigationController::HandleKeyPressEvent: Seq");
				static const SetViewEvent setViewSeq(ViewId::Seq);
				EventController::GetInstance()->BroadcastEvent(setViewSeq);
				break;
			case Event::Arp:
				Serial.println("NavigationController::HandleKeyPressEvent: Arp");
				static const SetViewEvent setViewArp(ViewId::Arp);
				EventController::GetInstance()->BroadcastEvent(setViewArp);
				break;
			case Event::Gate:
				Serial.println("NavigationController::HandleKeyPressEvent: Gate");
				static const SetViewEvent setViewGate(ViewId::Gate);
				EventController::GetInstance()->BroadcastEvent(setViewGate);
				break;
			default:
				break;
		}
	}
}

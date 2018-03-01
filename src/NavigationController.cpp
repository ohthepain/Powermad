// NavigationController.cpp

#include "View.h"
#include "NavigationController.h"
#include <Arduino.h>

namespace Atomic
{
	NavigationController* NavigationController::mInstance = nullptr;

	NavigationController::NavigationController()
	{
		mSong = new Song();

		EventController::EventHandler handler = [&](const Event& event) { this->HandleKeyPressEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::KeyPress, handler);
	}

	NavigationController::~NavigationController()
	{
		delete mSong;
		mSong = nullptr;
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

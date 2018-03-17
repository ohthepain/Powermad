// SongPositionManager.cpp

#include "Event.h"
#include "SongPositionManager.h"
#include "MidiEvent.h"

namespace Atomic
{
	SongPositionManager* SongPositionManager::mInstance = nullptr;

	void SongPositionManager::Init()
	{
		mInstance = new SongPositionManager();
	}

	void SongPositionManager::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	SongPositionManager::SongPositionManager()
	: mPulsesFromSpp(0)
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleEvent(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
	}

	void SongPositionManager::HandleEvent(const Event& event)
	{
		const MidiSystemRealTimeMessage& midiSystemRealTimeMessage = static_cast<const MidiSystemRealTimeMessage&>(event);
		switch (midiSystemRealTimeMessage.GetSystemRealTimeMessageId())
		{
			case MidiSystemRealTimeMessageId::TimingClock:
				++mPulsesFromSpp;
				break;
			case MidiSystemRealTimeMessageId::Start:
				mPulsesFromSpp = 0;
				break;
			case MidiSystemRealTimeMessageId::Continue:
				break;
			case MidiSystemRealTimeMessageId::Stop:
				break;
			default:
				break;
		}
	}
}
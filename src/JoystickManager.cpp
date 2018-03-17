// JoystickManager.cpp

#include "JoystickManager.h"
#include "MidiEvent.h"
#include "InputPinManager.h"
#include "SongPositionManager.h"
#include <Arduino.h>

namespace Atomic
{
	JoystickManager* JoystickManager::mInstance = nullptr;

	JoystickManager::JoystickManager()
	{
		EventController::EventHandler myFunction = [&](const Event& event) { this->HandleMidiSystemRealTimeMessage(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, myFunction);
	}

	JoystickManager::~JoystickManager()
	{
	}

	void JoystickManager::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new JoystickManager();
	}

	void JoystickManager::Shutdown()
	{
		myassert(mInstance == nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	void JoystickManager::AddJoytickAxis(JoystickAxisId joystickAxisId, AnalogInputId analogInputId)
	{
		mJoysticks.Add({joystickAxisId, analogInputId});
	}

	const size_t kNumInflectionPoints = 8;
	uint inflectionPoint[kNumInflectionPoints] = { 1000, 10, 700, 300, 580, 80, 550, 450, };
	uint divisor[kNumInflectionPoints] =         { 4,  4,  8,  8,   16,   16,   32,   32, };
	uint centerVal = 512;

	void JoystickManager::CheckJoystickAxis(size_t n)
	{
		tJoystick& joystick = mJoysticks[n];
		AnalogInputId analogInputId = joystick.analogInputId;
		uint32_t songTime = SongPositionManager::GetInstance()->GetPulsesFromSpp();
		size_t pointnum;

		uint value = InputPinManager::GetInstance()->ReadAnalogInputValue(analogInputId);
		for (pointnum=0; pointnum<kNumInflectionPoints; pointnum++)
		{
			uint point = inflectionPoint[pointnum];
			if (point > centerVal && value >= point)
			{
				goto send_event;
			}
			if (point < centerVal && value <= point)
			{
				goto send_event;
			}
		}
		return;

	send_event:
		if (songTime - joystick.lastMessageTime > divisor[pointnum])
		{
			joystick.lastMessageTime = songTime;
			//msg("CheckJoystickAxis - send event: n ", n, " value ", value);
			JoystickAxisEvent joystickAxisEvent(joystick.joystickAxisId, value, divisor[n]);
			EventController::GetInstance()->BroadcastEvent(joystickAxisEvent);
		}
	}

	void JoystickManager::HandleMidiTimingClock()
	{
		for (size_t n=0; n<mJoysticks.GetSize(); n++)
		{
			CheckJoystickAxis(n);
		}
	}

	void JoystickManager::HandleMidiSystemRealTimeMessage(const Event& event)
	{
		const MidiSystemRealTimeMessage& midiSystemRealTimeMessage = static_cast<const MidiSystemRealTimeMessage&>(event);
		switch (midiSystemRealTimeMessage.GetSystemRealTimeMessageId())
		{
			case MidiSystemRealTimeMessageId::TimingClock:
				HandleMidiTimingClock();
				break;
			default:
				break;
		}
	}
}

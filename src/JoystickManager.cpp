// JoystickManager.cpp

#include "JoystickManager.h"
#include "MidiEvent.h"
#include "InputPinManager.h"
#include "SongPositionManager.h"
#include "UserMessage.h"
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
		int centerVal = InputPinManager::GetInstance()->ReadAnalogInputValue(analogInputId);
		/*while (centerVal > 512 + 50 || centerVal < 512 - 50)
		{
			WarnUser("Initialization Error:", "Please release joysticks or recalibrate");
			delay(500);
		}*/
		mJoysticks.Add({joystickAxisId, analogInputId, centerVal, 0});
		msg("center value ", centerVal);
	}

	const size_t kNumInflectionPoints = 8;
	uint inflectionPoint[kNumInflectionPoints] = { 1000, 10, 700, 300, 580, 80, 550, 450, };
	uint divisor[kNumInflectionPoints] =         { 6, 6, 12, 12, 24, 24, 48, 48, };

	void JoystickManager::CheckJoystickAxis(size_t n)
	{
		tJoystick& joystick = mJoysticks[n];
		AnalogInputId analogInputId = joystick.analogInputId;
		uint32_t songTime = SongPositionManager::GetInstance()->GetPulsesFromSpp();
		size_t pointnum;

		uint value = InputPinManager::GetInstance()->ReadAnalogInputValue(analogInputId);
		for (pointnum=0; pointnum<kNumInflectionPoints; pointnum++)
		{
			int point = inflectionPoint[pointnum];
			if (point > joystick.centerValue && value >= point)
			{
				goto send_event;
			}
			if (point < joystick.centerValue && value <= point)
			{
				goto send_event;
			}
		}
		return;

	send_event:
		if (songTime - joystick.lastMessageTime[n] > divisor[pointnum])
		{
			if (n == 1)
			{
				//msg("songTime ", songTime, " last msg time ", joystick.lastMessageTime[n], " point ", pointnum, " divisor ", divisor[pointnum]);
			}
			joystick.lastMessageTime[n] = songTime;
			//msg("CheckJoystickAxis - send event: n ", n, " value ", value);
			JoystickAxisEvent joystickAxisEvent(joystick.joystickAxisId, value, divisor[pointnum]);
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

// Event.cpp

#include "Event.h"
#include <myassert.h>
#include <Arduino.h>

namespace std {
    void __throw_bad_function_call() {exit(3);}
}

namespace Atomic
{
	EventController* EventController::mInstance = nullptr;

	void EventController::Init()
	{
		mInstance = new EventController();
	}

	void EventController::Shutdown()
	{
		delete mInstance;
		mInstance = nullptr;
	}

  EventController::EventController()
  : mBusy(false)
  {
    mHandlerMap = new EventHandlerList[EventType::ArraySize];
    mHandlerAddQueue = new EventHandlerList[EventType::ArraySize];
    mHandlerRemoveQueue = new EventHandlerList[EventType::ArraySize];
  }

  EventController::~EventController()
  {
    delete [] mHandlerMap;
    mHandlerMap = nullptr;
  }
	
	void EventController::AddEventHandler(EventType eventType, EventHandler eventHandler)
	{
    int eventTypeInt = static_cast<int>(eventType);
    myassert(!mBusy);
		if (mBusy)
		{
      Serial.println("AddEventHandler: busy");
      EventHandlerList& eventHandlerList = mHandlerAddQueue[eventTypeInt];
      eventHandlerList.Add(eventHandler);
		}
		else
		{
      EventHandlerList& eventHandlerList = mHandlerMap[eventTypeInt];
      eventHandlerList.Add(eventHandler);
		}
	}

  void EventController::BroadcastEvent(const Event& event)
  {
    mBusy = true;
    int eventTypeInt = static_cast<int>(event.GetEventType());
    EventHandlerList& eventHandlerList = mHandlerMap[eventTypeInt];
    for (size_t i=0; i<eventHandlerList.GetSize(); i++)
    {
      EventHandler eventHandler = eventHandlerList[i];
      eventHandler(event);
    }

    mBusy = false;
  }
}

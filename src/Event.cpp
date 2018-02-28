// Event.cpp

#include "Event.h"
#include <assert.h>
#include <Arduino.h>

namespace std {
    void __throw_bad_function_call() {exit(3);}
}

namespace Atomic
{
	EventController* EventController::mInstance = nullptr;

  template<class T> Vector<T>::Vector()
  : mNodes(nullptr)
  , mSize(0)
  , mCapacity(0)
  {
  }

  template<class T> Vector<T>::~Vector()
  {
    delete [] mNodes;
    mNodes = nullptr;
  }

  template<class T> void Vector<T>::Add(T value)
  {
    if (mSize == mCapacity)
    {
      int newsize = mCapacity * 2 + 2;
      T* newNodes = new T[newsize];
      for (size_t i=0; i<mCapacity; i++)
      {
        newNodes[i] = mNodes[i];
      }
      delete [] mNodes;
      mNodes = newNodes;
      mCapacity = newsize;
    }
    mNodes[mSize++] = value;
  }
  
  template<class T> void Vector<T>::Remove(T value)
  {
    bool found = false;
    for (int i=0; i<mSize; i++)
    {
      found = found || mNodes[i] == value;
      if (found && i < mSize - 1)
      {
        mNodes[i] = mNodes[i+1];
      }
    }
    assert(found);
    if (found)
    {
      --mSize;
    }
  }
  
  template <class T> T& Vector<T>::operator[](int index)
  {
    assert((size_t)index < mSize);
    return mNodes[index];
  }

  template<class T> void Vector<T>::Clear()
  {
    mSize = 0;
  }

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
    mHandlerMap = new EventHandlerList[Event::ArraySize];
    mHandlerAddQueue = new EventHandlerList[Event::ArraySize];
    mHandlerRemoveQueue = new EventHandlerList[Event::ArraySize];
  }

  EventController::~EventController()
  {
    delete [] mHandlerMap;
    mHandlerMap = nullptr;
  }
	
	void EventController::AddEventHandler(Event::EventType eventType, EventHandler eventHandler)
	{
    assert(eventType < Event::ArraySize);
    assert(!mBusy);
		if (mBusy)
		{
      Serial.println("AddEventHandler: busy");
      EventHandlerList& eventHandlerList = mHandlerAddQueue[eventType];
      eventHandlerList.Add(eventHandler);
		}
		else
		{
      EventHandlerList& eventHandlerList = mHandlerMap[eventType];
      eventHandlerList.Add(eventHandler);
		}
	}

  void EventController::BroadcastEvent(const Event& event)
  {
    mBusy = true;
    int eventType = (int)event.GetEventType();
    EventHandlerList& eventHandlerList = mHandlerMap[eventType];
    for (size_t i=0; i<eventHandlerList.GetSize(); i++)
    {
      EventHandler eventHandler = eventHandlerList[i];
      eventHandler();
    }

    mBusy = false;
  }
}

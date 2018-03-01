// View

#pragma once

#include "Event.h"
#include "LcdDisplayController.h"

namespace Atomic
{
	enum class ViewId {
		Song,
		Seq,
		Arp,
		Gate,
	};

	class SetViewEvent : public Event
	{
	public:
		SetViewEvent(ViewId viewId) : mViewId(viewId) {}
		EventType GetEventType() const { return EventType::SetView; }
		ViewId GetViewId() const { return mViewId; }
	private:
		ViewId mViewId;
	};

	class View
	{
	public:
		View() : mIsActive(false) {}
		virtual ~View() {}
		void SetActive(bool active) { mIsActive = active; }
		bool IsActive() const { return mIsActive; }
		virtual ViewId GetViewId() const = 0;

		virtual void HandleEvent(const Event& event);
		virtual void HandleActiveEvent(const Event& event) = 0;
	private:
		bool mIsActive;
	};

	class ViewLcd : public View
	{
	public:
		ViewLcd() : mLcdDisplayController(LcdDisplayController::GetInstance()) {}
		virtual ~ViewLcd() {}
	protected:
		LcdDisplayController* mLcdDisplayController;
	};
}

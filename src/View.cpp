// View

#include "View.h"

namespace Atomic
{
	void View::HandleEvent(const Event& event)
	{
		switch (event.GetEventType())
		{
			case EventType::SetView:
			{
				const SetViewEvent& setViewEvent = static_cast<const SetViewEvent&>(event);
				ViewId viewId = setViewEvent.GetViewId();
				SetActive(viewId == GetViewId());
				break;
			}
			default:
				break;
		}

		if (IsActive())
		{
			HandleActiveEvent(event);
		}
	}
}

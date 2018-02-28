// EventMonitor.h

#include "Event.h"
#include <assert.h>

namespace Atomic
{
	class EventMonitor
	{
	public:
		static void Init();
		static void Shutdown();
		static EventMonitor* GetInstance() { assert(mInstance); return mInstance; }

	private:
		static EventMonitor* mInstance;
		EventMonitor();
		~EventMonitor();

		void HandleEvent(const Event& event);
	};
}

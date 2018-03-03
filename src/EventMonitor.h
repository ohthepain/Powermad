// EventMonitor.h

#include "MidiEvent.h"
#include <myassert.h>

namespace Atomic
{
	class EventMonitor
	{
	public:
		static void Init();
		static void Shutdown();
		static EventMonitor* GetInstance() { myassert(mInstance); return mInstance; }

	private:
		static EventMonitor* mInstance;
		EventMonitor();
		~EventMonitor();

		void HandleEvent(const Event& event);
	};
}

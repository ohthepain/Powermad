// PanelButtonsController

#include "Event.h"
#include <assert.h>

class IntervalTimer;
class NavigationManager;

namespace Atomic
{
	class TempoMonitor
	{
		public:
			static void Init();
			static void Shutdown();
			static TempoMonitor* GetInstance() { assert(mInstance != nullptr); return mInstance; }

		private:
			static TempoMonitor* mInstance;
			NavigationManager* mNavigationManager;

			TempoMonitor();
			virtual ~TempoMonitor() {}

			static void HandleMidiClock();
	};
}

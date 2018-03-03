// PanelButtonsController

#include "MidiEvent.h"
#include <myassert.h>

class IntervalTimer;
class NavigationManager;

namespace Atomic
{
	class TempoMonitor
	{
		public:
			static void Init();
			static void Shutdown();
			static TempoMonitor* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		private:
			static TempoMonitor* mInstance;
			NavigationManager* mNavigationManager;

			TempoMonitor();
			virtual ~TempoMonitor() {}

			void HandleMidiSystemRealTimeMessage(const Event&);
	};
}

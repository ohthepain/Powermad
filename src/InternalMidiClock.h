// PanelButtonsController

#include "Event.h"
#include <assert.h>

class IntervalTimer;

namespace Atomic
{
	class InternalMidiClock
	{
		public:
			static void Init();
			static void Shutdown();
			static InternalMidiClock* GetInstance() { assert(mInstance != nullptr); return mInstance; }

		private:
			static InternalMidiClock* mInstance;
			InternalMidiClock();
			virtual ~InternalMidiClock() {}

			void HandleMillisecondEvent();
			void HandleKeyPress(const Event& event);

			double mLastMidiPulseTime;
	};
}

// PanelButtonsController

#include "MidiEvent.h"
#include <myassert.h>

class IntervalTimer;

namespace Atomic
{
	class InternalMidiClock
	{
		public:
			static void Init();
			static void Shutdown();
			static InternalMidiClock* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		private:
			static InternalMidiClock* mInstance;
			InternalMidiClock();
			virtual ~InternalMidiClock() {}

			void HandleMillisecondEvent();
			void HandleKeyPress(const Event& event);

			double mLastMidiPulseTime;
	};
}

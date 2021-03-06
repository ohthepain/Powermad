// TimerController.h

#include <myassert.h>

class IntervalTimer;
class EventController;

namespace Atomic
{
	class TimerController
	{
		public:
			static void Init();
			static void Shutdown();
			static TimerController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		private:
			TimerController();
			virtual ~TimerController();

			static void HandleTimer();

			static TimerController* mInstance;
		
			EventController* mEventController;

			IntervalTimer* mTimer;
	};
}

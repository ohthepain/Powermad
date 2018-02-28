// PanelButtonsController

#include <list>
#include <assert.h>

class IntervalTimer;

namespace Atomic
{
	class TimerController
	{
		public:
			static void Init();
			static void Shutdown();
			static TimerController* GetInstance() { return mInstance; }

		private:
			TimerController();
			virtual ~TimerController();

			static void HandleTimer();

			static TimerController* mInstance;
		
			EventController* mEventController;

			IntervalTimer* mTimer;
	};

	class PanelButtonsController
	{
		public:
			static void Init();
			static void Shutdown();
			static PanelButtonsController* GetInstance() { return mInstance; }

      int HandleTimer();
      void HandleRawKeyPress(int i);
      
		private:
			PanelButtonsController();
			virtual ~PanelButtonsController() {}

			uint32_t ScanKeys();
			void Update();

			static PanelButtonsController* mInstance;

			unsigned long mSavedKeyState;
			unsigned long mTimeLastKeyStateChange;
			unsigned long mTempKeyState;

			const int kClockPin = 12;
			const int kDataPin = 11;
			const int kInputPin = 10;
	};
}

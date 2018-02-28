// PanelButtonsController

#include <list>
#include <assert.h>

class IntervalTimer;

namespace Atomic
{
	class PanelButtonsController
	{
		public:
			static void Init();
			static void Shutdown();
			static PanelButtonsController* GetInstance() { assert(mInstance != nullptr); return mInstance; }

      		int HandleTimer();
      		void HandleRawKeyEvent(const Event& event);
      
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

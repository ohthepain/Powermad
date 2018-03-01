// LcdDisplayController

#include "Event.h"
#include <assert.h>
class LiquidCrystal;

namespace Atomic
{
	class LcdDisplayController
	{
		public:
			static void Init();
			static void Shutdown();
			static LcdDisplayController* GetInstance() { assert(mInstance != nullptr); return mInstance; }

		private:
			LcdDisplayController();
			virtual ~LcdDisplayController();

			void HandleEvent(const Event& event);

			static LcdDisplayController* mInstance;
			LiquidCrystal* mLiquidCrystal;
	};
}

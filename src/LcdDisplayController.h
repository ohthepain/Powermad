// LcdDisplayController

#pragma once

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

			void WriteToScreen(int x, int y, const char* string);
			void WriteToScreen(int x, int y, int n);
			void Clear();

		private:
			LcdDisplayController();
			virtual ~LcdDisplayController();

			void HandleEvent(const Event& event);

			static LcdDisplayController* mInstance;
			LiquidCrystal* mLiquidCrystal;
	};
}

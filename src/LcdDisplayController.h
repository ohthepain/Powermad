// LcdDisplayController

#pragma once

#include "MidiEvent.h"
#include <myassert.h>
class LiquidCrystal;

namespace Atomic
{
	class LcdDisplayController
	{
		public:
			static void Init();
			static void Shutdown();
			static LcdDisplayController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

			void SetCursorEnabled(bool enabled);
			void SetCursor(int x, int y);
			void WriteToScreen(int x, int y, const char* string);
			void WriteToScreen(int x, int y, int n);
			void WriteToScreen(int x, int y, char c);
			void Clear();

		private:
			LcdDisplayController();
			virtual ~LcdDisplayController();

			void HandleEvent(const Event& event);

			static LcdDisplayController* mInstance;
			LiquidCrystal* mLiquidCrystal;
			bool mCursorEnabled;
			int mCursorColumn;
			int mCursorRow;
	};
}

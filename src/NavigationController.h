// NavigationController.h

#pragma once

#include <stdint.h>
#include "Song.h"
#include "MidiEvent.h"
#include <myassert.h>

namespace Atomic
{
	class NavigationController
	{
	public:
		static void Init();
		static void Shutdown();
		static NavigationController* GetInstance() { myassert(mInstance != nullptr); return mInstance; }

		Song* GetSong() { return mSong; }
		Sequence* GetCurrentSequence() { return mCurrentSequence; }

	private:
		static NavigationController* mInstance;

		NavigationController();
		virtual ~NavigationController();

		void HandleKeyPressEvent(const Event& event);

		Song* mSong;
		Sequence* mCurrentSequence;
	};
}

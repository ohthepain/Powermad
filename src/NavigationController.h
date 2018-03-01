// NavigationController.h

#pragma once

#include <stdint.h>
#include "Song.h"
#include "Event.h"
#include <assert.h>

namespace Atomic
{
	class NavigationController
	{
	public:
		static void Init();
		static void Shutdown();
		static NavigationController* GetInstance() { assert(mInstance != nullptr); return mInstance; }

		Song* GetSong() { return mSong; }

	private:
		static NavigationController* mInstance;

		NavigationController();
		virtual ~NavigationController();

		void HandleKeyPressEvent(const Event& event);

		Song* mSong;
	};
}

// NavigationController.h

#pragma once

#include <stdint.h>
#include "Song.h"
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

		Song* mSong;

		NavigationController();
		virtual ~NavigationController();
	};
}

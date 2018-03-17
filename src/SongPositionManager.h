// SongPositionManager.h

#pragma once

#include <stdint.h>

namespace Atomic
{
	class Event;

	// SongPosition keeps running when song is stopped so that the UI can keep the beat while the song is not playing
	class SongPositionManager
	{
	public:
		static void Init();
		static void Shutdown();
		static SongPositionManager* GetInstance() { return mInstance; }

		void SetPulsesFromSpp(uint32_t pulsesFromSpp) { mPulsesFromSpp = pulsesFromSpp; }
		uint32_t GetPulsesFromSpp() const { return mPulsesFromSpp; }

	private:
		static SongPositionManager* mInstance;

		SongPositionManager();
		virtual ~SongPositionManager() {}

		void HandleEvent(const Event& event);

		uint32_t mPulsesFromSpp;
	};
}

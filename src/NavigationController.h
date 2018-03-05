// NavigationController.h

#pragma once

#include <stdint.h>
#include "Song.h"
#include "SongPlayer.h"
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

		// Returns non-const pointer to current song - you can't get this through the NavigationController
		Song* GetCurrentSong() const { return mCurrentSong; }
		TrackId GetCurrentTrackId() const { return mCurrentTrackId; }
		// Get trackplayers through SongPlayer
		//TrackPlayer* GetCurrentTrackPlayer() const { return mCurrentSong->GetTrackPlayer(mCurrentTrackId); }
		MidiSongPositionPointer GetCurrentMidiSongPositionPointer() const { return mMidiSongPositionPointer; }

	private:
		static NavigationController* mInstance;

		NavigationController();
		virtual ~NavigationController();

		void HandleKeyPressEvent(const Event& event);

		Song* mCurrentSong;
		SongPlayer* mSongPlayer;
		TrackId mCurrentTrackId;
		MidiSongPositionPointer mMidiSongPositionPointer;
	};
}

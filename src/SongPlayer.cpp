// SongPlayer

#include "MidiManager.h"
#include "SongPlayer.h"

namespace Atomic
{
	SongPlayer* SongPlayer::mInstance = nullptr;

	const Song* Player::GetSong() const
	{
		return GetSongPlayer()->GetSong();
	}

	GatePlayer::GatePlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId) 
	: Player(songPlayer, parent, trackId)
	{

	}

	ArpPlayer::ArpPlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId) 
	: Player(songPlayer, parent, trackId)
	{
		mNoteNum = new uint8_t[kMaxNotes];
		mNoteVelocity = new uint8_t[kMaxNotes];
		mGatePlayers.Add(new GatePlayer(songPlayer, this, trackId));
	}

	ArpPlayer::~ArpPlayer()
	{
		delete [] mNoteNum;
		mNoteNum = nullptr;
		delete [] mNoteVelocity;
		mNoteVelocity = nullptr;
	}

	void ArpPlayer::Update(uint32_t clocks)
	{
		static uint32_t lastClocks = 0;
		myassert(clocks - lastClocks <= 1);
		lastClocks = clocks;

		int division = mArp->GetDivision();
		if (clocks % division == 0)
		{
			int n = mCurrentNoteNum + 1;
			for (int n = mCurrentNoteNum + 1; n != mCurrentNoteNum; n++)
			{
				if (n >= kMaxNotes) 
				{
					n = 0;
				}
				if (mNoteNum[n] != 0)
				{
					break;
				}
			}
			if (n != mCurrentNoteNum)
			{
				mCurrentNoteNum = n;
				MidiSourceId midiSourceId = GetParent()->GetMidiSourceId();
				uint8_t channel = GetParent()->GetMidiChannel();
				MidiManager::GetInstance()->SendNoteOn(midiSourceId, channel, mNoteNum[mCurrentNoteNum], mNoteVelocity[n]);
			}
		}
	}

	TrackPlayer::TrackPlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId)
	: Player(songPlayer, parent, trackId)
	{
		mArpPlayers.Add(new ArpPlayer(songPlayer, this, trackId));
	}

	void TrackPlayer::Update(uint32_t midiClocks)
	{
		MidiSongPositionPointer midiSongPositionPointer = mSongPlayer->GetMidiSongPositionPointer();
		const Song* song = mSongPlayer->GetSong();
		myassert(song != nullptr);
		myassert(mTrack != nullptr);
		SequenceId sequenceId = song->GetSequenceIdForTrackAtSpp(mTrack->GetTrackId(), midiSongPositionPointer);

		// If we hit a new note then hand it to the arpgeggiator
		// If any notes end then remove them from the arpeggiator
	}

	void TrackPlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		ArpPlayer* arpPlayer = mArpPlayers[0];
		myassert(arpPlayer);
		arpPlayer->NoteOn(note, velocity);
	}

	void TrackPlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		ArpPlayer* arpPlayer = mArpPlayers[0];
		myassert(arpPlayer);
		arpPlayer->NoteOff(note, velocity);
	}

	SongPlayer::SongPlayer()
	: mSong(nullptr)
	, mIsPlaying(false)
	, mMidiSongPositionPointer(0)
	{
	}

	void SongPlayer::SetSong(const Song* song)
	{
		mSong = song;
		for (size_t i=0; i<mTrackPlayer.GetSize(); i++)
		{
			delete mTrackPlayer[i];
		}
		mTrackPlayer.Clear();

		for (size_t i=0; i<song->GetNumTracks(); i++)
		{
			mTrackPlayer.Add(new TrackPlayer(this, nullptr, i));
		}
	}

	SongPlayer::~SongPlayer()
	{
		mTrackPlayer.Clear();
	}

	const TrackPlayer* SongPlayer::GetTrackPlayer(TrackId trackId) const
	{
		myassert(mTrackPlayer[trackId]);
		return mTrackPlayer[trackId];
	}

	void SongPlayer::Init()
	{
		myassert(mInstance == nullptr);
		mInstance = new SongPlayer;
	}

	void SongPlayer::Shutdown()
	{
		myassert(mInstance != nullptr);
		delete mInstance;
		mInstance = nullptr;
	}

	void SongPlayer::Start()
	{
		if (!mIsPlaying)
		{
			mMidiSongPositionPointer = 0;
			mNumMidiClocksFromSpp = 0;
			mIsPlaying = true;
		
			for (size_t n=0; n<kMaxTracks; n++)
			{
				myassert(mTrackPlayer[n]);
				mTrackPlayer[n]->Start();
			}
		}
	}

	void SongPlayer::Stop()
	{
		mIsPlaying = false;
	}

	void SongPlayer::Continue()
	{
		mIsPlaying = true;
	}

	void SongPlayer::SetMidiSongPositionPointer(MidiSongPositionPointer midiSongPositionPointer)
	{
		// TODO: should this be ignored if not playing?
		mMidiSongPositionPointer = midiSongPositionPointer;
	}

	void SongPlayer::Update()
	{
		// TODO: we should probably use MIDI Clock to correct position, not for update

		if (mIsPlaying)
		{
			for (size_t n=0; n<kMaxTracks; n++)
			{
				myassert(mTrackPlayer[n]);
				mTrackPlayer[n]->Update(mNumMidiClocksFromSpp);
			}
		}
	}
}

// SongPlayer

#include "MidiManager.h"
#include "SongPlayer.h"
#include <Arduino.h>

namespace Atomic
{
	SongPlayer* SongPlayer::mInstance = nullptr;

	const Song* Player::GetSong() const
	{
		return GetSongPlayer()->GetSong();
	}

	MidiSourceId Player::GetMidiSourceId() const
	{
		Serial.print("Player::GetMidiChannel: mSongPlayer "); Serial.println((int)mSongPlayer);
		Serial.print("Player::GetMidiChannel: mTrackId "); Serial.println((int)mTrackId);
		myassert(mSongPlayer);
		const Song* song = GetSong();
		Serial.print("Player::GetMidiChannel: song @"); Serial.println((int)song);
		const Track* track = song->GetTrack(mTrackId);
		Serial.print("Player::GetMidiChannel: track @"); Serial.println((int)track);
		return track->GetMidiSourceId();
	}

	MidiChannel Player::GetMidiChannel() const
	{
		Serial.print("Player::GetMidiChannel: mSongPlayer "); Serial.println((int)mSongPlayer);
		Serial.print("Player::GetMidiChannel: mTrackId "); Serial.println((int)mTrackId);
		myassert(mSongPlayer);
		const Song* song = GetSong();
		Serial.print("Player::GetMidiChannel: song @"); Serial.println((int)song);
		const Track* track = song->GetTrack(mTrackId);
		Serial.print("Player::GetMidiChannel: track @"); Serial.println((int)track);
		return track->GetMidiChannel();
	}

	GatePlayer::GatePlayer(const SongPlayer* songPlayer, TrackId trackId) 
	: Player(songPlayer, trackId)
	{

	}

	ArpPlayer::ArpPlayer(const SongPlayer* songPlayer, TrackId trackId) 
	: Player(songPlayer, trackId)
	{
		mNoteNum = new uint8_t[kMaxNotes];
		mNoteVelocity = new uint8_t[kMaxNotes];
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

	void GatePlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		Serial.println("GatePlayer::NoteOn");
		const Song* song = GetSongPlayer()->GetSong();
		myassert(song);
		//const Track* track = song->GetTrack(GetTrackId());
		//myassert(track);
		Serial.print("GatePlayer::NoteOn: track id "); Serial.println(GetTrackId());
		const TrackPlayer* trackPlayer = GetSongPlayer()->GetTrackPlayer(GetTrackId());
		Serial.print("GatePlayer::NoteOn: trackPlayer @"); Serial.println((int)trackPlayer);
		uint8_t channel = trackPlayer->GetMidiChannel();
		Serial.print("GatePlayer::NoteOn: channel "); Serial.println((int)channel);
		MidiSourceId midiSourceId = trackPlayer->GetMidiSourceId();
		Serial.print("GatePlayer::NoteOn: midiSourceId "); Serial.println((int)midiSourceId);
		MidiManager::GetInstance()->SendNoteOn(midiSourceId, channel, note, velocity);
		Serial.println("GatePlayer::NoteOn: bye");
	}

	void GatePlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		const Song* song = GetSongPlayer()->GetSong();
		myassert(song);
		//const Track* track = song->GetTrack(GetTrackId());
		//myassert(track);
		const TrackPlayer* trackPlayer = GetSongPlayer()->GetTrackPlayer(GetTrackId());
		uint8_t channel = trackPlayer->GetMidiChannel();
		MidiSourceId midiSourceId = GetParent()->GetMidiSourceId();
		MidiManager::GetInstance()->SendNoteOff(midiSourceId, channel, note, velocity);
	}

	GatePlayer* ArpPlayer::GetGatePlayer()
	{
		GateId gateId = mArp->GetGateId();
		GatePlayer* gatePlayer = GetSongPlayer()->GetGatePlayer(gateId);
		return gatePlayer;
	}

	void ArpPlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		Serial.println("ArpPlayer::NoteOn");
		GatePlayer* gatePlayer = GetGatePlayer();
		myassert(gatePlayer);
		gatePlayer->NoteOn(note, velocity);		
	}

	void ArpPlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		Serial.println("ArpPlayer::NoteOn");
		GatePlayer* gatePlayer = GetGatePlayer();
		myassert(gatePlayer);
		gatePlayer->NoteOn(note, velocity);		
	}

	TrackPlayer::TrackPlayer(const SongPlayer* songPlayer, TrackId trackId)
	: Player(songPlayer, trackId)
	{
	}

	void TrackPlayer::Update(uint32_t midiClocks)
	{
		MidiSongPositionPointer midiSongPositionPointer = mSongPlayer->GetMidiSongPositionPointer();
		const Song* song = mSongPlayer->GetSong();
		myassert(song != nullptr);
		myassert(mTrack != nullptr);

		//SequenceId sequenceId = song->GetSequenceIdForTrackAtSpp(mTrack->GetTrackId(), midiSongPositionPointer);

		// If we hit a new note then hand it to the arpgeggiator
		// If any notes end then remove them from the arpeggiator
	}

	void TrackPlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		Serial.println("TrackPlayer::NoteOn");
		ArpId arpId = mCurrentSequence->GetArpId();
		Serial.print("TrackPlayer::NoteOn: arpId "); Serial.println((int)arpId);
		ArpPlayer* arpPlayer = GetSongPlayer()->GetArpPlayer(arpId);
		Serial.print("TrackPlayer::NoteOn: Got arpPlayer @"); Serial.println((int)arpPlayer);
		myassert(arpPlayer);
		arpPlayer->NoteOn(note, velocity);
	}

	void TrackPlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		Serial.println("TrackPlayer::NoteOn");
		ArpId arpId = mCurrentSequence->GetArpId();
		ArpPlayer* arpPlayer = GetSongPlayer()->GetArpPlayer(arpId);
		Serial.print("TrackPlayer::NoteOn: Got arpPlayer @"); Serial.println((int)arpPlayer);
		myassert(arpPlayer);
		arpPlayer->NoteOff(note, velocity);
	}

	SongPlayer::SongPlayer()
	: mSong(nullptr)
	, mIsPlaying(false)
	, mMidiSongPositionPointer(0)
	{
	}

	void SongPlayer::ClearSong()
	{
		for (size_t i=0; i<mTrackPlayers.GetSize(); i++)
		{
			delete mTrackPlayers[i];
		}
		mTrackPlayers.Clear();

		for (size_t i=0; i<mArpPlayers.GetSize(); i++)
		{
			delete mArpPlayers[i];
		}
		mArpPlayers.Clear();

		for (size_t i=0; i<mGatePlayers.GetSize(); i++)
		{
			delete mGatePlayers[i];
		}
		mGatePlayers.Clear();

		mSong = nullptr;
	}

	void SongPlayer::SetSong(const Song* song)
	{
		Serial.println("SongPlayer::SetSong");
		ClearSong();
		Serial.print("SongPlayer::SetSong: num tracks: "); Serial.println(song->GetNumTracks());

		mSong = song;

		for (size_t i=0; i<song->GetNumTracks(); i++)
		{
			TrackPlayer* trackPlayer = new TrackPlayer(this, i);
			const Track* track = song->GetTrack(i);
			myassert(track);
			trackPlayer->SetTrack(track);
			SequenceId sequenceId = song->GetSequenceIdForTrackAtSpp(i, 0);
			const Sequence* sequence = song->GetSequence(sequenceId);
			myassert(sequence);
			trackPlayer->SetCurrentSequence(sequence);
			mTrackPlayers.Add(trackPlayer);
		}

		for (size_t i=0; i<song->GetNumArps(); i++)
		{
			ArpPlayer* arpPlayer = new ArpPlayer(this, i);
			const Arp* arp = song->GetArp(i);
			myassert(arp);
			arpPlayer->SetArp(arp);
			mArpPlayers.Add(arpPlayer);
		}

		for (size_t i=0; i<song->GetNumGates(); i++)
		{
			GatePlayer* gatePlayer = new GatePlayer(this, i);
			mGatePlayers.Add(gatePlayer);
			const Gate* gate = song->GetGate(i);
			myassert(gate);
			gatePlayer->SetGate(gate);
			mGatePlayers.Add(gatePlayer);
		}
	}

	SongPlayer::~SongPlayer()
	{
		ClearSong();
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
				myassert(mTrackPlayers[n]);
				mTrackPlayers[n]->Start();
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
				myassert(mTrackPlayers[n]);
				mTrackPlayers[n]->Update(mNumMidiClocksFromSpp);
			}
		}
	}
}

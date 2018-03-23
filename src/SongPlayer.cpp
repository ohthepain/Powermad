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
		myassert(mSongPlayer);
		const Song* song = GetSong();
		const Track* track = song->GetTrack(mTrackId);
		return track->GetMidiSourceId();
	}

	MidiChannel Player::GetMidiChannel() const
	{
		myassert(mSongPlayer);
		const Song* song = GetSong();
		const Track* track = song->GetTrack(mTrackId);
		return track->GetMidiChannel();
	}

	GatePlayer::GatePlayer(const SongPlayer* songPlayer, TrackId trackId) 
	: Player(songPlayer, trackId)
	{

	}

	void GatePlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		const Song* song = GetSongPlayer()->GetSong();
		myassert(song);
		//const Track* track = song->GetTrack(GetTrackId());
		//myassert(track);
		const TrackPlayer* trackPlayer = GetSongPlayer()->GetTrackPlayer(GetTrackId());
		uint8_t channel = trackPlayer->GetMidiChannel();
		MidiSourceId midiSourceId = trackPlayer->GetMidiSourceId();
		msg("GatePlayer::NoteOn: midiSourceId ", (int)midiSourceId);
		MidiManager::GetInstance()->SendNoteOn(midiSourceId, channel, note, velocity);
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

	ArpPlayer::ArpPlayer(const SongPlayer* songPlayer, TrackId trackId) 
	: Player(songPlayer, trackId)
	{
	}

	ArpPlayer::~ArpPlayer()
	{
	}

	void ArpPlayer::Start()
	{
		mCurrentNoteNum = 0;
	}

	void ArpPlayer::PlayNextNote()
	{
		if (mNoteList.GetSize() > 0)
		{
			msg("ArpPlayer::PlayNextNote: this many notes: ", mNoteList.GetSize());
			++mCurrentNoteNum;
			if (mCurrentNoteNum >= (int)mNoteList.GetSize())
			{
				mCurrentNoteNum = 0;
			}
			NoteRecord* noteRecord = mNoteList[mCurrentNoteNum];
			myassert(noteRecord);
			GatePlayer* gatePlayer = GetGatePlayer();
			myassert(gatePlayer);
			gatePlayer->NoteOn(noteRecord->note, noteRecord->velocity);
		}
	}

	void ArpPlayer::HandleMidiTimingClock(uint32_t clocks)
	{
		static uint32_t lastClocks = 0;
		myassert(clocks - lastClocks <= 1);
		lastClocks = clocks;

		int division = mArp->GetDivision();
		if (clocks % division == 0)
		{
			PlayNextNote();
		}
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
		/*
		GatePlayer* gatePlayer = GetGatePlayer();
		myassert(gatePlayer);
		gatePlayer->NoteOn(note, velocity);		
		*/
		mNoteList.Add(new NoteRecord{0, 0, note, velocity});
		Serial.println("ArpPlayer::NoteOn: bye");
	}

	void ArpPlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		Serial.println("ArpPlayer::NoteOff");
		/*
		GatePlayer* gatePlayer = GetGatePlayer();
		myassert(gatePlayer);
		gatePlayer->NoteOn(note, velocity);
		*/
		for (size_t i=0; i<mNoteList.GetSize(); i++)
		{
			NoteRecord* noteRecord = mNoteList[i];
			if (noteRecord->note == note)
			{
				mNoteList.Remove(noteRecord);
			}
		}	
	}

	TrackPlayer::TrackPlayer(const SongPlayer* songPlayer, TrackId trackId)
	: Player(songPlayer, trackId)
	{
	}

	void TrackPlayer::Start()
	{

	}

	void TrackPlayer::Stop()
	{

	}

    void TrackPlayer::Continue()
	{

	}

	void TrackPlayer::HandleMidiTimingClock(uint32_t midiClocks)
	{
		//Serial.println("TrackPlayer::HandleMidiTimingClock");
		MidiSongPositionPointer midiSongPositionPointer = GetSongPlayer()->GetMidiSongPositionPointer();
		//Serial.println("TrackPlayer::HandleMidiTimingClock 1");
		const Song* song = GetSongPlayer()->GetSong();
		//Serial.println("TrackPlayer::HandleMidiTimingClock 2");
		myassert(song != nullptr);
		//Serial.println("TrackPlayer::HandleMidiTimingClock 3");
		myassert(mTrack != nullptr);

		//SequenceId sequenceId = song->GetSequenceIdForTrackAtSpp(mTrack->GetTrackId(), midiSongPositionPointer);

		// If we hit a new note then hand it to the arpgeggiator
		// If any notes end then remove them from the arpeggiator
		//Serial.println("TrackPlayer::HandleMidiTimingClock: bye");
	}

	void TrackPlayer::NoteOn(uint8_t note, uint8_t velocity)
	{
		ArpId arpId = mCurrentSequence->GetArpId();
		ArpPlayer* arpPlayer = GetSongPlayer()->GetArpPlayer(arpId);
		myassert(arpPlayer);
		arpPlayer->NoteOn(note, velocity);
	}

	void TrackPlayer::NoteOff(uint8_t note, uint8_t velocity)
	{
		ArpId arpId = mCurrentSequence->GetArpId();
		ArpPlayer* arpPlayer = GetSongPlayer()->GetArpPlayer(arpId);
		myassert(arpPlayer);
		arpPlayer->NoteOff(note, velocity);
	}

	SongPlayer::SongPlayer()
	: mSong(nullptr)
	, mIsPlaying(false)
	, mMidiSongPositionPointer(0)
	{
		EventController::EventHandler handler = [&](const Event& event) { this->HandleMidiSystemRealTimeMessage(event); return 0; };
		EventController::GetInstance()->AddEventHandler(EventType::MidiSystemRealTimeMessage, handler);
	}

	void SongPlayer::HandleMidiSystemRealTimeMessage(const Event& event)
	{
		myassert(event.GetEventType() == EventType::MidiSystemRealTimeMessage);
		const MidiSystemRealTimeMessage& midiSystemRealTimeMessage = static_cast<const MidiSystemRealTimeMessage&>(event);
		switch (midiSystemRealTimeMessage.GetSystemRealTimeMessageId())
		{
			case MidiSystemRealTimeMessageId::TimingClock:
				HandleMidiTimingClock();
				break;
			case MidiSystemRealTimeMessageId::Start:
				Start();
				break;
			case MidiSystemRealTimeMessageId::Continue:
				Continue();
				break;
			case MidiSystemRealTimeMessageId::Stop:
				Stop();
				break;
			case MidiSystemRealTimeMessageId::ActiveSensing:
				myassertmsg(false, "Unexpected ActiveSensing");
				break;
			case MidiSystemRealTimeMessageId::SystemReset:
				myassertmsg(false, "Unexpected SystemReset");
				break;
			default:
				myassertmsg(false, "Illegal MidiSystemRealTimeMessageId");
		}
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
		delay(2000);

		mSong = song;

		for (size_t i=0; i<song->GetNumTracks(); i++)
		{
			Serial.print("new TrackPlayer with songplayer "); Serial.println((int)this);
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

		Start();
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
		Serial.println("SongPlayer::Start");
		if (!mIsPlaying)
		{
			mMidiSongPositionPointer = 0;
			mNumMidiClocksFromSpp = 0;
			mStartTime = millis();
		
			for (size_t n=0; n<mTrackPlayers.GetSize(); n++)
			{
				TrackPlayer* trackPlayer = mTrackPlayers[n];
				myassert(trackPlayer);
				trackPlayer->Start();
			}

			for (size_t n=0; n<mArpPlayers.GetSize(); n++)
			{
				ArpPlayer* arpPlayer = mArpPlayers[n];
				myassert(arpPlayer);
				arpPlayer->Start();
			}

			for (size_t n=0; n<mGatePlayers.GetSize(); n++)
			{
				GatePlayer* gatePlayer = mGatePlayers[n];
				myassert(gatePlayer);
				gatePlayer->Start();
			}
		}
	}

	void SongPlayer::Stop()
	{
		Serial.println("SongPlayer::Stop");
		if (mIsPlaying)
		{
			mIsPlaying = false;

			for (size_t n=0; n<mTrackPlayers.GetSize(); n++)
			{
				TrackPlayer* trackPlayer = mTrackPlayers[n];
				myassert(trackPlayer);
				trackPlayer->Stop();
			}

			for (size_t n=0; n<mArpPlayers.GetSize(); n++)
			{
				ArpPlayer* arpPlayer = mArpPlayers[n];
				myassert(arpPlayer);
				arpPlayer->Stop();
			}

			for (size_t n=0; n<mGatePlayers.GetSize(); n++)
			{
				GatePlayer* gatePlayer = mGatePlayers[n];
				myassert(gatePlayer);
				gatePlayer->Stop();
			}
		}
		else
		{
			// Reset song when user taps top twice
			Start();
		}
	}

	void SongPlayer::Continue()
	{
		Serial.println("SongPlayer::Continue");
		mIsPlaying = true;
	}

	void SongPlayer::SetMidiSongPositionPointer(MidiSongPositionPointer midiSongPositionPointer)
	{
		// TODO: should this be ignored if not playing?
		mMidiSongPositionPointer = midiSongPositionPointer;
	}

	void SongPlayer::HandleMidiTimingClock()
	{
		if (mIsPlaying)
		{
			double tempo = mSong->GetTempo();
			double elapsed = (double)millis() - mStartTime;
			double pulses = elapsed * tempo * 24 / 60000;
			for (uint32_t pulsenum = mNumMidiClocksFromSpp+1; pulsenum <= pulses; pulsenum++)
			{
				mNumMidiClocksFromSpp = pulsenum;
				for (size_t n=0; n<mTrackPlayers.GetSize(); n++)
				{
					TrackPlayer* trackPlayer = mTrackPlayers[n];
					myassert(trackPlayer);
					trackPlayer->HandleMidiTimingClock(mNumMidiClocksFromSpp);
				}

				for (size_t n=0; n<mArpPlayers.GetSize(); n++)
				{
					ArpPlayer* arpPlayer = mArpPlayers[n];
					myassert(arpPlayer);
					arpPlayer->HandleMidiTimingClock(mNumMidiClocksFromSpp);
				}

				for (size_t n=0; n<mGatePlayers.GetSize(); n++)
				{
					GatePlayer* gatePlayer = mGatePlayers[n];
					myassert(gatePlayer);
					gatePlayer->HandleMidiTimingClock(mNumMidiClocksFromSpp);
				}
			}
		}
	}
}

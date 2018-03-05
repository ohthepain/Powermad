// SongPlayer

#pragma once
#include "Song.h"

namespace Atomic
{
    class SongPlayer;
	class TrackPlayer;

	class Player
	{
	public:
		Player(const SongPlayer* songPlayer, const Player* parent, TrackId trackId) : mSongPlayer(songPlayer), mParent(parent) {}
		virtual ~Player() {}
		const Player* GetParent() const { myassert(mParent != nullptr); return mParent; }
		const SongPlayer* GetSongPlayer() const { myassert(mSongPlayer != nullptr); return mSongPlayer; }
		const Song* GetSong() const;
		virtual MidiSourceId GetMidiSourceId() const { myassert(mParent); myassert(mParent != this); return mParent->GetMidiSourceId(); }
		virtual MidiChannel GetMidiChannel() const { myassert(mParent); myassert(mParent != this); return mParent->GetMidiChannel(); }

		virtual void Update(uint32_t midiClocks) = 0;

	private:
		const SongPlayer* mSongPlayer;
		const Player* mParent;
		TrackId mTrackId;
	};

	class GatePlayer : public Player
	{
	public:
		GatePlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId);
		virtual ~GatePlayer() {}		

		void Update(uint32_t midiClocks) {}
		void SetGate(Gate* gate) { mGate = gate; }
	private:
		const Gate* mGate;
	};

	class ArpPlayer : public Player
	{
	public:
		const uint8_t kMaxNotes = 8;

		ArpPlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId);
		virtual ~ArpPlayer();

		void Update(uint32_t midiClocks);
		void SetArp(const Arp *arp) { mArp = arp; }

		void NoteOn(uint8_t note, uint8_t velocity);
		void NoteOff(uint8_t note, uint8_t velocity);
	private:
		const Arp* mArp;
		uint8_t* mNoteNum;
		uint8_t* mNoteVelocity;
		int mCurrentNoteNum;
		Vector<GatePlayer*> mGatePlayers;
	};

    class TrackPlayer : public Player
    {
    public:
        TrackPlayer(const SongPlayer* songPlayer, const Player* parent, TrackId trackId);
		virtual ~TrackPlayer() {}

        void SetSongPlayer(SongPlayer* songPlayer) { mSongPlayer = songPlayer; }
		void SetTrack(Track* track) { mTrack = track; }
		const Track* GetTrack() const { return mTrack; }
		MidiSourceId GetMidiSourceId() const { return mMidiSourceId; }
		void SetMidiSourceId(MidiSourceId midiSourceId) { mMidiSourceId = midiSourceId; }

        void Start();
        void Stop();
        void Continue();
		void Update(uint32_t midiClocks);

		void NoteOn(uint8_t note, uint8_t velocity);
		void NoteOff(uint8_t note, uint8_t velocity);
    private:
		const int kMaxArpPlayers = 1;
		const Track* mTrack;
        const SongPlayer* mSongPlayer;
		Vector<ArpPlayer*> mArpPlayers;
		MidiSourceId mMidiSourceId;
    };

    class SongPlayer
    {
    public:
		const size_t kMaxTracks = 32;

		static void Init();
		static void Shutdown();
		static SongPlayer* GetInstance() { myassert(mInstance); return mInstance; }
		
		void LoadSong();

        const TrackPlayer* GetTrackPlayer(TrackId trackId) const;
		void SetSong(const Song* song);
		const Song* GetSong() const { return mSong; }

        void Start();
        void Stop();
        void Continue();
        void SetMidiSongPositionPointer(MidiSongPositionPointer midiSongPositionPointer);
        MidiSongPositionPointer GetMidiSongPositionPointer() const { return mMidiSongPositionPointer; }

		void Update();

    private:
		static SongPlayer* mInstance;
        SongPlayer();
        virtual ~SongPlayer();

		const Song* mSong;
		Vector<TrackPlayer*> mTrackPlayer;
		bool mIsPlaying;
		MidiSongPositionPointer mMidiSongPositionPointer;
		uint32_t mNumMidiClocksFromSpp;
    };
}

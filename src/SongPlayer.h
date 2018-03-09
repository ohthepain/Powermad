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
		Player(const SongPlayer* songPlayer, TrackId trackId) : mSongPlayer(songPlayer), mTrackId(trackId) {}
		virtual ~Player() {}
		const Player* GetParent() const { myassert(mParent != nullptr); return mParent; }
		void SetParent(Player* parent) { mParent = parent; }
		const SongPlayer* GetSongPlayer() const { myassert(mSongPlayer != nullptr); return mSongPlayer; }
		const Song* GetSong() const;
		TrackId GetTrackId() const { return mTrackId; }
		virtual MidiSourceId GetMidiSourceId() const;
		virtual MidiChannel GetMidiChannel() const;

		virtual void Update(uint32_t midiClocks) = 0;

	private:
		const SongPlayer* mSongPlayer;
		const Player* mParent;
		TrackId mTrackId;
	};

	class GatePlayer : public Player
	{
	public:
		GatePlayer(const SongPlayer* songPlayer, TrackId trackId);
		virtual ~GatePlayer() {}		

		void Update(uint32_t midiClocks) {}
		void SetGate(const Gate* gate) { mGate = gate; }

		void NoteOn(uint8_t note, uint8_t velocity);
		void NoteOff(uint8_t note, uint8_t velocity);
	private:
		const Gate* mGate;
	};

	class ArpPlayer : public Player
	{
	public:
		const uint8_t kMaxNotes = 8;

		ArpPlayer(const SongPlayer* songPlayer, TrackId trackId);
		virtual ~ArpPlayer();

		void Update(uint32_t midiClocks);
		void SetArp(const Arp *arp) { mArp = arp; }

		void NoteOn(uint8_t note, uint8_t velocity);
		void NoteOff(uint8_t note, uint8_t velocity);
	private:
		// An arp only has one gate player. The 'envelopes' should be owned by the sequence?
		GatePlayer* GetGatePlayer();

		const Arp* mArp;
		uint8_t* mNoteNum;
		uint8_t* mNoteVelocity;
		int mCurrentNoteNum;
	};

    class TrackPlayer : public Player
    {
    public:
        TrackPlayer(const SongPlayer* songPlayer, TrackId trackId);
		virtual ~TrackPlayer() {}

        void SetSongPlayer(SongPlayer* songPlayer) { mSongPlayer = songPlayer; }
		void SetTrack(const Track* track) { mTrack = track; }
		const Track* GetTrack() const { return mTrack; }
		void SetCurrentSequence(const Sequence* sequence) { mCurrentSequence = sequence; }

        void Start();
        void Stop();
        void Continue();
		void Update(uint32_t midiClocks);

		void NoteOn(uint8_t note, uint8_t velocity);
		void NoteOff(uint8_t note, uint8_t velocity);
    private:
		const int kMaxArpPlayers = 1;
		const Track* mTrack;
		const Sequence* mCurrentSequence;
        const SongPlayer* mSongPlayer;
    };

    class SongPlayer
    {
    public:
		const size_t kMaxTracks = 32;

		static void Init();
		static void Shutdown();
		static SongPlayer* GetInstance() { myassert(mInstance); return mInstance; }
		
		void LoadSong();

		GatePlayer* GetGatePlayer(GateId gateId) const { return mGatePlayers[gateId]; }
		ArpPlayer* GetArpPlayer(ArpId arpId) const { return mArpPlayers[arpId]; }
        TrackPlayer* GetTrackPlayer(TrackId trackId) const { return mTrackPlayers[trackId]; }
		void SetSong(const Song* song);
		void ClearSong();
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
		Vector<GatePlayer*> mGatePlayers;
		Vector<ArpPlayer*> mArpPlayers;
		// No sequence player between track and arp!
		Vector<TrackPlayer*> mTrackPlayers;
		bool mIsPlaying;
		MidiSongPositionPointer mMidiSongPositionPointer;
		uint32_t mNumMidiClocksFromSpp;
    };
}

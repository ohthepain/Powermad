// Song.h

#pragma once
#include "Vector.h"
#include "MidiManager.h"
#include <stdint.h>

namespace Atomic
{
    typedef uint8_t SequenceId;
    typedef uint8_t TrackId;
    typedef uint8_t ArpId;
    typedef uint8_t GateId;
    typedef uint8_t PartId;
    typedef uint16_t MidiSongPositionPointer;

    enum class ScaleId
    {
        Parent,
        Song,
        NoteMask,
    };

    class Gate
    {
        uint8_t mTarget;
        uint8_t mCcNum;
        uint8_t mResolution;
        uint8_t mLength;
    };

    class Arp
    {
    public:
        Arp() {}
        virtual ~Arp() {}

        // 24 clocks in a quarter note
        int GetDivision() const { return 6; }
    };

    class Sequence
    {
    public:
        Sequence() {}
        virtual ~Sequence() {}

    private:
        SequenceId mSequenceId;
        ArpId mArpId;
        uint8_t mMidiChannel;
    };

    class Track
    {
    public:
        Track() : mTrackId(1), mMidiSourceId(MidiSourceId::USB), mMidiChannel(1) {}
        virtual ~Track() {}

        TrackId GetTrackId() const { return mTrackId; }
        uint8_t GetMidiChannel() const { return mMidiChannel; }
        MidiSourceId GetMidiSourceId() const { return mMidiSourceId; }

    private:
        TrackId mTrackId;
        MidiSourceId mMidiSourceId;
        uint8_t mMidiChannel;
    };

    class Part
    {
        // A set of sequences and a length
        uint16_t mPartId;
        uint16_t mLength;
    };
    
    class Song
    {
    public:
        Song();
        virtual ~Song();

        double GetTempo() { return mTempo; }

        // SPP = num midi beats from start. Each MIDI Beat is a 16th note (since there are 24 MIDI Clocks in a quarter note).
        SequenceId GetSequenceIdForTrackAtSpp(TrackId trackId, MidiSongPositionPointer spp) const { return 1; }
        const Track* GetTrack(TrackId trackId) const;
        const Sequence* GetSequence(SequenceId sequenceId) const;
        const Arp* GetArp(ArpId arpId)const;
        const Gate* GetGate(GateId gateId) const;

        size_t GetNumTracks() const { return 1; }
        size_t GetNumSequences() const { return 1; }
        size_t GetNumArps() const { return 1; }
        size_t GetNumGates() const { return 1; }

    private:
        double mTempo;
        Vector<Part*> mPartList;
        Vector<Track*> mTracks;
        Vector<Sequence*> mSequences;
        Vector<Arp*> mArps;
        Vector<Gate*> mGates;
    };

    class ViewPreferences
    {
        uint8_t mResolution;
        bool mChase;
    };
}
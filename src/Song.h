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
    typedef uint8_t MidiChannel;
    typedef uint16_t MidiSongPositionPointer;
    typedef uint8_t value_t;
    typedef size_t index_t;

    enum class ScaleId
    {
        Parent,
        Song,
        NoteMask,
    };

    class Gate
    {
    public:
        Gate(GateId gateId) : mGateId(gateId) {}
        virtual ~Gate() {}

        GateId GetGateId() const { return mGateId; }

    private:
        GateId mGateId;
        uint8_t mTarget;
        uint8_t mCcNum;
        uint8_t mResolution;
        uint8_t mLength;
    };

    class ValueList : public Vector<uint8_t>
    {
        virtual ~ValueList() {}
    };

    class Arp
    {
    public:
        enum class PatternId {
            Up = 1,
            Down,
            UpDown,
            Random,
            Assign
        };

        enum class DestinationId {
            Note=0,
            Velocity,
            AB,
            MidiContinuousController,
            Transpose,
            Enable
        };

        Arp(ArpId arpId);
        virtual ~Arp() {}

        // 24 clocks in a quarter note
        ArpId GetArpId() const { return mArpId; }
        void SetDivision(int division) { mDivision = division; }
        int GetDivision() const { return mDivision; }
        void SetGateId(GateId gateId) { mGateId = gateId; }
        GateId GetGateId() const { return mGateId; }
        void SetLength(uint32_t length) { mLength = length; }
        size_t GetLength() const { return mLength; }
        void SetOctaves(value_t octaves) { mOctaves = octaves; }
        value_t GetOctaves() const { return mOctaves; }
        void SetPattern(PatternId patternId) { mPatternId = patternId; }
        PatternId GetPatternId() const { return mPatternId; }

        uint8_t SetValue(DestinationId destinationId, int slotnum, value_t value);
        value_t GetValue(DestinationId destinationId, int slotnum) const;
        value_t GetNote(int slotnum) const;
        void SetNote(int slotnum, uint8_t notenum);

    private:
        ArpId mArpId;
        GateId mGateId;
        uint8_t mDivision;
        uint32_t mLength;
        value_t mOctaves;
        PatternId mPatternId;
        Vector<ValueList*> maValueList;
    };

    class Sequence
    {
    public:
        Sequence(SequenceId sequenceId) : mSequenceId(sequenceId) {}
        virtual ~Sequence() {}

        SequenceId GetSequenceId() const { return mSequenceId; }
        void SetArpId(ArpId arpId) { mArpId = arpId; }
        ArpId GetArpId() const { return mArpId; }

    private:
        SequenceId mSequenceId;
        ArpId mArpId;
        MidiChannel mMidiChannel;
    };

    class Track
    {
    public:
        Track(TrackId trackId) : mTrackId(trackId), mMidiSourceId(MidiSourceId::MidiPort), mMidiChannel(1) {}
        virtual ~Track() {}

        TrackId GetTrackId() const { return mTrackId; }
        void SetMidiChannel(MidiChannel midiChannel) { mMidiChannel = midiChannel; }
        uint8_t GetMidiChannel() const { return mMidiChannel; }
        void SetMidiSourceId(MidiSourceId midiSourceId) { mMidiSourceId = midiSourceId; }
        MidiSourceId GetMidiSourceId() const { return mMidiSourceId; }
        void SetSequenceId(SequenceId sequenceId) { mSequenceId = sequenceId; }
        SequenceId GetSequenceId() const { return mSequenceId; }

    private:
        TrackId mTrackId;
        MidiSourceId mMidiSourceId;
        MidiChannel mMidiChannel;
        SequenceId mSequenceId;
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

        double GetTempo() const { return mTempo; }

        // SPP = num midi beats from start. Each MIDI Beat is a 16th note (since there are 24 MIDI Clocks in a quarter note).
        SequenceId GetSequenceIdForTrackAtSpp(TrackId trackId, MidiSongPositionPointer spp) const { return 1; }
        Track* GetTrack(TrackId trackId) const;
        Sequence* GetSequence(SequenceId sequenceId) const;
        Arp* GetArp(ArpId arpId)const;
        Gate* GetGate(GateId gateId) const;

        void AddTrack(Track* track);
        void AddSequence(Sequence* sequence);
        void AddArp(Arp* arp);
        void AddGate(Gate* gate);

        size_t GetNumTracks() const { return mTracks.GetSize(); }
        size_t GetNumSequences() const { return mSequences.GetSize(); }
        size_t GetNumArps() const { return mArps.GetSize(); }
        size_t GetNumGates() const { return mGates.GetSize(); }

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
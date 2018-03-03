// Song.h

#pragma once

#include <stdint.h>
#include <list>
#include "MidiManager.h"

namespace Atomic
{
    const uint8_t kTargetSong = 1;

    enum class ScaleId
    {
        Parent,
        Song,
        NoteMask,
    };

    class TranceGate
    {
        uint8_t mTarget;
        uint8_t mCcNum;
        uint8_t mResolution;
        uint8_t mLength;
    };

    class Sequence
    {
    public:
        Sequence() : mMidiSourceId(MidiSourceId::USB), mMidiChannel(1) {}
        virtual ~Sequence() {}

        MidiSourceId GetMidiSourceId() { return mMidiSourceId; }
        uint8_t GetMidiChannel() { return mMidiChannel; }

    private:
        uint16_t mSequenceId;
        // USB, etc
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
            ~Song() {}

            double GetTempo() { return mTempo; }

        private:
            double mTempo;
            std::list<Part> mPartList;
    };

    class ViewPreferences
    {
        uint8_t mResolution;
        bool mChase;
    };
}
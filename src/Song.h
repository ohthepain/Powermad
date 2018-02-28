// Song.h

#pragma once

#include <stdint.h>
#include <list>

namespace Atomic
{
    const uint8_t kTargetSong = 1;

    class TranceGate
    {
        uint8_t mTarget;
        uint8_t mCcNum;
        uint8_t mResolution;
        uint8_t mLength;
    };

    class Sequence
    {
        uint16_t mSequenceId;
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
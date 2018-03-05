// Song.cpp

#include "Song.h"

namespace Atomic
{
	Song::Song()
	: mTempo(120.0)
	{
		Track track;
		mTracks.Add(new Track);
		mSequences.Add(new Sequence);
		mArps.Add(new Arp);
		mGates.Add(new Gate);
	}

	Song::~Song()
	{
	}

	const Track* Song::GetTrack(TrackId trackId) const
	{
		myassert(trackId < GetNumTracks());
		return mTracks[trackId];
	}

	const Sequence* Song::GetSequence(SequenceId sequenceId) const
	{
		myassert(sequenceId < GetNumSequences());
		return mSequences[sequenceId];
	}

    const Arp* Song::GetArp(ArpId arpId) const
	{
		myassert(arpId < GetNumArps());
		return mArps[arpId];
	}

	const Gate* Song::GetGate(GateId gateId) const
	{
		myassert(gateId < GetNumGates());
		return mGates[gateId];
	}
}

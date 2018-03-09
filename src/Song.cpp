// Song.cpp

#include "Song.h"

namespace Atomic
{
	Song::Song()
	: mTempo(120.0)
	{
	}

	Song::~Song()
	{
	}

	Track* Song::GetTrack(TrackId trackId) const
	{
		myassert(trackId < GetNumTracks());
		return mTracks[trackId];
	}

	Sequence* Song::GetSequence(SequenceId sequenceId) const
	{
		myassert(sequenceId < GetNumSequences());
		return mSequences[sequenceId];
	}

    Arp* Song::GetArp(ArpId arpId) const
	{
		myassert(arpId < GetNumArps());
		return mArps[arpId];
	}

	Gate* Song::GetGate(GateId gateId) const
	{
		myassert(gateId < GetNumGates());
		return mGates[gateId];
	}

	void Song::AddTrack(Track* track)
	{
		myassert(track->GetTrackId() == GetNumTracks());
		mTracks.Add(track);
	}

    void Song::AddSequence(Sequence* sequence)
	{
		myassert(sequence->GetSequenceId() == GetNumSequences());
		mSequences.Add(sequence);
	}
	
    void Song::AddArp(Arp* arp)
	{
		myassert(arp->GetArpId() == GetNumArps());
		mArps.Add(arp);
	}
	
    void Song::AddGate(Gate* gate)
	{
		myassert(gate->GetGateId() == GetNumGates());
		mGates.Add(gate);
	}
}

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

	Arp::Arp(ArpId arpId) : mArpId(arpId), mDivision(6), mLength(8)
	{
		ValueList* valueList = new ValueList;
		for (int i=0; i<8; i++)
		{
			valueList->Add(60);
		}
		maValueList.Add(valueList);
	}

	uint8_t Arp::GetNote(int n) const
	{
		myassert((size_t)n < GetLength());
		const ValueList& valueList = *(maValueList[0]);
		uint8_t note = valueList[n];
		return note;
	}

	value_t Arp::GetValue(DestinationId destinationId, int slotnum) const
	{
		myassert((size_t)destinationId < maValueList.GetSize());
		const ValueList* valueList = maValueList[(int)destinationId];
		return (*valueList)[slotnum];
	}

	void Arp::SetNote(int slotnum, uint8_t notenum)
	{
		SetValue(DestinationId::Note, slotnum, notenum);
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

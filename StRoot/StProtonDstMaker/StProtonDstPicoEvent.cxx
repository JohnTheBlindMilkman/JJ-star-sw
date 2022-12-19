#include "StProtonDstPicoEvent.h"

#include "TClonesArray.h"

ClassImp(StProtonDstPicoEvent)

StProtonDstPicoEvent::StProtonDstPicoEvent() 
{
    fPrimaryTracks = new TClonesArray("PicoTrack",2000);
    mNPrimaryTracks = 0;
}

StProtonDstPicoTrack* StProtonDstPicoEvent::AddPrimaryTrack() 
{
  TClonesArray &tracks = *fPrimaryTracks;
  StProtonDstPicoTrack *track = new(tracks[mNPrimaryTracks++]) StProtonDstPicoTrack;
  return track;
}

void StProtonDstPicoEvent::Clear(const Option_t* option) 
{
    fPrimaryTracks->Clear("C");
    mNPrimaryTracks=0;
}

PicoEventB::~StProtonDstPicoEvent() 
{
}
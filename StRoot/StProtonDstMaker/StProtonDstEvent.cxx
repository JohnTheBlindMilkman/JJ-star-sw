#include "StProtonDstEvent.h"

#include "TClonesArray.h"

ClassImp(StProtonDstEvent)

StProtonDstEvent::StProtonDstEvent() 
{
    // Create an Event object.
    fProtonTracks = new TClonesArray("Track", 2000);
    mNPionTracks = 0;
}

Track* StProtonDstEvent::AddProtonTrack() 
{                                                                      
    TClonesArray &tracks = *fProtonTracks;
    StProtonDstTrack *track = new(tracks[mNPionTracks++]) StProtonDstTrack;
    return track;
}

void StProtonDstEvent::Clear(const Option_t* option) 
{
    fProtonTracks->Clear("C"); 
    mNPionTracks = 0;
}

StProtonDstEvent::~StProtonDstEvent() 
{
}

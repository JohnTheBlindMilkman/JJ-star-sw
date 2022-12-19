#ifndef StProtonDstHbtReader_h
#define StProtonDstHbtReader_h

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TArrayI.h"

#include "StHbtEventReader.hh"
#include "StHbtEnumeration.hh"
#include "StMaker.h"
#include "StChain.h"
#include "St_DataSetIter.h"
#include "StHbtEvent.hh"
#include "StIOMaker.h"
#include "StEnumerations.h"
#include "StStrangeMuDstMaker.h"

#include "StProtonDstEvent.h"

#include <stdlib.h>

class StProtonDstHbtReader : public StHbtEventReader 
{
    public:
        StProtonDstHbtReader(StHbtIOMode mode, StIOMaker* io, const char* dirName, const char* fileName, const char* filter=".", int maxFiles=999);
        ~StProtonDstHbtReader();
        StHbtEvent* ReturnHbtEvent();
        StHbtString Report();
        TH1D* ReturnRPdistribution() { return fRPdistribution;};
        void SetDebug(int);
        TArrayI shuffleOrder(int arraySize);

    private:
        StIOMaker* mIOMaker;
        StHbtIOMode mIOMode;
        TString mCurrentFileName,mDir,mFile,mFilter,mInputDir;
        int mMaxFiles,mDebug,mTracks;
        TChain* mTChain; 
        TFile* mCurrentFile;
        TTree* mTTree;
        int[] mTrackIndexArray;
        TH1D *fRPdistribution;
        StProtonDstEvent* mEvent; 
        StHbtEvent* mHbtEvent; 
        unsigned int mEventIndex,mEvents;
        void read();
        int initRead(const char* dir, const char* file, const char* filter, int mMaxFiles);
        int uninitRead();
        int fillChain(TChain* chain, const char* dir, const char* filter, const int maxFiles);
        int fillChain(TChain* chain, const char* list, const int maxFiles);
    
    ClassDef(StProtonDstHbtReader, 1)
};

inline void StProtonDstHbtReader::SetDebug(int debug) {mDebug=debug;}
  
#endif


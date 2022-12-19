#ifndef StProtonDstPicoDstMaker_hh
#define StProtonDstPicoDstMaker_hh
#include "StMaker.h"
#include "StThreeVectorF.hh"
#include "StPhysicalHelixD.hh"
#include "StProtonDstEvent.h"
#include "StProtonDstTrack.h"
#include "StMuDst.h"
#include "StMuDstMaker.h"
#include "StMuTrack.h"
#include "StMuEvent.h"

#include "TFile.h"
#include "TString.h"
#include "TArrayI.h"

#ifndef St_NO_NAMESPACES
using std::string;
#endif

class StProtonDstPicoDstMaker : public StMaker 
{
    public:
        StProtonDstPicoDstMaker(StMuDstMaker* maker);
        ~StProtonDstPicoDstMaker() {;}
        
        void Clear(Option_t *option="");
        Int_t Init();
        Int_t Make();
        Int_t Finish();
        
        StMuDst* muDst();
        void setMuDstMaker(StMuDstMaker*);
        void setFileName(TString fileName) {mFileName = fileName;}
    
    private:
        bool accept(StMuDst*);
        bool acceptPrimaryTrack(StMuTrack*);
        bool acceptGlobalTrack(StMuTrack*);
        
        StMuDstMaker *mMuDstMaker; //!
        TString mFileName; //!
        TString mLastMuFile; //!
        TFile *mFile; //!
        StMuEvent *mMuEvent;         //! pointer to Mu-DST Event array
        TObjArray* mMuTracks;        //! Mu-DST Primary Tracks
        TObjArray* mMuGlobalTracks;  //! Mu-DST Global Tracks
        
        TTree *mTree; //!
        int nEventsPassed;
        int nEventsFailed;
        PicoEventB *mEvent;
        int nBytes;
        int bin;

        Float_t CalcDcaSigned(const StThreeVectorF vertex, const StPhysicalHelixD helix);

  
  ClassDef(StProtonDstPicoDstMaker,1)
};

inline void PicoDstMakerB::setMuDstMaker(StMuDstMaker* f) {mMuDstMaker=f;}

#endif
  

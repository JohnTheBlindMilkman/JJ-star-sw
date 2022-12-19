#ifndef StProtonDstMaker_hh     
#define StProtonDstMaker_hh

#include "StMaker.h"

#include "StProtonDstPicoEvent.h"
#include "StProtonDstPicoTrack.h"
#include "StProtonDstEvent.h"
#include "StProtonDstTrack.h"

#include "StMuDst.h"
#include "StMuDstMaker.h"
#include "StMuTrack.h"

#include "StFlowAnalysisMaker.h"
#include "StFlowPhiWgtMaker.h"
#include "StFlowMaker.h"

#include "TFile.h"
#include "TString.h"
#include "TArrayI.h"

// Leave this in
#ifndef ST_NO_NAMESPACES
using std::string;
#endif

class StProtonDstMaker : public StMaker 
{
    public:
        StProtonDstMaker();
        ~StProtonDstMaker();

        void Clear(Option_t *option="");    
        Int_t Init();                      
        Int_t Make();                      
        Int_t Finish();                    

        StMuDst* muDst();
        void setMuDstMaker(StMuDstMaker*);
        void setFlowPhiWgtMaker(StFlowPhiWgtMaker*);
        void setFlowMaker(StFlowMaker*);
        void setFileName(TString fileName) {mFileName = fileName;}

    private:
        bool accept(StProtonDstPicoEvent*); 
        bool acceptPion(StProtonDstPicoTrack*); 
        bool acceptKaon(StProtonDstPicoTrack*); 
        bool acceptProton(StProtonDstPicoTrack*); 
        bool acceptHiPt(StProtonDstPicoTrack*); 
        bool CheckId(int runnr); //if we're not using this, why is this here? - JJ

        StMuDstMaker* mMuDstMaker; 
        StFlowPhiWgtMaker* mFlowPhiWgtMaker;
        StFlowMaker *mFlowMaker; 
        StFlowAnalysisMaker *mFlowAnaMaker; 

        Bool_t mFlowMakerPassFailFlag; 
        TString mFileName,mLastMuFile;      
        TFile *mFile;         
        TTree *mTree;				  
        int nEventsPassed,nEventsFailed,nEventsFailedDueToFlowFlagCut,nBytes,bin;
        Event *mEvent;
        double  pt,pz;
	
    ClassDef(StProtonDstMaker,1)
};

inline void StProtonDstMaker::setMuDstMaker(StMuDstMaker* f) {mMuDstMaker=f;}
inline void StProtonDstMaker::setFlowPhiWgtMaker(StFlowPhiWgtMaker* f) {mFlowPhiWgtMaker=f;}
inline void StProtonDstMaker::setFlowMaker(StFlowMaker* f) {mFlowMaker=f;}

#endif

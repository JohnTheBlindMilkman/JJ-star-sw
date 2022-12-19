#include "StProtonDstPicoDstMaker.h"
#include "StEventTypes.h"
#include "StMuDSTMaker/COMMON/StMuException.hh"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StMuDSTMaker/COMMON/StMuCut.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StHbtMaker/Infrastructure/StHbtEvent.hh"
#include "StProtonDstPicoEvent.h"
#include "StProtonDstPicoTrack.h"

#include "TChain.h"
#include "StMessMgr.h"
#include "TClonesArray.h"
#include "TBranch.h"
#include "TTree.h"

ClassImp(StProtonDstPicoDstMaker)

StProtonDstPicoDstMaker::StProtonDstPicoDstMaker(StMuDstMaker *maker) : StMaker("StProtonDstPicoDstMaker") 
{
    mFile = 0;
    mLastMuFile = "";
    nEventsPassed = nEventsFailed = 0;
    mMuDstMaker  = maker;
}

Int_t StProtonDstPicoDstMaker::Init() 
{
    mFile = new TFile(mFileName.Data(), "RECREATE");
    cout << "The output filename is " << mFileName.Data() << endl;
    
    mTree = new TTree("PicoDst","PicoDst");
    cout << "StProtonDstPicoDstMaker: made the tree" << endl;
    mTree->AutoSave();
    mFile->SaveSelf();
    
    cout << "StProtonDstPicoDstMaker: saving settings for mTree and mFile done. " << endl;
    mEvent = new StProtonDstPicoEvent();
    
    if(mTree) 
        cout << "StProtonDstPicoDstMaker: mEvent allocated." << endl;
    mTree->Branch("StProtonDstPicoEvent","StProtonDstPicoEvent",&mEvent);
    cout << "StProtonDstPicoDstMaker: StProtonDstPicoEvent branch is made" << endl;
    nBytes = 0;
    
    cout << "StProtonDstPicoDstMaker: end of PDMB::Init()" << endl;
    return StMaker::Init();
}

Int_t StProtonDstPicoDstMaker::Make() 
{ 
    TString currentMuFile = mMuDstMaker->chain()->GetFile()->GetName();
    if (currentMuFile.CompareTo(mLastMuFile)) 
    {
        cout << "New File: " << currentMuFile.Data() << endl;
        mLastMuFile = currentMuFile;
    }
    
    StMuDst *muDst = mMuDstMaker->muDst();
    if(!accept(muDst)) 
    {
        nEventsFailed++;
        return kStOk;
    }

    mMuEvent = muDst->event();
    mMuTracks = 0;
    mMuGlobalTracks = 0;
    mMuTracks = muDst->primaryTracks();
    mMuGlobalTracks = muDst->globalTracks();
    
    mEvent->SetRunID(mMuEvent->runId());
    mEvent->SetCenterOfMassEnergy(mMuEvent->runInfo().centerOfMassEnergy());
    mEvent->SetMagneticField(mMuEvent->runInfo().magneticField());
    mEvent->SetUncorrNegMult(mMuEvent->refMultNeg());
    mEvent->SetUncorrPosMult(mMuEvent->refMultPos());

    if( (mMuEvent->runId() > 8000000) && (mMuEvent->runId() < 9000000) ) //year 7 only
        mEvent->SetMultEta(mMuEvent->grefmult()); //is this correct
    else 
        mEvent->SetMultEta(mMuEvent->refMult());

    mEvent->SetEventID(mMuEvent->eventId());
    mEvent->SetVertexPos(mMuEvent->primaryVertexPosition());
    mEvent->SetBeamMassNumberEast(mMuEvent->runInfo().beamMassNumber(east));
    mEvent->SetBeamMassNumberWest(mMuEvent->runInfo().beamMassNumber(west));
    mEvent->SetCTB(mMuEvent->ctbMultiplicity());
    mEvent->SetZDCe(mMuEvent->zdcAdcAttentuatedSumEast());
    mEvent->SetZDCw(mMuEvent->zdcAdcAttentuatedSumWest());
    mEvent->SetOrigMult(mMuEvent->eventSummary().numberOfGoodPrimaryTracks()); 
    
    mEvent->SetRefMult(mMuEvent->refMult());
    mEvent->SetZdcTriggerDetector(mMuEvent->zdcTriggerDetector());
    mEvent->SetBbcTriggerDetector(mMuEvent->bbcTriggerDetector());
    
    mEvent->SetNglobalTracks(mMuGlobalTracks->GetEntries());
    mEvent->SetTofMult(mMuEvent->btofTrayMultiplicity());
    
    StProtonDstPicoTrack *track = 0;    
    StMuTrack *muTrack;
    
    int nMuTracks = mMuTracks->GetEntries();
    mEvent->SetNumberOfTracksInOriginalPrimaryTrackArray(nMuTracks);
    
    int goodTracks = 0;
    
    for (int j=0; j<nMuTracks; j++)
    {
        muTrack = (StMuTrack*)mMuTracks->UncheckedAt(j);
        if (acceptPrimaryTrack(muTrack)) 
        {
            track = mEvent->AddPrimaryTrack();
            track->SetPt(muTrack->pt());

            if (muTrack->index2Global() < 0) 
            {
                gMessMgr->Info() << "StProtonDstPicoDstMaker: index2Global<0" << endl;
                continue;
            }

            StMuTrack* muGlobalTrack = (StMuTrack*) mMuGlobalTracks->At(muTrack->index2Global());
            if (!muGlobalTrack) 
            {
                gMessMgr->Info() << "StProtonDstPicoDstMaker: no global track" << endl;
                cout << "no global track" << endl;
                continue;
            }
            
            track->SetMsquared( muTrack->p().mag()*muTrack->p().mag()*(1./(muTrack->btofPidTraits().beta()*muTrack->btofPidTraits().beta()) - 1.) ); //track->SetMsquared( muGlobalTrack->btofPidTraits().beta() );
            track->SetPtGlobal(muGlobalTrack->pt());
            track->SetPhi(muTrack->phi());
            track->SetPhiGlobal(muGlobalTrack->phi());
            track->SetEta(muTrack->eta());
            track->SetEtaGlobal(muGlobalTrack->eta());
            track->SetDedx(muTrack->dEdx());
            track->SetCharge(muTrack->charge());
            track->SetDcaSigned(CalcDcaSigned(mMuEvent->primaryVertexPosition(),muTrack->helix()));
            track->SetDca(muTrack->dca().mag());
            track->SetDca3(muTrack->dca());
            track->SetDcaGlobal(muTrack->dcaGlobal().mag());
            track->SetChi2(muTrack->chi2xy()); 
            track->SetTopologyMap(muTrack->topologyMap());
            track->SetNhits(muTrack->nHits());
            track->SetFitPts(muTrack->nHitsFit() - muTrack->nHitsFit(kSvtId) - muTrack->nHitsFit(kSsdId) - 1); //remove additional points
            track->SetMaxPts(muTrack->nHitsPoss() - muTrack->nHitsPoss(kSvtId) - muTrack->nHitsPoss(kSsdId) - 1); //remove additional points
            track->SetNdedxPts(muTrack->nHitsDedx());
            track->SetDcaGlobal3(muTrack->dcaGlobal());
            track->SetTrackLength(muTrack->helix().pathLength(mMuEvent->primaryVertexPosition())); //???
            track->SetZFirstPoint(muTrack->firstPoint().z());
            track->SetZLastPoint(muTrack->lastPoint().z());
            
            track->SetFlag(muTrack->flag());
            track->SetZFirstPointX(muTrack->firstPoint().x());
            track->SetZFirstPointY(muTrack->firstPoint().y());
            track->SetIndex2Global(muTrack->index2Global());
            track->SetHelix(muTrack->helix());
            
            track->SetP(muTrack->p().x(),muTrack->p().y(),muTrack->p().z());
            
            if (muTrack->charge() < 0) // nSigma* are used multiple times, mahe them as variables - JJ
            {
                track->SetPidPiMinus(muTrack->nSigmaPion());  
                track->SetPidAntiProton(muTrack->nSigmaProton());
                track->SetPidKaonMinus(muTrack->nSigmaKaon());
                track->SetPidAntiDeuteron( 999.0 ); // why? - JJ
                track->SetPidElectron(muTrack->nSigmaElectron());
            } 
            else 
            {
                track->SetPidPiPlus(muTrack->nSigmaPion()); 
                track->SetPidProton(muTrack->nSigmaProton()); 
                track->SetPidKaonPlus(muTrack->nSigmaKaon()); 
                track->SetPidDeuteron( 999.0 ); // again, why? - JJ
                track->SetPidPositron(muTrack->nSigmaElectron());
            }
            
            if ( muTrack->nSigmaKaon() > 2.0 ) // I don't understand this... - JJ
            {
                if (muTrack->charge() > 0 ) 
                {
                    track->SetMostLikelihoodPID(14); // proton
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
                else 
                {
                    track->SetMostLikelihoodPID(15); // anti-proton
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
            }
            if ( muTrack->nSigmaPion() > 2.0 ) 
            {
                if (muTrack->charge() > 0 ) 
                {
                    track->SetMostLikelihoodPID(11); // kaon
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
                else 
                {
                    track->SetMostLikelihoodPID(12); // anti-kaon
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
            }
            if ( muTrack->nSigmaPion() < -2.0 ) 
            {
                if (muTrack->charge() < 0 ) 
                {
                    track->SetMostLikelihoodPID(3); // electron
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
                else 
                {
                    track->SetMostLikelihoodPID(2); // positron
                    track->SetMostLikelihoodProb( 0.99 ); // guaranteed
                }
            }

            track->SetExtrapTag(0); // none are in the PID merging area
            track->SetElectronPositronProb(muTrack->pidProbElectron());
            track->SetPionPlusMinusProb(muTrack->pidProbPion());
            track->SetKaonPlusMinusProb(muTrack->pidProbKaon());
            track->SetProtonPbarProb(muTrack->pidProbProton());
            
            goodTracks++;
        }
    } // end loop over tracks
    
    nEventsPassed++;
    nBytes += mTree->Fill();
    mEvent->Clear();
    mMuTracks->Clear();
    mMuGlobalTracks->Clear();
    
    return kStOK;
}

Int_t StProtonDstPicoDstMaker::Finish() 
{
    mFile->Write();
    mFile->Close();
    
    cout << "StProtonDstPicoDstMaker::Finish()" << endl << endl;
    cout << "\t  nEventsPassed: " << nEventsPassed << " events." << endl;
    cout << "\t  nEventsFailed: " << nEventsFailed << " events." << endl;
    
    cout << "Chris : Finish ended : StProtonDstPicoDstMaker.cxx" << endl;
    
    return kStOK;
}

void StProtonDstPicoDstMaker::Clear(Option_t *opt) // once again, why the option? - JJ
{
    StMaker::Clear();
}

bool StProtonDstPicoDstMaker::accept(StMuDst* muDst) 
{
    StMuEvent *muEvent = muDst->event();
    int refMult = muEvent->refMult();

    bool good = false;

    //============================
    //=== REDO THIS PART =========
    //============================ - JJ

    //Year 10, 200 GeV AuAu
    if ( (muEvent->runNumber() >= 11002145) && (muEvent->runNumber() < 11028089) ) 
    {
        if ( muEvent->triggerIdCollection().nominal().isTrigger(260001) ) 
            good = true; //mb1-fast trigger testing
    } 
    else if ( (muEvent->runNumber() >= 11028089) && (muEvent->runNumber() < 11035029) ) 
    {
        if ( muEvent->triggerIdCollection().nominal().isTrigger(260011) ) 
            good = true; //mb1-fast trigger later
    } 
    else if ( (muEvent->runNumber() >= 11035051) && (muEvent->runNumber() <= 11054068) ) 
    {
        if ( muEvent->triggerIdCollection().nominal().isTrigger(260021) ) 
            good = true;
    } 
    else if ( (muEvent->runNumber() >= 11055095) && (muEvent->runNumber() <= 11077018) ) 
    {
        if ( muEvent->triggerIdCollection().nominal().isTrigger(260031) ) 
            good = true;
    } 
    else 
        good = false;	
    
    float vertexX = muEvent->primaryVertexPosition().x();
    float vertexY = muEvent->primaryVertexPosition().y();
    float vertexZ = muEvent->primaryVertexPosition().z();
    
    if (!good) 
        return false;
    if (refMult < 3) 
        return false; //11.5 gev //we'll use this for 19.6 GeV too just to be safe. & 27 GeV too

    if (fabs(vertexX) < 1e-5 && fabs(vertexY) < 1e-5 && fabs(vertexZ) < 1e-5) 
        return false;
    if (sqrt(pow(vertexX,2)+pow(vertexY,2)) > 2.2) 
        return false; //7gev //### will allow to vary Vr value
    if (fabs(vertexZ) > 30.) 
        return false; //70 for 7.7 gev, 50 for 11.5 gev, 30 for 39 gev //### will allow to vary Vz value
        
    return good;
}

bool StProtonDstPicoDstMaker::acceptPrimaryTrack(StMuTrack* track) // wtf? - JJ
{
    return true;
}

bool StProtonDstPicoDstMaker::acceptGlobalTrack(StMuTrack* track) // WAS ZUM TEUFEL - JJ
{
    return true;
}

Float_t StProtonDstPicoDstMaker::CalcDcaSigned(const StThreeVectorF vertex, const StPhysicalHelixD helix) 
{
    double xCenter = helix.xcenter();
    double yCenter = helix.ycenter();
    double radius = 1.0/helix.curvature();
    double dPosCenter = ::sqrt( (vertex.x() - xCenter) * (vertex.x() - xCenter) + (vertex.y() - yCenter) * (vertex.y() - yCenter));

    return (Float_t)(radius - dPosCenter);
}
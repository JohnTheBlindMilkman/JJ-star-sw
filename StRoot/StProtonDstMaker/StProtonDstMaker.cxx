#include "StProtonDstMaker.h"
#include "StEventTypes.h"

#include "TChain.h"
#include "StMessMgr.h"

#include "StFlowMaker/StFlowEvent.h"
#include "StFlowMaker/StFlowSelection.h"

#include "StMuDSTMaker/COMMON/StMuException.hh"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StMuDSTMaker/COMMON/StMuCut.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"

#include "StHbtMaker/Infrastructure/StHbtEvent.hh"

#include "TClonesArray.h"
#include "TBranch.h"

ClassImp(StProtonDstMaker)

StProtonDstMaker::StProtonDstMaker() : StMaker("StProtonDstMaker") 
{
    mFile = 0;
    mLastMuFile = "";
    nEventsPassed = nEventsFailed = 0;
    nEventsFailedDueToFlowFlagCut = 0;
	
    mMuDstMaker = 0; 
    mFlowPhiWgtMaker = 0; 
    mFlowMaker = 0;
    mFlowAnaMaker = 0;
}

StProtonDstMaker::~StProtonDstMaker()
{
}

Int_t StProtonDstMaker::Init() 
{
    mFile =  new TFile(mFileName.Data(), "RECREATE");
    std::cout << "The output filename is " << mFileName.Data() << std::endl;

    mTree = new TTree("ProtonDst","ProtonDst");

    mTree->AutoSave();
    mFile->SaveSelf();

    mEvent = new Event();
        
    mTree->Branch("Event","Event",&mEvent);
    nBytes = 0;
    
    mFlowAnaMaker = (StFlowAnalysisMaker*) GetMaker("FlowAnalysis");

    return StMaker::Init();
}

Int_t StProtonDstMaker::Make() 
{
    mFlowAnaMaker = (StFlowAnalysisMaker*) GetMaker("FlowAnalysis");
    
    StProtonDstPicoEvent *myCurrentPicoEvent = (StProtonDstPicoEvent*) mFlowAnaMaker->getMyStFAMpicoEvent();
    
    mFlowMakerPassFailFlag = kFALSE;  //will get set to true if it passes flow cuts.
    mFlowMakerPassFailFlag = mFlowAnaMaker->getFlowAnalysisMakerEventCutPassFailFlag();

    if(!accept(myCurrentPicoEvent)) 
    {
        nEventsFailed++;
        return kStOk;
    }
    
    mEvent->SetVertex(myCurrentPicoEvent->GetVertexPos());
    mEvent->SetRunNumber(myCurrentPicoEvent->GetRunID());
    mEvent->SetRefMult(myCurrentPicoEvent->GetRefMult());
    mEvent->SetZdcAdc0((unsigned short)myCurrentPicoEvent->GetZdcTriggerDetector().adc(0));
    mEvent->SetMagField(myCurrentPicoEvent->GetMagneticField());

    mEvent->SetNglobalTracks(myCurrentPicoEvent->GetNglobalTracks());
    mEvent->SetTofMult(myCurrentPicoEvent->GetTofMult());
    mEvent->SetEtaSymTpc(mFlowAnaMaker->getFlowAnalysisMakerEtaSymTpc_Corrected());
    
    if(mFlowAnaMaker) 
    {
        if(mFlowAnaMaker->getFlowAnalysisMakerEventCutPassFailFlag()) 
        {
            mFlowMakerPassFailFlag = mFlowAnaMaker->getFlowAnalysisMakerEventCutPassFailFlag();
            Float_t reactionPlane = mFlowAnaMaker->getPsi(1,1); 
            Float_t subPsiA = mFlowAnaMaker->getPsiSub(2,1);
            Float_t subPsiB = mFlowAnaMaker->getPsiSub(3,1);
            mEvent->SetReactionPlane(reactionPlane);
            mEvent->SetReactionPlaneSubeventA(subPsiA);
            mEvent->SetReactionPlaneSubeventB(subPsiB);
        } 
        else 
        {
            mFlowMakerPassFailFlag = mFlowAnaMaker->getFlowAnalysisMakerEventCutPassFailFlag();
            mEvent->SetReactionPlane(-999.);
            mEvent->SetReactionPlaneSubeventA(-999.);
            mEvent->SetReactionPlaneSubeventB(-999.);
        }
    }
    
    
    StProtonDstTrack *track = 0;

    TClonesArray *tracks = myCurrentPicoEvent->PrimaryTracks();
    StProtonDstPicoTrack *picoTrack;
    int nPicoTracks = tracks->GetEntries();

    int nTracks = 0;

    for(int j=0; j<nPicoTracks; j++) 
    {
        picoTrack = (StProtonDstPicoTrack*) tracks->UncheckedAt(j);

        if(acceptProton(picoTrack)) 
        {
            track = mEvent->AddProtonTrack();
            
            track->SetCharge(picoTrack->GetCharge());
            track->SetNHits(picoTrack->GetNhits());
            track->SetP(picoTrack->P().x(),picoTrack->P().y(),picoTrack->P().z());
            track->SetTopologyMap(0,picoTrack->GetTopologyMap().data(0));
            track->SetTopologyMap(1,picoTrack->GetTopologyMap().data(1));
            track->SetPidPiPlus(picoTrack->GetPidPiPlus()); 
            track->SetPidPiMinus(picoTrack->GetPidPiMinus());
            track->SetPidKaonPlus(picoTrack->GetPidKaonPlus());
            track->SetPidKaonMinus(picoTrack->GetPidKaonMinus());
            track->SetPidProton(picoTrack->GetPidProton());
            track->SetPidAntiProton(picoTrack->GetPidAntiProton());
            track->SetPidElectron(picoTrack->GetPidElectron());
            track->SetPidPositron(picoTrack->GetPidPositron());
            track->SetDca3d(picoTrack->GetDca3());
            track->SetChi2(picoTrack->GetChi2());
            track->SetDedx(picoTrack->GetDedx());
            track->SetFlag(picoTrack->GetFlag());
            
            track->SetDca3dGlobal(picoTrack->GetDcaGlobal3());
                
            nTracks++;
        }
    }

    if(nTracks>0)
        nBytes += mTree->Fill();

    nEventsPassed++;
    mEvent->Clear();

    return kStOK;
}

void StProtonDstMaker::Clear(Option_t *opt) //why the option if it is not used? - JJ
{
    StMaker::Clear();
}

Int_t StProtonDstMaker::Finish() 
{
    mFile->Write();  
    mFile->Close();

    std::cout << "StStProtonDstMaker::Finish()" << std::endl << std::endl;
    std::cout << "\t  nEventsPassed: " << nEventsPassed << " events." << std::endl;
    std::cout << "\t  nEventsFailed: " << nEventsFailed << " events." << std::endl;
    std::cout << "\t  nEventsFailedDueToFlowFlagCut: " << nEventsFailedDueToFlowFlagCut << " events." << std::endl;
    
    return kStOK;
}

bool StProtonDstMaker::accept(StProtonDstPicoEvent *picoEvent) //why is this? - JJ
{
    int refMult = picoEvent->GetRefMult();

    bool good = true; 
    double vzmin = 0.;

    float vertexX = picoEvent->GetVertexPos().x(); 
    float vertexY = picoEvent->GetVertexPos().y();
    float vertexZ = picoEvent->GetVertexPos().z();

    if ( !mFlowMakerPassFailFlag ) 
    { 
        nEventsFailedDueToFlowFlagCut++;
        return false;
    }

    if ( fabs(vertexX) < 1e-5 && fabs(vertexY) < 1e-5 && fabs(vertexZ) < 1e-5) 
        return false;
    if ( sqrt(pow(vertexX,2)+pow(vertexY,2)) > 2.2 ) 
        return false; 
    if ( !good ) 
        return false; 
    if ( (vertexZ > 30.) || (vertexZ <= -30.) ) 
        return false;

    return good;
}

bool StProtonDstMaker::acceptPion(StProtonDstPicoEvent* track) 
{
    bool good = track && ( track->GetFlag() > 0 ) && ( track->GetFlag() < 1000) && ( track->GetPt() > 0.1 ) && ( track->GetPt() < 1.5 ) && ( track->GetTopologyMap().numberOfHits(kTpcId) >= 10 ) && ( track->GetDcaGlobal3().mag() < 5.0 );

    if ((good) && (track->GetCharge() > 0)) 
    {
        if( (fabs(track->GetPidPiPlus()) <= 3.4) && (fabs(track->GetPidKaonPlus()) > 1.4) && (fabs(track->GetPidProton()) > 1.4) && (fabs(track->GetPidPositron()) > 1.4)) 
            good = true;
    } 
    else if ((good) && (track->GetCharge() < 0)) 
    {
        if( (fabs(track->GetPidPiMinus()) <= 3.4) && (fabs(track->GetPidKaonMinus()) > 1.4) && (fabs(track->GetPidAntiProton()) > 1.4) && (fabs(track->GetPidElectron()) > 1.4)) 
            good = true;
    } 
    else 
        good = false;
    
    if (good) 
    {
        float TEnergy = sqrt(track->P().mag2()+0.13957*0.13957);
        float rapidity = 0.5*log((TEnergy+track->P().z())/(TEnergy-track->P().z()));

        good = ( fabs(rapidity) <= 1.0);
    }

    return good;
}

bool StProtonDstMaker::acceptKaon(StProtonDstPicoEvent* track) 
{
    bool good = track && ( track->GetFlag() > 0 ) && ( track->GetPt() > 0.1 ) && ( track->GetPt() < 1.0 ) && ( (fabs(track->GetPidPiPlus()) > 2.0 ) || (fabs(track->GetPidPiMinus()) > 2.0) )  && ( (fabs(track->GetPidKaonPlus()) <= 2.0 ) || (fabs(track->GetPidKaonMinus()) <= 2.0) )  && ( (fabs(track->GetPidProton()) > 2.0 ) || (fabs(track->GetPidAntiProton()) > 2.0) )  && ( (fabs(track->GetPidElectron()) > 2.0 ) || (fabs(track->GetPidPositron()) > 2.0) )  && ( track->GetTopologyMap().numberOfHits(kTpcId) >= 10 ) && ( track->GetDca3().perp() < 3.0 );

    if(good) 
    {
        float TEnergy = sqrt(track->P().mag2()+0.49368*0.49368);
        float rapidity = 0.5*log((TEnergy+track->P().z())/(TEnergy-track->P().z()));

        good = ( fabs(rapidity) <= 1.0);
    }

    return good;
}

bool StProtonDstMaker::acceptProton(StProtonDstPicoEvent* track) 
{
    bool good = track && ( track->GetFlag() > 0 ) && ( track->GetPt() > 0.1 ) && ( track->GetPt() < 1.0 ) && ( (fabs(track->GetPidPiPlus()) > 2.0 ) || (fabs(track->GetPidPiMinus()) > 2.0) )  && ( (fabs(track->GetPidKaonPlus()) > 2.0 ) || (fabs(track->GetPidKaonMinus()) > 2.0) )  && ( (fabs(track->GetPidProton()) <= 2.0 ) || (fabs(track->GetPidAntiProton()) > 2.0) )  && ( (fabs(track->GetPidElectron()) > 2.0 ) || (fabs(track->GetPidPositron()) > 2.0) )  && ( track->GetTopologyMap().numberOfHits(kTpcId) >= 10 ) && ( track->GetDca3().perp() < 3.0 ); 

    if(good) 
    {
        float TEnergy = sqrt(track->P().mag2()+0.938272*0.938272);
        float rapidity = 0.5*log((TEnergy+track->P().z())/(TEnergy-track->P().z()));

        good = ( fabs(rapidity) <= 1.0);
    }

    return good;
}

bool StProtonDstMaker::acceptHiPt(StProtonDstPicoEvent* track) 
{
    bool good = track && ( track->GetFlag() > 0 );
    float pt = sqrt( (track->P().x())*(track->P().x()) + (track->P().y())*(track->P().y()) );

    if ( good ) 
        good = ( pt >= 1.0 );
    
    if(good) 
    {
        float eta = 0.5*log( ( track->P().mag() - track->P().z() ) / ( track->P().mag() + track->P().z() ) );

        good = ( fabs(eta) <= 1.0);
    }
    
    return good;
}

//NOTE:  Bad runs should be removed using StRefMultCorr earlier.
//We will not use this in my analysis.
bool StProtonDstMaker::CheckId(int runnr) // well maybe I should remove it then... - JJ
{
    Int_t nBadRuns=226;
    Int_t badList[226]=
	{
	    4017062,4017063,4017064,4017065,4018028,4018029,4019011,4019014,4019018,
	    4019023,4019031,4019036,4019038,4020015,4020016,4020025,4020026,4020031,
	    4020036,4020037,4020038,4020060,4020069,4020072,4020073,4020076,4020077,
	    4020078,4020081,4020082,4020084,4021007,4021009,4021011,4021012,4021014,
	    4021015,4021016,4021017,4021020,4021022,4022047,4022052,4022054,4022055,
	    4022056,4022058,4022059,4022061,4022062,4022065,4022067,4022069,4022071,
	    4022072,4022073,4022075,4022077,4022079,4022085,4022088,4022090,4022091,
	    4022092,4022093,4022094,4022096,4022097,4022098,4022099,4022100,4022101,
	    4023067,4025005,4025016,4027027,4027028,4027035,4027040,4027041,4027042,
	    4028008,4028012,4028022,4028037,4028045,4028046,4028047,4028048,4028050,
	    4028051,4029014,4032032,4033015,4034030,4034032,4034033,4035022,4035026,
	    4037016,4037017,4037018,4037025,4038034,4040004,4040005,4040006,4040009,
	    4040026,4041005,4041006,4041035,4044031,4045006,4047044,4047045,4047046,
	    4048001,4048002,4048004,4048005,4048006,4049002,4049003,4049004,4049005,
	    4049008,4051002,4054012,4054013,4054014,4054015,4054016,4054021,4054022,
	    4054029,4054030,4054031,4054032,4054033,4054036,4054037,4054038,4054039,
	    4054041,4054042,4055012,4055013,4056003,4056008,4056009,4056010,4056011,
	    4056012,4056018,4056020,4056027,4056033,4059012,4059024,4059025,4059026,
	    4060039,4060057,4062012,4062054,4062056,4062064,4065013,4065015,4065058,
	    4065061,4065064,4066007,4066047,4066052,4066057,4066058,4068022,4068023,
	    4070049,4070050,4070051,4070052,4070053,4070054,4070055,4072006,4072007,
	    4072035,4072036,4072037,4072041,4072042,4072053,4073046,4074012,4074020,
	    4074022,4074039,4074040,4074052,4076005,4076008,4076011,4077061,4077062,
	    4078001,4078012,4078052,4078053,4079002,4079003,4079028,4079034,4080028,
	    4080030,4080031,4080080,4080085,4080086,4080087,4080089,4081021,4081111,
	    4081112
	}; //alright, you got me this time, I'm not changing this to a one-liner - JJ
    
    for(int i=0;i<nBadRuns;i++)
	    if(runnr == badList[i])
	        return false;
	
    return true;
}
#include "StProtonDstHbtReader.h"

#include "StPhysicalHelixD.hh"
#include "SystemOfUnits.h"
#include "StMemoryInfo.hh"
#include "StHbtMaker/Infrastructure/StExceptions.hh"
#include "StHbtMaker/Infrastructure/StHbtTrackCollection.hh"
#include "StHbtVector.hh"

#include "TVector3.h"
#include "TString.h"

#include <algorithm>
#include <math.h>
#include <typeinfo>

#include "StProtonDstEvent.h"
#include "StProtonDstTrack.h"

ClassImp(StProtonDstHbtReader)

#if !(ST_NO_NAMESPACES)
    using namespace units;
#endif

using std::random_shuffle;

StProtonDstHbtReader::StProtonDstHbtReader(StHbtIOMode mode, StIOMaker* io, const char* dirName, const char* fileName, const char* filter, int maxFiles) : mIOMaker(io), mIOMode(mode), mMaxFiles(maxFiles), mDebug(0), mCurrentFile(0), mTTree(0) 
{
    if (mDebug) 
        cout << "StProtonDstHbtReader::StProtonDstHbtReader(...)"<< endl;

    fRPdistribution = new TH1D("fRPdistribution","Reaction plane distribution",720,-2.*TMath::Pi(),2.*TMath::Pi());

    mDir = dirName;
    mFile = fileName;
    mFilter = filter;
    mReaderStatus = 0;  // "good"
    mEvent = new StProtonDstEvent();
    if (mDebug) 
        cout << "StProtonDstHbtReader::StProtonDstHbtReader(...) - leaving"<< endl;
}

//__________________
StProtonDstHbtReader::~StProtonDstHbtReader()
{
    if (mCurrentFile) 
    { 
        mCurrentFile->Close(); 
        delete mCurrentFile; 
        mCurrentFile = 0;
    }
}

//__________________
StHbtString StProtonDstHbtReader::Report()
{
    StHbtString temp = "\n This is the StProtonDstHbtReader\n";
    return temp;
}

//__________________
StHbtEvent* StProtonDstHbtReader::ReturnHbtEvent()
{
    if (mDebug) 
        cout << "StProtonDstHbtReader::ReturnHbtEvent()" << endl;

    try 
    {
        read();
    }
    catch(StExceptionEOF e) 
    {
        e.print();
        mReaderStatus = 2;
        return 0;
    }
    catch(StException e) 
    {
        e.print();
        mReaderStatus = 1;
        return 0;
    }
        
    if (!mHbtEvent) 
        cout << "StProtonDstHbtReader::ReturnHbtEvent() - no mHbtEvent" << endl;

    return mHbtEvent;
}

//__________________
void StProtonDstHbtReader::read()
{
    if (!mTChain) 
    {
        try 
        {
            cout << initRead(mDir.Data(),mFile.Data(),mFilter.Data(),mMaxFiles) << " files to analyse " << endl;
        }
        catch(StException e) 
        {
            e.print();
            return 0;
        }
    }
    
    mEvents = (unsigned int) mTChain->GetEntries();
    if (!mEvents) 
        throw StException("StProtonDstHbtReader::read() - no events to read "); //this should be in iniRead() method; called once and not every event - JJ

    mEvent->Clear();
    int iBytes= mTChain->GetEntry(mEventIndex++);

    if (mEvents < mEventIndex) 
        throw StExceptionEOF("StProtonDstHbtReader::read()");
    if (!iBytes) 
        throw StException("StProtonDstHbtReader::read() - no event ");

	if(mEvent) 
	{	    
	    mHbtEvent->SetEventNumber(1);
	    mHbtEvent->SetRunNumber(mEvent->RunNumber()); //Set the runnumber for the event
	    mHbtEvent->SetCtbMult(0);
	    mHbtEvent->SetZdcAdcEast(0);
	    mHbtEvent->SetZdcAdcWest(0);
	    mHbtEvent->SetNumberOfTpcHits(0);
	    mHbtEvent->SetNumberOfTracks(0);
	    mHbtEvent->SetNumberOfGoodTracks(0);
	    mHbtEvent->SetUncorrectedNumberOfPositivePrimaries(0);
	    mHbtEvent->SetUncorrectedNumberOfNegativePrimaries(0); 
	    mHbtEvent->SetUncorrectedNumberOfPrimaries(0);
	    mHbtEvent->SetReactionPlane(mEvent->ReactionPlane(),0); //setting reaction plane
	    mHbtEvent->SetReactionPlane(mEvent->ReactionPlane(),1); //setting reaction plane
	    mHbtEvent->SetReactionPlaneError(0, 0);
	    mHbtEvent->SetReactionPlaneSubEventDifference(0, 0);
	    mHbtEvent->SetTriggerWord(0);
	    mHbtEvent->SetTriggerActionWord(0);
	    mHbtEvent->SetL3TriggerAlgorithm(0, 0);
	    mHbtEvent->SetUncorrectedNumberOfPrimaries(mEvent->RefMult());  //Set the refMult for the event
	    mHbtEvent->SetPrimVertPos(mEvent->Vertex());  //Set the vertex for the event

        //New Event cut quantities.
        mHbtEvent->SetEtaSymTpc(mEvent->EtaSymTpc());
	    mHbtEvent->SetNglobalTracks(mEvent->NglobalTracks());
	    mHbtEvent->SetTofMult(mEvent->TofMult());
	    mHbtEvent->SetReactionPlaneSubeventA(mEvent->ReactionPlaneSubeventA());
	    mHbtEvent->SetReactionPlaneSubeventB(mEvent->ReactionPlaneSubeventB());

	    StHbtTrackCollection *mTrackCollection = mHbtEvent->TrackCollection();

        if (mDebug)
	        cout << "Reader - The size of the track collection is " << mHbtEvent->TrackCollection()->size() << endl;

	    TClonesArray *tracks = 0;
	    tracks = mEvent->ProtonTracks();           //Change this to Kaon or ProtonTracks for other HBT analyses

	    if (tracks) 
	    {
            mTracks = tracks->GetEntries();
            mTrackIndexArray = shuffleOrder(mTracks);
            
            for (int i = 0; i < mTracks; i++) //To-Do: turn this into for (auto track : tracks) or sth like that??? - JJ
            {
                StProtonDstTrack *track = (StProtonDstTrack*) tracks->UncheckedAt(mTrackIndexArray[i]);
                StHbtTrack* trackCopy = new StHbtTrack;
                trackCopy->SetHiddenInfo(0);
                
                trackCopy->SetCharge(track->Charge());
                trackCopy->SetNHits(track->NHits());
                
                //---- Set dummy values ----//
                
                trackCopy->SetNHitsDedx(0);
                if (track->Charge() < 0) 
                {
                    trackCopy->SetNSigmaElectron(track->PidElectron());
                    trackCopy->SetNSigmaPion(track->PidPiMinus());
                    trackCopy->SetNSigmaKaon(track->PidKaonMinus());
                    trackCopy->SetNSigmaProton(track->PidAntiProton());
                } 
                else if (track->Charge() > 0) 
                {
                    trackCopy->SetNSigmaElectron(track->PidPositron());
                    trackCopy->SetNSigmaPion(track->PidPiPlus());
                    trackCopy->SetNSigmaKaon(track->PidKaonPlus());
                    trackCopy->SetNSigmaProton(track->PidProton());
                }
                
                trackCopy->SetPidProbElectron(0.);
                trackCopy->SetPidProbPion(0.);
                trackCopy->SetPidProbKaon(0.);
                trackCopy->SetPidProbProton(0.);
                trackCopy->SetdEdx(track->Dedx());
                trackCopy->SetDCAxy(track->Dca3d().mag());
                trackCopy->SetDCAz(0.);
                trackCopy->SetDCAxyGlobal(track->Dca3dGlobal().mag());
                trackCopy->SetDCAzGlobal(0.);
                trackCopy->SetChiSquaredXY(track->Chi2());
                trackCopy->SetChiSquaredZ(0.);
                
                //---- Set momentum ----//
            
                float px = track->P().x();
                float py = track->P().y();
                float pz = track->P().z();
                
                StHbtThreeVector v(px,py,pz);
                
                trackCopy->SetP(v);
                trackCopy->SetPt(sqrt(px*px+py*py));
                
                // NEED TO SET HELIX!!
                
                const StThreeVectorD p((double)px,(double)py,(double)pz);
                const StThreeVectorD origin((double)mEvent->Vertex().x(),(double)mEvent->Vertex().y(),(double)mEvent->Vertex().z());
                
                StPhysicalHelixD helix(p,origin,(double)(mEvent->MagField())*kilogauss,(double)(track->Charge()));
                
                trackCopy->SetHelix(helix);
            
                trackCopy->SetTopologyMap(0,track->TopologyMap(0));
                trackCopy->SetTopologyMap(1,track->TopologyMap(1));
                
                mTrackCollection->push_back(trackCopy);

                if (mDebug)
                    cout << "now the size of the track collection is " << mHbtEvent->TrackCollection()->size() << endl;
            }
	    }	    
	}
}

int StProtonDstHbtReader::initRead(const char* dir, const char* file, const char* filter, int mMaxFiles)
{
    mHbtEvent = new StHbtEvent;
    mEventIndex = 0;
    mTChain = new TChain("ProtonDst","ProtonDst");
    int nFiles = 0;
    TString strDirFile = Form("%s%s",dir,file);

    if (mDebug)
        cout << "StProtonDstHbtReader::initReader()" << endl;
    
    if (strlen(file) != 0) // if a filename was given 
    { 
        if ( strstr(file,".lis") || strstr(file,".list") ) // if a file list is specified
        { 
            cout << Form("StProtonDstHbtReader::initReader() list =  %s",file) << endl;
            try 
            {
                nFiles = fillChain(mTChain, strDirFile.Data(), mMaxFiles);
                cout << "StProtonDstHbtReader::InitReader() = "  << strDirFile << endl;
            }
            catch(StException e) 
            {
                throw e;
            }
        }
        else // a single file was specified 
        { 
            mTChain->Add(strDirFile.Data());
            cout<<"StProtonDstHbtReader::InitReader() 2 = "<< (dir+file).c_str()<<endl;
            nFiles++;
        }
    }
    else 
    {
        try 
        {
            nFiles = fillChain(mTChain,dir, filter, mMaxFiles);
        }
        catch(StException e) 
        {
            throw e;
        }
    }  
        
    mTChain->SetBranchAddress("Event",&mEvent); 
    return nFiles;
}


int StProtonDstHbtReader::uninitRead()
{
    if (mEvent) 
        delete mEvent;
    if (mTChain) 
        delete mTChain;
    mEvent = 0;
    mTChain = 0;
    return 0;
}

int StProtonDstHbtReader::fillChain(TChain* chain, const char* fileList, const int maxFiles) 
{
    int count=0;
    TString fileName;
    ifstream* inputStream = new ifstream;
    cout << "StProtonDstHbtReader::fillChain() filelist = " << fileList << endl;
    
    inputStream->open(fileList);
    if (!(inputStream->is_open())) 
        throw StException("StProtonDstHbtReader::fillChain(string dir) - can not open directory");
    
    if (mDebug>1) 
        cout << " StProtonDstHbtReader::fillChain(...)- inputStream->good() : " << inputStream->good() << endl;

    while (inputStream >> fileName)
    {
        if(fileName.Contains(".root")) 
        {
            chain->Add(temp);
            ++count;
        }
    }   

    delete inputStream;
    if (mDebug) 
        cout << "StProtonDstHbtReader::(string dir)(string dir) - Added " << count << " files to the chain" << endl;
    return count;
}

int StProtonDstHbtReader::fillChain(TChain* chain, const char* dir, const char* filter, const int maxFiles) //as of now this is beyond my comprehension, I need coffee - JJ
{
    // read directory
    void *pDir = gSystem->OpenDirectory(dir);
    if(!pDir) 
        throw StException("StProtonDstHbtReader::fillChain(string dir) - can not open directory");

    // now find the files that end in the specified searchString
    const char* fileName(0);
    int count(0);
    while((fileName = gSystem->GetDirEntry(pDir)))
    {
        if(strcmp(fileName,".")==0 || strcmp(fileName,"..")==0) 
            continue;
        if(strstr(fileName,filter) ) // found a match
        { 
            char* fullFile = gSystem->ConcatFileName(dir,fileName);
            // add it to the chain
            cout << "StProtonDstHbtReader::fillChain(string dir) - Adding " << fullFile << " to the chain" << endl;
            chain->Add(fullFile);
            delete fullFile;
            ++count;
            if (count>maxFiles) 
                break;
        }   
    }
    cout << "StProtonDstHbtReader::(string dir)(string dir) - Added " << count << " files to the chain" << endl;
    return count;
}

TArrayI StProtonDstHbtReader::shuffleOrder(int arraySize)  //changed the name format and variable language to mach the rest - JJ
{ // also, it is depriceted since c++14 (https://en.cppreference.com/w/cpp/algorithm/random_shuffle)
    TArrayI array;
    array.Set(nr);
    int i=0;
    int test=0;
    int r;
    while (i<nr)
    {
        r=int((double)nr*rand()/(double)RAND_MAX);
        test=0;
        for (int j=0; j<i; j++)
            if (r==array[j]) 
                test=1;
        if (test==1)
            continue;
        else
        {
            array[i] = r;
            i++;
        }
    }
    return array;
}









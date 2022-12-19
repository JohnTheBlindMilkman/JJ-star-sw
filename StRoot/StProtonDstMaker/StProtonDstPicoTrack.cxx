#include "StProtonDstPicoTrack.h"

ClassImp(StProtonDstPicoTrack)

StProtonDstPicoTrack::StProtonDstPicoTrack(double Px, double Py, double Pz) 
{
  fP[0] = Px;
  fP[1] = Py;
  fP[2] = Pz;
  maxInt = 32.;
}

Float_t StProtonDstPicoTrack::GetP() const 
{ 
    float momentum = mPt/::sqrt(1-(tanh(mEta)*tanh(mEta)));
    return momentum; 
}

Float_t StProtonDstPicoTrack::GetPGlobal() const 
{ 
    float momentum = mPtGlobal / ::sqrt(1-(tanh(mEtaGlobal)*tanh(mEtaGlobal)));
    return momentum; 
}

Float_t StProtonDstPicoTrack::GetY() const 
{ 
    float M = 0.139; 
    if (strcmp(mPid, "none") == 0)          
        M = 0.139;
    else if (strcmp(mPid, "pi+") == 0)      
        M = 0.139;
    else if (strcmp(mPid, "pi-") == 0)      
        M = 0.139;
    else if (strcmp(mPid, "pr+") == 0)      
        M = 0.938;
    else if (strcmp(mPid, "pr-") == 0)      
        M = 0.938;
    else if (strcmp(mPid, "k+")  == 0)      
        M = 0.494;
    else if (strcmp(mPid, "k-")  == 0)      
        M = 0.494;
    else if (strcmp(mPid, "d+")  == 0)      
        M = 1.876;
    else if (strcmp(mPid, "d-")  == 0)      
        M = 1.876;
    else if (strcmp(mPid, "e-")  == 0)      
        M = 0.0005;
    else if (strcmp(mPid, "e+")  == 0)      
        M = 0.0005;

    double Pz = ::sqrt(this->GetP()*this->GetP() - mPt*mPt); 
    if (mEta < 0) 
        Pz = -Pz;
        
    double E = ::sqrt(this->GetP()*this->GetP() + M*M);
    float rapidity = 0.5*::log((E + Pz)/(E - Pz));
    return rapidity;
}

void StProtonDstPicoTrack::SetPidPiPlus(Float_t pid)  // I feel like there should be a better way... - JJ
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 

    mPidPiPlus = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidPiMinus(Float_t pid) 
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidPiMinus = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidProton(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidProton = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidKaonMinus(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
    
    mPidKaonMinus = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidKaonPlus(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidKaonPlus = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidAntiProton(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidAntiProton = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidDeuteron(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidDeuteron = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidAntiDeuteron(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidAntiDeuteron = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidElectron(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidElectron = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPidPositron(Float_t pid)  
{
    if (fabs(pid) > maxInt) 
        pid = maxInt; 
        
    mPidPositron = (Int_t)(pid*1000.); 
}

void StProtonDstPicoTrack::SetPid(const Char_t* pid)  //whyyyy - JJ
{ 
    strncpy(mPid, pid, 9);
    mPid[9] = '\0'; 
}
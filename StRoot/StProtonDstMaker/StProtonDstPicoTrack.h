#ifndef StProtonDstPicoTrack_h
#define StProtonDstPicoTrack_h
#include <string.h>
#include <math.h>

#include "Rtypes.h"
#include "StObject.h"
#include "StTrackTopologyMap.h"
#include "StThreeVectorD.hh"
#include "StPhysicalHelixD.hh"

class StProtonDstPicoTrack : public StObject 
{
    public:
        StProtonDstPicoTrack(double Px, double Py, double Pz);
        StProtonDstPicoTrack() { maxInt = 32.;}
        virtual ~StProtonDstPicoTrack() {};

        Float_t GetPidPiPlus() const;
        Float_t GetPidPiMinus() const;
        Float_t GetPidProton() const;
        Float_t GetPidKaonMinus() const;
        Float_t GetPidKaonPlus() const;
        Float_t GetPidAntiProton() const;
        Float_t GetPidDeuteron() const;
        Float_t GetPidAntiDeuteron() const;
        Float_t GetPidElectron() const;
        Float_t GetPidPositron() const;

        const Char_t* GetPid() const;
        Float_t GetPhi() const;
        Float_t GetPhiGlobal() const;
        Float_t GetEta() const;
        Float_t GetEtaGlobal() const;
        Float_t GetZFirstPoint() const;
        Float_t GetZLastPoint() const;
        Float_t GetDedx() const;
        Float_t GetPt() const;
        Float_t GetPtGlobal() const;
        Float_t GetP() const;
        Float_t GetPGlobal() const;
        Float_t GetY() const;
        Short_t GetCharge() const;
        Float_t GetDca() const;
        StThreeVectorD GetDca3() const;
        Float_t GetDcaSigned() const;
        Float_t GetDcaGlobal() const;
        Float_t GetChi2() const;
        Int_t GetFitPts() const;  // contains fit points in TPC xor FTPC only (SVT and/or SSD hits subtracted)
        Int_t GetMaxPts() const;  // contains possible hits in TPC xor FTPC only (SVT and/or SSD hits subtracted)
        Int_t GetNhits() const;  // contains ALL hits on the track (TPC + SVT + SSD + FTPC east + FTPC west)
        Int_t GetNdedxPts() const;
        Float_t GetTrackLength() const;
        Int_t GetMostLikelihoodPID() const; 
        Float_t GetMostLikelihoodProb() const; 
        Int_t GetExtrapTag() const;
        Float_t GetElectronPositronProb() const;
        Float_t GetPionPlusMinusProb() const; 
        Float_t GetKaonPlusMinusProb() const; 
        Float_t GetProtonPbarProb() const;
        StThreeVectorD GetDcaGlobal3() const; 
        const StTrackTopologyMap& GetTopologyMap() const;
        Int_t  GetFlag() const;
        Int_t  GetIndex2Global() const;
        Float_t GetZFirstPointX() const;
        Float_t GetZFirstPointY() const;
        StPhysicalHelixD GetHelix();

        Float_t GetMsquared() const;
        void SetMsquared(Float_t);
        
        void SetPidPiPlus(Float_t);
        void SetPidPiMinus(Float_t);
        void SetPidProton(Float_t);
        void SetPidKaonMinus(Float_t);
        void SetPidKaonPlus(Float_t);
        void SetPidAntiProton(Float_t);
        void SetPidDeuteron(Float_t);
        void SetPidAntiDeuteron(Float_t);
        void SetPidElectron(Float_t);
        void SetPidPositron(Float_t);
        void SetPid(const Char_t*);
        void SetPhi(Float_t);
        void SetPhiGlobal(Float_t);
        void SetEta(Float_t);
        void SetEtaGlobal(Float_t);
        void SetZFirstPoint(Float_t);
        void SetZLastPoint(Float_t);
        void SetDedx(Float_t);
        void SetPt(Float_t);
        void SetPtGlobal(Float_t);
        void SetCharge(Short_t);
        void SetDca(Float_t);
        void SetDca3(StThreeVectorD);
        void SetDcaSigned(Float_t);
        void SetDcaGlobal(Float_t);
        void SetChi2(Float_t);
        void SetFitPts(Int_t);
        void SetMaxPts(Int_t);
        void SetNhits(Int_t);
        void SetNdedxPts(Int_t);
        void SetTrackLength(Float_t);
        void SetMostLikelihoodPID(Int_t); 
        void SetMostLikelihoodProb(Float_t); 
        void SetExtrapTag(Int_t); 
        void SetElectronPositronProb(Float_t);
        void SetPionPlusMinusProb(Float_t);
        void SetKaonPlusMinusProb(Float_t);
        void SetProtonPbarProb(Float_t);
        void SetDcaGlobal3(StThreeVectorD gdca3);
        void SetTopologyMap(StTrackTopologyMap map);

        void SetFlag(Int_t);
        void SetIndex2Global(Int_t);
        void SetZFirstPointX(Float_t);
        void SetZFirstPointY(Float_t);
        void SetHelix(StPhysicalHelixD);

        void SetP(double Px, double Py, double Pz) { fP[0] = Px; fP[1] = Py; fP[2] = Pz; }
        void SetP(StThreeVectorD v) { fP = v; }
        StThreeVectorD& P() { return fP; }
    
    private:
        StThreeVectorD fP;
        Float_t mMsquared;
        
        Int_t   mFlag;
        Int_t   mIndex2Global;
        Float_t mZFirstPointX;
        Float_t mZFirstPointY;
        StPhysicalHelixD mHelix;
        
        Int_t   mPidPiPlus;
        Int_t   mPidPiMinus;
        Int_t   mPidProton;
        Int_t   mPidKaonPlus;
        Int_t   mPidKaonMinus;
        Int_t   mPidAntiProton;
        Int_t   mPidDeuteron;
        Int_t   mPidAntiDeuteron;
        Int_t   mPidElectron;
        Int_t   mPidPositron;
        Char_t  mPid[10];
        Float_t mPhi;
        Float_t mPhiGlobal;
        Float_t mEta;
        Float_t mEtaGlobal;
        Float_t mZFirstPoint;
        Float_t mZLastPoint;
        Float_t mDedx;
        Float_t mPt;
        Float_t mPtGlobal;
        Short_t mCharge;
        Float_t mDca;
        Float_t mDcaSigned;
        Float_t mDcaGlobal;
        Float_t mChi2;
        Int_t   mFitPts; // contains fit points in TPC xor FTPC only (SVT and/or SSD hits subtracted)
        Int_t   mMaxPts; // contains possible hits in TPC xor FTPC only (SVT and/or SSD hits subtracted)
        Int_t   mNhits;  // contains ALL hits on the track (TPC + SVT + SSD + FTPC east + FTPC west)
        Int_t   mNdedxPts;
        Float_t mTrackLength;
        Float_t maxInt;  //declared globally in StProtonDstPicoTrack.cxx
        Int_t   mMostLikelihoodPID;
        Float_t mMostLikelihoodProb;
        Int_t   mExtrapTag; //merging area tag.
        Float_t mElectronPositronProb;
        Float_t mPionPlusMinusProb;  
        Float_t mKaonPlusMinusProb;  
        Float_t mProtonPbarProb;
        StThreeVectorD mDcaGlobal3;  
        StThreeVectorD mDca3;
        StTrackTopologyMap mTopology; //Not set in FillFromMuDst but needed for Hbt
  				//SO SET IT TOO LIKE IN FillFromPicoEvent()

    ClassDef(StProtonDstPicoTrack,2)
};
inline Float_t StProtonDstPicoTrack::GetMsquared() const { return mMsquared; }
inline void StProtonDstPicoTrack::SetMsquared(Float_t ms) { mMsquared = ms; }

//Define the Get functions for the StProtonDstPicoTrack
inline Float_t StProtonDstPicoTrack::GetPidPiPlus() const { return mPidPiPlus/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidPiMinus() const { return mPidPiMinus/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidProton() const { return mPidProton/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidKaonMinus() const { return mPidKaonMinus/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidKaonPlus() const { return mPidKaonPlus/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidAntiProton() const { return mPidAntiProton/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidDeuteron() const { return mPidDeuteron/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidAntiDeuteron() const { return mPidAntiDeuteron/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidElectron() const { return mPidElectron/1000.; }
inline Float_t StProtonDstPicoTrack::GetPidPositron() const { return mPidPositron/1000.; }
inline const Char_t* StProtonDstPicoTrack::GetPid() const { return mPid; }
inline Float_t StProtonDstPicoTrack::GetPhi() const { return mPhi; }   
inline Float_t StProtonDstPicoTrack::GetPhiGlobal() const { return mPhiGlobal; }   
inline Float_t StProtonDstPicoTrack::GetEta() const { return mEta; }     
inline Float_t StProtonDstPicoTrack::GetEtaGlobal() const { return mEtaGlobal; }     
inline Float_t StProtonDstPicoTrack::GetZFirstPoint() const { return mZFirstPoint; }     
inline Float_t StProtonDstPicoTrack::GetZLastPoint() const { return mZLastPoint; }     
inline Float_t StProtonDstPicoTrack::GetDedx() const { return mDedx; }     
inline Float_t StProtonDstPicoTrack::GetPt() const { return mPt; }
inline Float_t StProtonDstPicoTrack::GetPtGlobal() const { return mPtGlobal; }
inline Short_t StProtonDstPicoTrack::GetCharge() const { return mCharge; }   
inline Float_t StProtonDstPicoTrack::GetDca() const { return mDca; }
inline Float_t StProtonDstPicoTrack::GetDcaSigned() const { return mDcaSigned; }
inline Float_t StProtonDstPicoTrack::GetDcaGlobal() const { return mDcaGlobal; }
inline Float_t StProtonDstPicoTrack::GetChi2() const { return mChi2; } 
inline Int_t StProtonDstPicoTrack::GetFitPts() const { return mFitPts; }  
inline Int_t StProtonDstPicoTrack::GetMaxPts() const { return mMaxPts; }  
inline Int_t StProtonDstPicoTrack::GetNhits() const { return mNhits; }
inline Int_t StProtonDstPicoTrack::GetNdedxPts() const { return mNdedxPts; }  
inline Float_t StProtonDstPicoTrack::GetTrackLength() const { return mTrackLength; }  
inline Int_t StProtonDstPicoTrack::GetMostLikelihoodPID() const { return mMostLikelihoodPID; } 
inline Float_t StProtonDstPicoTrack::GetMostLikelihoodProb() const { return mMostLikelihoodProb; } 
inline Int_t StProtonDstPicoTrack::GetExtrapTag() const { return mExtrapTag; } 
inline Float_t StProtonDstPicoTrack::GetElectronPositronProb() const { return mElectronPositronProb; }
inline Float_t StProtonDstPicoTrack::GetPionPlusMinusProb() const { return mPionPlusMinusProb; }
inline Float_t StProtonDstPicoTrack::GetKaonPlusMinusProb() const { return mKaonPlusMinusProb; }
inline Float_t StProtonDstPicoTrack::GetProtonPbarProb() const { return mProtonPbarProb; }
inline StThreeVectorD StProtonDstPicoTrack::GetDcaGlobal3() const { return mDcaGlobal3; }
inline StThreeVectorD StProtonDstPicoTrack::GetDca3() const { return mDca3; }
inline const StTrackTopologyMap& StProtonDstPicoTrack::GetTopologyMap() const { return mTopology; }

inline Int_t StProtonDstPicoTrack::GetFlag() const { return mFlag; }

inline Int_t StProtonDstPicoTrack::GetIndex2Global() const { return mIndex2Global; }  

inline Float_t StProtonDstPicoTrack::GetZFirstPointX() const { return mZFirstPointX; } 

inline Float_t StProtonDstPicoTrack::GetZFirstPointY() const { return mZFirstPointY; } 

inline StPhysicalHelixD StProtonDstPicoTrack::GetHelix() { return mHelix; }

inline void StProtonDstPicoTrack::SetMostLikelihoodPID(Int_t val) { mMostLikelihoodPID=val; } 

inline void StProtonDstPicoTrack::SetMostLikelihoodProb(Float_t val) { mMostLikelihoodProb=val; } 

inline void StProtonDstPicoTrack::SetExtrapTag(Int_t val) { mExtrapTag=val; } 

inline void StProtonDstPicoTrack::SetElectronPositronProb(Float_t val) { mElectronPositronProb = val; }

inline void StProtonDstPicoTrack::SetPionPlusMinusProb(Float_t val) { mPionPlusMinusProb = val; }

inline void StProtonDstPicoTrack::SetKaonPlusMinusProb(Float_t val) { mKaonPlusMinusProb = val; }

inline void StProtonDstPicoTrack::SetProtonPbarProb(Float_t val) { mProtonPbarProb = val; }

inline void StProtonDstPicoTrack::SetPhi(Float_t phi)        { mPhi = phi; }      

inline void StProtonDstPicoTrack::SetPhiGlobal(Float_t gphi) { mPhiGlobal = gphi; }   

inline void StProtonDstPicoTrack::SetEta(Float_t eta)        { mEta = eta; }       

inline void StProtonDstPicoTrack::SetEtaGlobal(Float_t geta) { mEtaGlobal = geta; } 

inline void StProtonDstPicoTrack::SetZFirstPoint(Float_t zFirst) { mZFirstPoint = zFirst; } 

inline void StProtonDstPicoTrack::SetZLastPoint(Float_t zLast) { mZLastPoint = zLast; } 

inline void StProtonDstPicoTrack::SetDedx(Float_t dedx)      { mDedx = dedx; }       

inline void StProtonDstPicoTrack::SetPt(Float_t pt)          { mPt = pt; }              

inline void StProtonDstPicoTrack::SetPtGlobal(Float_t gpt)   { mPtGlobal = gpt; }

inline void StProtonDstPicoTrack::SetCharge(Short_t charge)  { mCharge = charge; }     

inline void StProtonDstPicoTrack::SetDca(Float_t dca)        { mDca = dca; }

inline void StProtonDstPicoTrack::SetDcaSigned(Float_t sdca) { mDcaSigned = sdca; }

inline void StProtonDstPicoTrack::SetDcaGlobal(Float_t gdca) { mDcaGlobal = gdca; }

inline void StProtonDstPicoTrack::SetChi2(Float_t chi2)      { mChi2 = chi2; }

inline void StProtonDstPicoTrack::SetFitPts(Int_t fitPts)    { mFitPts = fitPts; }

inline void StProtonDstPicoTrack::SetMaxPts(Int_t maxPts)    { mMaxPts = maxPts; }

inline void StProtonDstPicoTrack::SetNhits(Int_t nhits)      { mNhits = nhits; }

inline void StProtonDstPicoTrack::SetNdedxPts(Int_t ndedxPts) { mNdedxPts = ndedxPts; }

inline void StProtonDstPicoTrack::SetTrackLength(Float_t tl) { mTrackLength = tl; }

inline void StProtonDstPicoTrack::SetDcaGlobal3(StThreeVectorD gdca3) { mDcaGlobal3 = gdca3; }

inline void StProtonDstPicoTrack::SetDca3(StThreeVectorD pdca3) { mDca3 = pdca3; }

inline void StProtonDstPicoTrack::SetFlag(Int_t flag) { mFlag = flag; }

inline void StProtonDstPicoTrack::SetIndex2Global(Int_t i2g) { mIndex2Global = i2g; }  

inline void StProtonDstPicoTrack::SetZFirstPointX(Float_t zFirstX) { mZFirstPointX = zFirstX; } 

inline void StProtonDstPicoTrack::SetZFirstPointY(Float_t zFirstY) { mZFirstPointY = zFirstY; } 

inline void StProtonDstPicoTrack::SetHelix(StPhysicalHelixD h) { mHelix = h; }

//NOTE:  This is different than in the Track class used for making PionDst's.
inline void StProtonDstPicoTrack::SetTopologyMap(StTrackTopologyMap map) { mTopology = map; }

#endif

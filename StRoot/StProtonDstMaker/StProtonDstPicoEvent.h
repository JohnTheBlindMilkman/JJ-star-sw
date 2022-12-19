#ifndef StProtonDstPicoEvent_h
#define StProtonDstPicoEvent_h

#include "TObject.h"
#include "TArrayI.h"
#include "TClonesArray.h"

#include "StThreeVectorF.hh"
#include "StZdcTriggerDetector.h"
#include "StBbcTriggerDetector.h"
#include "StMuEvent.h"
#include "StProtonDstPicoTrack.h"

class StProtonDstPicoEvent : public TObject 
{
    public:
        StProtonDstPicoEvent();
        ~StProtonDstPicoEvent();

        //Set Functions for StProtonDstPicoEvent variables
        void SetEventID(const Int_t&);
        void SetRunID(const Int_t&);
        void SetCenterOfMassEnergy(const Double_t&);
        void SetMagneticField(const Double_t&);
        void SetBeamMassNumberEast(const Short_t&);
        void SetBeamMassNumberWest(const Short_t&);
        void SetOrigMult(const UInt_t&);
        void SetL0TriggerWord(const UInt_t&);
        void SetUncorrPosMult(const UInt_t&);
        void SetUncorrNegMult(const UInt_t&);
        void SetMultEta(const UInt_t&);
        void SetVertexPos(const StThreeVectorF&);
        void SetCTB(const Float_t ctb);
        void SetZDCe(const Float_t zdce);
        void SetZDCw(const Float_t zdcw);
        void SetNumberOfTracksInOriginalPrimaryTrackArray(Int_t numMuTracks);
        void SetRefMult(const UInt_t&);
        void SetZdcTriggerDetector(const StZdcTriggerDetector&);
        void SetBbcTriggerDetector(const StBbcTriggerDetector&);
        void SetTofMult(const UInt_t&);
        void SetNglobalTracks(Int_t numGlobalTracks);
        
        //Get Functions for StProtonDstPicoEvent variables
        Int_t GetEventID() const;
        Int_t GetRunID() const;
        Double_t GetCenterOfMassEnergy() const;
        Double_t GetMagneticField() const;
        Double_t GetZdcCoincidenceRate() const; //New. Needed for Y10_200gev StRefMultCorr centralities.
        Short_t GetBeamMassNumberEast() const;
        Short_t GetBeamMassNumberWest() const;
        UInt_t GetOrigMult() const;
        UInt_t GetL0TriggerWord() const;
        UInt_t GetUncorrNegMult() const;
        UInt_t GetUncorrPosMult() const;
        UInt_t GetMultEta() const;
        StThreeVectorF GetVertexPos() const;
        Float_t GetCTB() const;
        Float_t GetZDCe() const;
        Float_t GetZDCw() const;
        Int_t GetNumberOfTracksInOriginalPrimaryTrackArray() const;
        Int_t GetNglobalTracks() const;
        UInt_t GetRefMult() const;
        UInt_t GetTofMult() const;
        StZdcTriggerDetector GetZdcTriggerDetector() const;
        StBbcTriggerDetector GetBbcTriggerDetector() const;
        
        StProtonDstPicoTrack* AddPrimaryTrack();
        TClonesArray* PrimaryTracks() { return fPrimaryTracks; }
        
        void Clear(const Option_t* option="");
    
    private:
        Int_t mRunID;                                    // ID of the run
        Double_t mCenterOfMassEnergy;                       // 
        Double_t mMagneticField;                            // 
        Double_t mZdcCoincidenceRate;   //New. Needed for Y10_200gev StRefMultCorr centralities.
        UInt_t mUncorrNegMult;                            // number of h-
        UInt_t mUncorrPosMult;                            // number of h+
        UInt_t mMultEta;                                  // number of tracks
        Int_t  mEventID;                                  // ID of the event
        StThreeVectorF mVertexPos;                                // primary vertex position
        UInt_t mL0TriggerWord;                            // L0 trigger word
        Short_t mBeamMassNumberEast;                       //
        Short_t mBeamMassNumberWest;                       //
        Float_t mCTB;                                      // CTB value sum
        Float_t mZDCe;                                     // ZDC east
        Float_t mZDCw;                                     // ZDC west
        UInt_t mOrigMult;                                 // number of tracks
        Int_t mNumberOfTracksInOriginalPrimaryTrackArray; //number of tracks in orignial MuTrack Array from mudst
        UInt_t  mRefMult; //refmult like usual for HBT
        UInt_t  mTofMult;
        Int_t mNglobalTracks;
        StZdcTriggerDetector mZdcTrigDet; //zdc trigger detector object
        StBbcTriggerDetector mBbcTrigDet; //bbc trigger detector object
        
        TClonesArray *fPrimaryTracks;  //Array of primary"PicoTracks" for flow
        unsigned short mNPrimaryTracks;

    ClassDef(StProtonDstPicoEvent,1)
};

//Define the Get functions
inline Int_t StProtonDstPicoEvent::GetEventID() const { return mEventID; }

inline Int_t StProtonDstPicoEvent::GetRunID() const { return mRunID; }

inline Double_t StProtonDstPicoEvent::GetCenterOfMassEnergy() const { return mCenterOfMassEnergy; }

inline Double_t StProtonDstPicoEvent::GetMagneticField() const { return mMagneticField; }

inline Double_t StProtonDstPicoEvent::GetZdcCoincidenceRate() const { return mZdcCoincidenceRate; } //New. Needed for Y10_200gev StRefMultCorr centralities.

inline Short_t StProtonDstPicoEvent::GetBeamMassNumberEast() const { return mBeamMassNumberEast; }

inline Short_t StProtonDstPicoEvent::GetBeamMassNumberWest() const { return mBeamMassNumberWest; }

inline UInt_t StProtonDstPicoEvent::GetOrigMult() const { return mOrigMult; }

inline UInt_t StProtonDstPicoEvent::GetL0TriggerWord() const { return mL0TriggerWord; }

inline UInt_t StProtonDstPicoEvent::GetUncorrNegMult() const { return mUncorrNegMult; }

inline UInt_t StProtonDstPicoEvent::GetUncorrPosMult() const { return mUncorrPosMult; }

inline UInt_t StProtonDstPicoEvent::GetMultEta() const { return mMultEta; }

//inline UInt_t StProtonDstPicoEvent::GetFlowEventMult() const { return pTrackCollection->size(); }

//inline UInt_t StProtonDstPicoEvent::GetCentrality() const { return mCentrality; }

inline StThreeVectorF StProtonDstPicoEvent::GetVertexPos() const { return mVertexPos; }

inline Float_t  StProtonDstPicoEvent::GetCTB() const { return mCTB; }

inline Float_t  StProtonDstPicoEvent::GetZDCe() const { return mZDCe; }

inline Float_t  StProtonDstPicoEvent::GetZDCw() const { return mZDCw; }  

//inline Float_t  StProtonDstPicoEvent::ZDCSMD(int eastwest,int verthori,int strip) const {return mZDCSMD[eastwest][verthori][strip-1];}

inline Int_t StProtonDstPicoEvent::GetNumberOfTracksInOriginalPrimaryTrackArray() const {
  return mNumberOfTracksInOriginalPrimaryTrackArray; }
  
//     inline Int_t GetTriggerValue() { return TriggerValue; }

//Define the Set functions (Set Centrality was defined elsewhere, in StFM.cxx)
inline void StProtonDstPicoEvent::SetEventID(const Int_t& id) { mEventID = id; }

inline void StProtonDstPicoEvent::SetRunID(const Int_t& id) { mRunID = id; }

inline void StProtonDstPicoEvent::SetMagneticField(const Double_t& mf) { mMagneticField = mf; }

inline void StProtonDstPicoEvent::SetZdcCoincidenceRate(const Double_t& mzdccr) { mZdcCoincidenceRate = mzdccr; } //New. Needed for Y10_200gev StRefMultCorr centralities.

inline void StProtonDstPicoEvent::SetCenterOfMassEnergy(const Double_t& cms) { mCenterOfMassEnergy = cms; }

inline void StProtonDstPicoEvent::SetBeamMassNumberEast(const Short_t& bme) { mBeamMassNumberEast = bme; }

inline void StProtonDstPicoEvent::SetBeamMassNumberWest(const Short_t& bmw) { mBeamMassNumberWest = bmw; }

inline void StProtonDstPicoEvent::SetOrigMult(const UInt_t& tracks) {
  mOrigMult = tracks; }

inline void StProtonDstPicoEvent::SetL0TriggerWord(const UInt_t& trigger) {
  mL0TriggerWord = trigger; }

inline void StProtonDstPicoEvent::SetUncorrNegMult(const UInt_t& negtracks) {
  mUncorrNegMult = negtracks; }

inline void StProtonDstPicoEvent::SetUncorrPosMult(const UInt_t& postracks) {
  mUncorrPosMult = postracks; }

inline void StProtonDstPicoEvent::SetMultEta(const UInt_t& goodtracks) {
  mMultEta = goodtracks; }

inline void StProtonDstPicoEvent::SetVertexPos(const StThreeVectorF& vertexPos) {
  mVertexPos = vertexPos; }

inline void StProtonDstPicoEvent::SetCTB(const Float_t ctb) { mCTB = ctb; }

inline void StProtonDstPicoEvent::SetZDCe(const Float_t zdce) { mZDCe = zdce; }

inline void StProtonDstPicoEvent::SetZDCw(const Float_t zdcw) { mZDCw = zdcw; }

inline void StProtonDstPicoEvent::SetNumberOfTracksInOriginalPrimaryTrackArray(const Int_t numMuTracks) {
  mNumberOfTracksInOriginalPrimaryTrackArray = numMuTracks; }

//     inline void SetTriggerValue(int tv) { TriggerValue = tv; }

//inline void StProtonDstPicoEvent::SetZDCSMD(int eastwest,int verthori,int strip,const Float_t zdcsmd) {
//  mZDCSMD[eastwest][verthori][strip-1] = (zdcsmd >0.)? zdcsmd:0.;}

inline void StProtonDstPicoEvent::SetZdcTriggerDetector(const StZdcTriggerDetector& zdcpointer) { mZdcTrigDet = zdcpointer; }

inline void StProtonDstPicoEvent::SetBbcTriggerDetector(const StBbcTriggerDetector& bbcpointer) { mBbcTrigDet = bbcpointer; }

inline StZdcTriggerDetector StProtonDstPicoEvent::GetZdcTriggerDetector() const { return mZdcTrigDet; }

inline StBbcTriggerDetector StProtonDstPicoEvent::GetBbcTriggerDetector() const { return mBbcTrigDet; }

inline void StProtonDstPicoEvent::SetRefMult(const UInt_t& rm) { mRefMult = rm; }

inline UInt_t StProtonDstPicoEvent::GetRefMult() const { return mRefMult; }

//For the new cuts on tof mult and nglobal tracks suggested by rosi
inline void StProtonDstPicoEvent::SetNglobalTracks(const Int_t numGlobalTracks) {
  mNglobalTracks = numGlobalTracks; }
  
inline Int_t StProtonDstPicoEvent::GetNglobalTracks() const {
  return mNglobalTracks; }

inline void StProtonDstPicoEvent::SetTofMult(const UInt_t& tm) { mTofMult = tm; }

inline UInt_t StProtonDstPicoEvent::GetTofMult() const { return mTofMult; }

#endif

#ifndef StProtonDstEvent_h
#define StProtonDstEvent_h

#include "TObject.h"
#include "TArrayI.h"
#include "TClonesArray.h"

#include "StProtonDstTrack.h"
#include "StThreeVectorF.hh"

class StProtonDstEvent : public TObject 
{
    public:
        StProtonDstEvent();
        ~StProtonDstEvent();
        
        StThreeVectorF Vertex() {return mVertex;}
        void SetVertex(StThreeVectorF v) {mVertex = v;}

        int RunNumber() {return mRunNumber;}
        void SetRunNumber(int number) {mRunNumber = number;}

        int RefMult() {return mRefMult;}
        void SetRefMult(int mult) {mRefMult = mult;}
        
        float MagField() {return mMagField;}
        void SetMagField(float field) {mMagField = field;}
        
        int ZdcAdc0() {return mZdcAdc0;}
        void SetZdcAdc0(int zdcadc0) {mZdcAdc0 = zdcadc0;}
        
        float ReactionPlane() {return mPhiRPWeighted;}
        void SetReactionPlane(float phi) {mPhiRPWeighted = phi; mPhiRP = phi;}
        float ReactionPlaneSubeventA() { return mPhiRPWeightedSubeventA;}
        void SetReactionPlaneSubeventA(float phi) {mPhiRPWeightedSubeventA = phi;}
        float ReactionPlaneSubeventB() { return mPhiRPWeightedSubeventB;}
        void SetReactionPlaneSubeventB(float phi) { mPhiRPWeightedSubeventB = phi;}

        float EtaSymTpc() { return mEtaSymTpc;}
        void SetEtaSymTpc(float etasym_corrected) { mEtaSymTpc = etasym_corrected;}
        int NglobalTracks() { return mNglobalTracks;}
        void SetNglobalTracks(int Nglobals) { mNglobalTracks = Nglobals;}
        int TofMult() { return mTofMult;}
        void SetTofMult(int tofmultiplicity) { mTofMult = tofmultiplicity;}
        
        void Clear(const Option_t* option="");
            
        StProtonDstTrack* AddProtonTrack();                                         //Adds a Pion Track
        TClonesArray* ProtonTracks() {return fProtonTracks;}                   //Returns a Pion Track

        unsigned short mNPionTracks;

    private:
        int mRunNumber;
        StThreeVectorF mVertex;		// Primary vertex
        unsigned short mRefMult;  // Tpc mult. used for cent. def in AuAu
        float mMagField;  //B-field
        unsigned short mZdcAdc0;
        
        float mPhiRP;           //Reaction plane angle
        float mPhiRPWeighted;   //Weighted RP angle
        float mPhiRPWeightedSubeventA;  //Subevent A event plane angle for resolution calculation
        float mPhiRPWeightedSubeventB;  //Subevent B event plane angle for resolution calculation
        float mEtaSymTpc;  //eta sym tpc for event cuts
        int mNglobalTracks;  //nGlobal tracks for event cuts
        int mTofMult;  //Tof mult for event cuts
        
        TClonesArray *fProtonTracks;    // Array of Pion Track objects
 

    ClassDef(StProtonDstEvent,3)
};

#endif

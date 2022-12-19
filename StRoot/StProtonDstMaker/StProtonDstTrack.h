#ifndef StProtonDstTrack_h
#define StProtonDstTrack_h

#include "TObject.h"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"

class StProtonDstTrack : public TObject 
{
    public:
        StProtonDstTrack(double Px, double Py, double Pz);
        StProtonDstTrack() {};

        virtual ~StProtonDstTrack() {};

        int  Charge();
        void SetCharge(int charge);

        int  NHits();
        void SetNHits(int nHits);

        void SetP(double Px, double Py, double Pz);
        void SetP(StThreeVectorF v);
        StThreeVectorF& P();

        StThreeVectorD Dca3d();
        void SetDca3d(StThreeVectorD v);
        StThreeVectorD Dca3dGlobal();
        void SetDca3dGlobal(StThreeVectorD v);
        
        float PidPiPlus(); //they should be called GetPidPiPlus() etc. - JJ
        float PidPiMinus();
        float PidKaonPlus();
        float PidKaonMinus();
        float PidProton();
        float PidAntiProton();
        float PidElectron();
        float PidPositron();
        void SetPidPiPlus(float pid);
        void SetPidPiMinus(float pid);
        void SetPidKaonPlus(float pid);
        void SetPidKaonMinus(float pid);
        void SetPidProton(float pid);
        void SetPidAntiProton(float pid);
        void SetPidElectron(float pid);
        void SetPidPositron(float pid);
        float Chi2();
        void SetChi2(float chi);
        float Dedx();
        void SetDedx(float dedx);
        int Flag();
        void SetFlag(int trkflag);
        
        void SetFirstPoint(StThreeVectorF first);
        StThreeVectorF FirstPoint();
        void SetLastPoint(StThreeVectorF last);
        StThreeVectorF LastPoint();
        
        unsigned int TopologyMap(const int word);
        void SetTopologyMap(const int word, const unsigned int map);

    private:
        StThreeVectorF fP;
        char mCharge;
        unsigned char mNHits;
        unsigned int mMap[2];
        StThreeVectorF mFirstPoint,mLastPoint;
        StThreeVectorD mDca,mDcaGlobal;
        float mPidPiPlus,mPidPiMinus,mPidKaonPlus,mPidKaonMinus,mPidProton,mPidAntiProton,mPidElectron,mPidPositron,mChi2,mDedx;
        int mFlag;
    
    ClassDef(StProtonDstTrack,2)
};

inline StProtonDstTrack::StProtonDstTrack(double Px, double Py, double Pz) 
{
	fP[0] = Px;
	fP[1] = Py;
	fP[2] = Pz;
}

inline int  Charge() {return mCharge;}

inline void SetCharge(int charge) {mCharge = charge;}

inline int  NHits() {return mNHits;}

inline void SetNHits(int nHits) {mNHits = nHits;}

inline void SetP(double Px, double Py, double Pz) { fP[0] = Px; fP[1] = Py; fP[2] = Pz; }

inline void SetP(StThreeVectorF v) { fP = v; }

inline StThreeVectorF& P() {return fP;}

inline StThreeVectorD Dca3d() {return mDca;}

inline void SetDca3d(StThreeVectorD v) { mDca = v; }

inline StThreeVectorD Dca3dGlobal() {return mDcaGlobal;}

inline void SetDca3dGlobal(StThreeVectorD v) { mDcaGlobal = v; }

inline float PidPiPlus() { return mPidPiPlus;}

inline float PidPiMinus() { return mPidPiMinus;}

inline float PidKaonPlus() { return mPidKaonPlus;}

inline float PidKaonMinus() { return mPidKaonMinus;}

inline float PidProton() { return mPidProton;}

inline float PidAntiProton() { return mPidAntiProton;}

inline float PidElectron() { return mPidElectron;}

inline float PidPositron() { return mPidPositron;}

inline void SetPidPiPlus(float pid) { mPidPiPlus = pid;}

inline void SetPidPiMinus(float pid) { mPidPiMinus = pid;}

inline void SetPidKaonPlus(float pid) { mPidKaonPlus = pid;}

inline void SetPidKaonMinus(float pid) { mPidKaonMinus = pid;}

inline void SetPidProton(float pid) { mPidProton = pid;}

inline void SetPidAntiProton(float pid) { mPidAntiProton = pid;}

inline void SetPidElectron(float pid) { mPidElectron = pid;}

inline void SetPidPositron(float pid) { mPidPositron = pid;}

inline float Chi2() { return mChi2; }

inline void SetChi2(float chi) { mChi2 = chi; }

inline float Dedx() { return mDedx; }

inline void SetDedx(float dedx) { mDedx = dedx; }

inline int Flag() { return mFlag; }

inline void SetFlag(int trkflag) { mFlag = trkflag; }

inline void SetFirstPoint(StThreeVectorF first) { mFirstPoint = first; }

inline StThreeVectorF FirstPoint() { return mFirstPoint; }

inline void SetLastPoint(StThreeVectorF last) { mLastPoint = last; }

inline StThreeVectorF LastPoint() { return mLastPoint; }

inline unsigned int TopologyMap(const int word) const { return mMap[word];}

inline void SetTopologyMap(const int word, const unsigned int map) { mMap[word]=map;}

#endif


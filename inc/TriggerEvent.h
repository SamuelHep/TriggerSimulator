#ifndef URQMD_TRIGEVENT_H
#define URQMD_TRIGEVENT_H

#ifdef private
#undef private
#endif

#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TriggerTrack.h"

class TriggerEvent : public TObject {

 public:
  
  TriggerEvent();
  TriggerEvent(URQMDEvent * urmqdEvent,bool reflection);
  virtual ~TriggerEvent();

  void SetVertex(double vx,double vy, double vz){vX=vx;vY=vy;vZ=vz;}
  void SetTrueMult(double val){mTrueMult=val;}; 

  double GetVertexX(){return vX;};
  double GetVertexY(){return vY;};
  double GetVertexZ(){return vZ;};
  int GetTrueMult(){return mTrueMult;};

  std::vector< TriggerTrack > GetTriggerTrackArray(){ return mTriggerTrackArray;};
  TriggerTrack * GetTrack(int i){ return &mTriggerTrackArray[i];};
  int GetNTracks(){ return (int) mTriggerTrackArray.size();};
  int FillTriggerTracks();

  void SetReflect(double val){ reflect = val; }

 private:
  
  URQMDEvent * mURQMDEvent;

  double reflect;
  int mTrueMult;
  std::vector< TriggerTrack > mTriggerTrackArray;
  double vX;
  double vY;
  double vZ;

  ClassDef(TriggerEvent,1);
};


#endif

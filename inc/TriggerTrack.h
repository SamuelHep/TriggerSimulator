#ifndef URQMD_TRIGTRACK_H
#define URQMD_TRIGTRACK_H

#ifdef private
#undef private
#endif

#include "TObject.h"

class TriggerTrack : public TObject {

 public:

  TriggerTrack();
  ~TriggerTrack();

  void SetPt(double val){mPt=val;};
  void SetPz(double val){mPz=val;};
  void SetQ(double val){mQ=val;};
  void SetHit(bool val){mHitDetector=val;}

  double GetPt(){return mPt;};
  double GetPz(){return mPz;};
  double GetQ(){return mQ;};
  
  bool Hit(){return mHitDetector;};

 private:

  bool mHitDetector;
  double mQ;
  double mPt;
  double mPz;
    
  ClassDef(TriggerTrack,1);

};


#endif

  
  

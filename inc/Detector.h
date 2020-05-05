#ifndef DETECTOR_TEMPLATE_H
#define DETECTOR_TEMPLATE_H

#ifdef private
#undef private
#endif

#include "TObject.h"
#include "TVector3.h"
#include "TLine.h"
#include "TRandom3.h"

class Detector : public TObject {

 public:

  Detector();
  ~Detector();

  Detector(double pointX1, double pointY1,double pointX2, double pointY2,bool EMOnly);
  void SetVertex(double x,double y,double z){ mVertex = TVector3(x,y,z);};
  void SetP1(double x, double y){ mP1 = TVector3(x,y,0);}
  void SetP2(double x, double y){ mP2 = TVector3(x,y,0);}
  void SetEM(bool val){ mEMOnly=val;};

  void SetAcceptance();
  int DetectorResponse(TriggerEvent * trigEvent);
  void SetEfficiency(double val){ mEfficiency = val;};
  void SetMinPt(double val){ minPt = val;};

  TVector3 GetVertex(){ return mVertex;}
  TVector3 GetP1(){ return mP1;}
  TVector3 GetP2(){ return mP2;}
  TLine * GetLine(){ mDetectorLine = TLine(mP1.Z(),mP1.Y(),mP2.Z(),mP2.Y()); return &mDetectorLine ;}

 private:

  TVector3 mP1;
  TVector3 mP2;
  
  double minPt;
  double minEta;
  double maxEta;

  double mEfficiency;
  TRandom3 * mRand;

  bool acceptanceSet;
  bool mEMOnly;
  TVector3 mVertex;
  
  TLine mDetectorLine;

  ClassDef(Detector,1);

};


#endif

  
  

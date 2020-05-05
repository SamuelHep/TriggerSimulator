#ifndef DETECTOR_CHAIN_H
#define DETECTOR_CHAIN_H

#ifdef private
#undef private
#endif

#include "TObject.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "TLine.h"
#include "URQMDEvent.h"
#include "TriggerEvent.h"
#include <map>

class DetectorChain : public TObject {

 public:

  DetectorChain();
  ~DetectorChain();

  void AddDetector(TString detectorName, Detector * detector);
  void PrintHits();

  void RunURQMDEvent(URQMDEvent * urmqdEvent);
  void RunTriggerEvent(TriggerEvent * triggerEvent);

  int GetDetectorHits(TString detector);

  void ReflectOn(){reflect = true;};
  void ReflectOff(){reflect = false;};

  TCanvas * DrawEvent();

 private:
  
  TriggerEvent * mTriggerEvent;
  int iCan;

  bool reflect;
  
  std::map< TString,Detector* > mDetectorArray;
  std::map< TString,int > mHitArray;

  ClassDef(DetectorChain,1)
    
    
    };

#endif

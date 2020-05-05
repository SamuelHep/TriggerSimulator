#ifndef URQMD_EVENT_H
#define URQMD_EVENT_H

#ifdef private
#undef private
#endif

#include "TVector3.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TH1F.h"
#include "TH2F.h"

//Forward Declarations
class TVector3;
class TLorentzVector;
class TClonesArray;
class URQMDTrack;
class TH1F;
class TH2F;

//Class Definition
class URQMDEvent : public TObject {

 private:
  int eventIndex;
  int nTracks;
  double impactParameter;
  double vX, vY, vZ;
  std::vector < URQMDTrack> tracks;
  

 public:
  URQMDEvent();
  virtual ~URQMDEvent();

  //Gets
  int GetEventIndex(){return eventIndex;}
  int GetMultiplicity(){return nTracks;}
  double GetImpactParameter(){return impactParameter; }
  double GetVertexX(){return vX;}
  double GetVertexY(){return vY;}
  double GetVertexZ(){return vZ;}
  int GetNSpectators();
  int GetNNucleonsOffMass();
  
  TVector3 GetVertex(){return TVector3(vX,vY,vZ);}
  URQMDTrack *GetTrack(int trackIndex){return &(tracks.at(trackIndex));}
  std::vector< URQMDTrack > GetTrackArray(){return tracks; }
  void AddTrack(URQMDTrack track);
  void Reset();
  
  //Sets
  void SetEventIndex(int val){eventIndex=val;}
  void SetMultiplicity(int val){nTracks=val;}
  void SetImpactParameter(double val){impactParameter = val;}
  void SetVertex(double x, double y, double z);
  void SetVertex(TH1F *zVertexDist, TH2F *xyVertexDist);

  //Prints
  void PrintEventInTxFormat(ofstream *outFile);
  void PrintEventSummary(bool printTracks=false);
  
  ClassDef(URQMDEvent,1);
};

#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TObject.h"
#include "TH1F.h"
#include "TH2F.h"

#include "URQMDTrack.h"
#include "URQMDEvent.h"

ClassImp(URQMDEvent);


//_________________________________________________
URQMDEvent::URQMDEvent(){

  eventIndex = -999;
  nTracks = 0;
  impactParameter = -999;
  vX = 0.0;
  vY = 0.0;
  vZ = 0.0;
}

//_________________________________________________
URQMDEvent::~URQMDEvent(){

  tracks.clear();

}

//_________________________________________________
void URQMDEvent::SetVertex(double x, double y, double z){
  vX = x;
  vY = y;
  vZ = z;  
}

//_________________________________________________
void URQMDEvent::SetVertex(TH1F *zVertexDist, TH2F *xyVertexDist){

  vZ = zVertexDist->GetRandom();
  xyVertexDist->GetRandom2(vX,vY);
  
}

//__________________________________________________
void URQMDEvent::AddTrack(URQMDTrack track){
  track.SetTrackIndex(nTracks);
  tracks.push_back(track);
  nTracks = tracks.size();
}

//__________________________________________________
void URQMDEvent::Reset(){

  eventIndex = -999;
  nTracks = 0;
  impactParameter = -999;
  vX = 0.0;
  vY = 0.0;
  vZ = 0.0;
  
  tracks.clear();
  
}

//__________________________________________________
int URQMDEvent::GetNSpectators(){

  int nSpectators(0);
  URQMDTrack *track = NULL;
  for (int iTrack=0; iTrack<nTracks; iTrack++){
    track = this->GetTrack(iTrack);
    
    if (track->GetNumberOfCollisions() == 0)
      continue;

    nSpectators++;      
  }

  return nSpectators;  
}

//__________________________________________________
int URQMDEvent::GetNNucleonsOffMass(){

  //URQMD reports nucleons that are part of a nucleus
  //as separate entries in the .f13 files, but they have
  //a reduced mass. This function returns the number of
  //nucleons of urqmdPid==1 that Do NOT have a mass of .938 GeV

  int nNucleonsOffMass(0);
  URQMDTrack *track = NULL;
  for (int iTrack=0; iTrack<nTracks; iTrack++){
    track = this->GetTrack(iTrack);
    
    if (track->GetURQMDPid() == 1 && ((int)(1000*track->GetMass())) != 938)
      nNucleonsOffMass++;
  }
  
  return nNucleonsOffMass;
}

//__________________________________________________
void URQMDEvent::PrintEventInTxFormat(ofstream *outFile){

  //Note that this function does not print nucleons which have
  //masses which have been reduced by binding energy
  
  int txMultiplicity = (int)tracks.size() - this->GetNNucleonsOffMass();

  *outFile <<TString::Format("EVENT: %d %d %d\n",eventIndex,txMultiplicity,1);
  *outFile <<TString::Format("VERTEX: %g %g %g %g %d %d %d %d\n",
			     vX,vY,vZ, 0.0, 1, 0, 0,txMultiplicity);
  
  int nGoodTracks(0);
  for (unsigned int iTrack=0; iTrack<tracks.size(); iTrack++){
    URQMDTrack *track = &tracks.at(iTrack);
    if (track->GetURQMDPid() == 1 && ((int)(1000*track->GetMass())) != 938)
      continue;
    *outFile <<TString::Format("TRACK: %d %g %g %g %d %d %d %d\n",
			       track->GetGeantPid(),track->GetMomentumX(),track->GetMomentumY(),
			       track->GetMomentumZ(),nGoodTracks,track->GetStartVertex(),
			       track->GetStopVertex(),track->GetURQMDPid());
    nGoodTracks++;
  }


  
}

//___________________________________________________
void URQMDEvent::PrintEventSummary(bool printTracks){

  std::cout <<"EVENT SUMMARY: " <<"Index: " <<eventIndex <<" Multiplicity: " <<nTracks <<"\n";

  if (!printTracks)
    return;
  
  for (long iTrack=0; iTrack<nTracks; iTrack++){
    std::cout <<"\t";
    tracks.at(iTrack).PrintTrackSummary();
  }
  std::cout <<"\n";
  
}

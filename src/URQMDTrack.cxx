#include <iostream>
#include "TObject.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TString.h"

#include "URQMDTrack.h"

ClassImp(URQMDTrack);

//_________________________________________________________
URQMDTrack::URQMDTrack(){

  trackIndex = -999;
  urqmdPID = -999;
  geantPID = -999;
  startVertex = 1; //Should always be 1 indicating starting at event vertex
  stopVertex  = 0; //Should always be 0 indiciating ending outside event
  charge = -999;
  time = -999;
  px = -999;
  py = -999;
  pz = -999;
  energy = -999;
  mass = -999;
  timeFr = -999;
  xFr = -999;
  yFr = -999;
  zFr = -999;
  pxFr = -999;
  pyFr = -999;
  pzFr = -999;
  energyFr = -999;
  iso3 = -999;
  parentCollisionNumber = -999;
  nColl = -999;
  parentProcess = -999;

}

//_________________________________________________________
URQMDTrack::~URQMDTrack(){

  //Nothing to do here

}

//_________________________________________________________
double URQMDTrack::GetEta(){
  
}

//_________________________________________________________
double URQMDTrack::GetRapidity(){
  return 0.5 * TMath::Log( (energy + pz) / (energy - pz));
}

//________________________________________________________
double URQMDTrack::GetPt(){
  return sqrt( pow(px,2) + pow(py,2) );
}

//_________________________________________________________
double URQMDTrack::GetmTm0(){
  return sqrt( TMath::Power(GetPt(),2) + TMath::Power(mass,2) ) - mass;
}

//________________________________________________________
void URQMDTrack::PrintTrackSummary(){

  std::cout <<"Index: " <<trackIndex <<" "
       <<"URQMDPid: " <<urqmdPID <<" "
       <<"Charge: " <<charge <<"\n";
  
}

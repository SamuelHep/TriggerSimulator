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
#include "TriggerEvent.h"
#include "TriggerTrack.h"
#include "Detector.h"
#include "TRandom3.h"

Detector::Detector()
{
  mEfficiency =1;
  mVertex = TVector3(-999,-999,-999);
  minPt=0;
  acceptanceSet=false;

  mRand= new TRandom3();

}

Detector::~Detector()
{


}

Detector::Detector(double pointX1, double pointY1,double pointX2, double pointY2,bool EMOnly)
{

  mEfficiency =1;
  mP1 = TVector3(0,pointY1,pointX1);
  mP2 = TVector3(0,pointY2,pointX2);
  mVertex = TVector3(-999,-999,-999);
  mEMOnly = EMOnly;
  minPt=0;
  acceptanceSet=false;
  
  mRand= new TRandom3();

}

void Detector::SetAcceptance()
{

  TVector3 v1 = mP1 - mVertex;
  TVector3 v2 = mP2 - mVertex;
  double Eta1 = v1.PseudoRapidity();
  double Eta2 = v2.PseudoRapidity();

  minEta = (Eta1 < Eta2) ? Eta1 : Eta2;
  maxEta = (Eta1 > Eta2) ? Eta1 : Eta2;

  std::cout << "MinEta = " << minEta << " MaxEta=" << maxEta << std::endl;

  acceptanceSet = true;

}


int Detector::DetectorResponse(TriggerEvent * trigEvent)
{

  mVertex = TVector3( trigEvent->GetVertexX(), trigEvent->GetVertexY(), trigEvent->GetVertexZ() );

  if (mVertex.X() == -999) return 0;
  if (!acceptanceSet) SetAcceptance();

  int hits=0;

  for (int iTrk=0; iTrk<trigEvent->GetNTracks(); iTrk++)
    {
      //Get track
      TriggerTrack * trk  = trigEvent->GetTrack(iTrk);
      
      //Check if particle has charge
      if (mEMOnly)
	{
	  if (trk->GetQ() == 0) continue;
	}

      //Check if particle has min pt to hit detector
      if ( trk->GetPt() < minPt) continue;

      //Check if within Eta acceptance
      TVector3 trkVec3 = TVector3(0,trk->GetPt(),trk->GetPz());
      double eta = trkVec3.PseudoRapidity();
      
      if ( eta < minEta || eta > maxEta ) continue;

      if (mEfficiency < 1 )
	{
	  if (mRand->Rndm() > mEfficiency) continue;
	}

      trk->SetHit(true);
      hits++;

    }

  return hits;

}

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

ClassImp(TriggerEvent)

//_________________________________________
TriggerEvent::TriggerEvent()
{

  reflect = -1.0;
  vX=0;
  vY=0;
  vZ=-200;
  mTrueMult=-999;

}

//_________________________________________
TriggerEvent::TriggerEvent(URQMDEvent * urqmdEvent,bool reflection)
{
  mURQMDEvent = urqmdEvent;
  reflect = (reflection) ? -1.0 : 1.0;

  vX=0.0;
  vY=0.0;
  vZ=-200.0;

  mTriggerTrackArray.clear();
  FillTriggerTracks();

}

//_________________________________________
TriggerEvent::~TriggerEvent()
{

  if (mURQMDEvent) delete mURQMDEvent;
  mTriggerTrackArray.clear();

}

//________________________________________
int TriggerEvent::FillTriggerTracks()
{

  mTrueMult = mURQMDEvent->GetMultiplicity();

  std::vector< TriggerTrack > triggerTracks;


  for (int iURQMDTrack=0; iURQMDTrack<mTrueMult;iURQMDTrack++)
    {

      TriggerTrack trgTrk;      
      URQMDTrack * trk = mURQMDEvent->GetTrack(iURQMDTrack);
      if (!trk) continue;

      double q  = trk->GetCharge(); 
      double pz = trk->GetMomentumZ();
      double pt = TMath::Sqrt(pow(trk->GetMomentumX(),2) + pow(trk->GetMomentumY(),2));
      trgTrk.SetPt(pt);
      trgTrk.SetPz(reflect*pz);
      trgTrk.SetQ(q);

      triggerTracks.push_back( trgTrk );

    }

  mTriggerTrackArray = triggerTracks;

}

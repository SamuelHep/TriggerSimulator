#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <map>

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
#include "DetectorChain.h"


DetectorChain::DetectorChain()
{
  iCan=0;
  reflect = true;

}

DetectorChain::~DetectorChain()
{
}

void DetectorChain::AddDetector(TString detectorName, Detector * detector)
{
  mDetectorArray[detectorName] = detector;
}


void DetectorChain::RunURQMDEvent(URQMDEvent * urqmdEvent)
{

  TriggerEvent * trigEvent = new TriggerEvent(urqmdEvent,reflect);
  RunTriggerEvent(trigEvent);
}

void DetectorChain::RunTriggerEvent(TriggerEvent * triggerEvent)
{

  mTriggerEvent = triggerEvent;

  for ( auto &v : mHitArray )
    {
      v.second = 0;
    }
  
  for ( auto &v : mDetectorArray )
    {
      mHitArray[v.first] = v.second->DetectorResponse(triggerEvent);
    }

}

void DetectorChain::PrintHits()
{
  for ( auto &v : mHitArray )
    {
      std::cout << v.first << " hits = " << v.second << std::endl;
    }
}

int DetectorChain::GetDetectorHits(TString detector)
{
  return mHitArray[detector];
}


TCanvas * DetectorChain::DrawEvent()
{

  TCanvas * detectorCanvas = new TCanvas(TString::Format("Can%i",iCan),TString::Format("Can%i",iCan),1000,500);
  iCan++;

  detectorCanvas->DrawFrame(-500,-250,500,250);

  for ( auto &v : mDetectorArray )
    {
      TLine * line1 = v.second->GetLine();
      TLine * line2 = new TLine(line1->GetX1(),-1.0*line1->GetY1(),line1->GetX2(),-1.0*line1->GetY2());

      line1->SetLineWidth(2);
      line1->SetLineColor(kGreen+2);
      line1->Draw("same");

      line2->SetLineWidth(2);
      line2->SetLineColor(kGreen+2);
      line2->Draw("same");

    }

  int N = ( mTriggerEvent->GetNTracks() < 100 ) ? mTriggerEvent->GetNTracks() : 100; 

  TRandom3 * rand = new TRandom3();

  for (int iTrack=0; iTrack < N; iTrack++)
    {
      TriggerTrack * trgTrack = mTriggerEvent->GetTrack(iTrack);
      double pz = trgTrack->GetPz();
      double pt = trgTrack->GetPt();

      TVector3 vec3 = TVector3(pz,pt,0);
      TVector3 vec3U = vec3.Unit();
      double Uy = vec3U.Y();
      double Ux = vec3U.X();

      bool yScale = ( Ux*(250.0/Uy) < 700.0  );  
      double scale = (yScale) ?  250.0/Uy : 700.0/Ux;
      
      TVector3 plotVec = vec3U*scale;
      double xyVert = sqrt(pow(mTriggerEvent->GetVertexX(),2) + pow(mTriggerEvent->GetVertexY(),2));

      if ( rand->Rndm() < 0.5 ) Uy = -1.0*Uy;

      TLine * trackLine = new TLine(mTriggerEvent->GetVertexZ(),xyVert,mTriggerEvent->GetVertexZ() + Ux*scale, xyVert + Uy*scale);
      if (trgTrack->Hit()) trackLine->SetLineColor(kRed);
      
      trackLine->Draw();
    }

  return detectorCanvas;

}

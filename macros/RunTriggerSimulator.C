




void RunTriggerSimulator()
{

  gSystem->Load("../bin/TriggerSimulator.so");

  URQMDReader * urqmdReader = new URQMDReader("/home/sheppelmann/sturqmd/rootfiles_AuAu_3_0/AuAu3p0GeV_3_268_UrQMD.root");

  Detector * epdDetector = new Detector( 374, 3, 374, 100, false );
  epdDetector->SetEfficiency(0.99);
  epdDetector->SetMinPt(0.001);

  Detector * tpcXDetector = new Detector( -210, 50, 210, 50, true );
  Detector * tpcYDetector = new Detector( -210, 50, -210, 200, true );

  tpcXDetector->SetEfficiency(0.90);
  tpcYDetector->SetEfficiency(0.90);
  tpcXDetector->SetMinPt(0.1);
  tpcYDetector->SetMinPt(0.1);

  Detector * btofWestDetector = new Detector( -246, 207,0,207, true );
  Detector * btofEastDetector = new Detector( 0, 207,246,207, true );

  btofWestDetector->SetEfficiency(0.35);
  btofEastDetector->SetEfficiency(0.70);
  btofWestDetector->SetMinPt(0.4);
  btofEastDetector->SetMinPt(0.4);

  DetectorChain * detectorChain = new DetectorChain();

  detectorChain->AddDetector( "EPD" , epdDetector );
  detectorChain->AddDetector( "TPCx" , tpcXDetector );
  detectorChain->AddDetector( "TPCy" , tpcYDetector );
  detectorChain->AddDetector( "BTOFwest" , btofWestDetector );
  detectorChain->AddDetector( "BTOFeast" , btofEastDetector );

  long int nEntries = urqmdReader->GetEntries();

  TCanvas * can;

  for ( int iEntry=0; iEntry<10;iEntry++ )
    {
      detectorChain->RunURQMDEvent( urqmdReader->GetEntry(iEntry) );
      if (iEntry==0) can = detectorChain->DrawEvent();

      std::cout << "================ EVENT NUMBER " << iEntry << " ================="<< std::endl;
      std::cout << "TPCx hits=" << detectorChain->GetDetectorHits("TPCx") << std::endl;
      std::cout << "TPCy hits=" << detectorChain->GetDetectorHits("TPCy") << std::endl;
      std::cout << "EPD  hits=" << detectorChain->GetDetectorHits("EPD") << std::endl;
      std::cout << "BTOF West hits=" << detectorChain->GetDetectorHits("BTOFwest") << std::endl;
      std::cout << "BTOF East hits=" << detectorChain->GetDetectorHits("BTOFeast") << std::endl;
     
    }

}






void RunEpdBtofExample()
{

  gSystem->Load("../bin/TriggerSimulator.so");

  URQMDReader * urqmdReader = new URQMDReader("/home/sheppelmann/sturqmd/rootfiles_AuAu_3_0/AuAu3p0GeV_3_268_UrQMD.root");

  Detector * epdDetector = new Detector( 374, 3, 374, 100, false );
  epdDetector->SetEfficiency(0.99);
  epdDetector->SetMinPt(0.01); // GeV
  
  Detector * btofDetector = new Detector( -246, 207,246,207, true );
  btofDetector->SetEfficiency(0.95);
  btofDetector->SetMinPt(0.1); // GeV

  DetectorChain * detectorChain = new DetectorChain();

  detectorChain->AddDetector( "EPD" , epdDetector );
  detectorChain->AddDetector( "BTOF" , btofDetector );

  long int nEntries = urqmdReader->GetEntries();

  TCanvas * can;

  for ( int iEntry=0; iEntry<10;iEntry++ )
    {
      detectorChain->RunURQMDEvent( urqmdReader->GetEntry(iEntry) );
      if (iEntry==0) can = detectorChain->DrawEvent();

      std::cout << "================ EVENT NUMBER " << iEntry << " ================="<< std::endl;
      std::cout << "EPD  hits=" << detectorChain->GetDetectorHits("EPD") << std::endl;
      std::cout << "BTOF hits=" << detectorChain->GetDetectorHits("BTOF") << std::endl;
     
    }

}

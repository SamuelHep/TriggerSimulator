#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TMath.h>
#include <TString.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include "URQMDTrack.h"
#include "URQMDEvent.h"
#include "URQMDReader.h"

ClassImp(URQMDReader);

//____________________________________________________________
URQMDReader::URQMDReader(){

  file = NULL;
  tree = NULL;
  currentURQMDEvent = NULL;
  
  totalEntries = 0;
  
}

//____________________________________________________________
URQMDReader::URQMDReader(TString fileNameWithFullPath){

  file = NULL;
  tree = NULL;
  currentURQMDEvent = NULL;

  ConstructTree(fileNameWithFullPath);
    
}

//____________________________________________________________
URQMDReader::~URQMDReader(){

  if (file){
    file->Close();
    file = NULL;
  }

  if (tree){
    delete tree;
    tree = NULL;
  }
  
}

//_____________________________________________________________
void URQMDReader::ConstructTree(TString fileNameWithFullPath){

  tree = new TChain("UrQMDEvents");

  if (fileNameWithFullPath.Contains(".list") ||
      fileNameWithFullPath.Contains(".txt") ||
      fileNameWithFullPath.Contains(".input")){

    ifstream fileList(fileNameWithFullPath);
    if (!fileList.is_open()){
      fputs("ERROR:: UrQMDReader::ConstructTree() - File list not open! Exiting\n",stderr);
      exit (EXIT_FAILURE);
    }

    std::string fileName;
    while (fileList.good()){
      getline(fileList,fileName);
      if (fileName.length() != 0 && fileName.find(".root") != std::string::npos){
	std::cout <<"Adding: " <<fileName << std::endl;
	tree->Add(fileName.c_str());
      }      
    };

    fileList.close();
    
  }//End if this is a file list

  else {
    tree->Add(fileNameWithFullPath.Data());
    std::cout <<"Adding: " <<fileNameWithFullPath.Data() << std::endl;
  }

  if (!tree){
    fputs("ERROR: DavisDstReader::ConstructTree() - Requested tree is not found!",stderr);
    exit (EXIT_FAILURE);
  }//End if this file is a root file

  //Set the Branch Addresses
  tree->SetBranchAddress("Event",&currentURQMDEvent);

  //Tree Properties
  tree->SetEstimate(tree->GetEntries()+1);
  tree->SetCacheSize(100000000); //100 MBytes
  tree->AddBranchToCache("*",true);

  totalEntries = tree->GetEntries();

}

//_____________________________________________________________
void URQMDReader::SetBranchStatus(TString branchName, Int_t active){
  
  tree->SetBranchStatus(branchName,active);

}

//_____________________________________________________________
URQMDEvent *URQMDReader::GetEntry(Long64_t iEntry){

  if (iEntry < 0){
    fputs("ERROR: URQMDReader::GetEntry() - Entry number must be positive!",stderr);
    exit (EXIT_FAILURE);
  }

  if (iEntry >= totalEntries){
    fputs("ERROR: URQMDReader::GetEtnry() - Entry number must be less than total Entries",stderr);
    exit (EXIT_FAILURE);
  }

  tree->GetEntry(iEntry);

  return currentURQMDEvent;

}

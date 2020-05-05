#ifndef URQMDREADER_H
#define URQMDREADER_H

#ifdef private
#undef private
#endif

#include "TTree.h"
#include "TChain.h"

//Forward Declarations
class URQMDTrack;
class URQMDEvent;
class Tree;
class TFile;
class TChain;

class URQMDReader : public TObject {

 private:
  TFile *file;
  TChain *tree;

  Long64_t totalEntries;
  URQMDEvent *currentURQMDEvent;

  void ConstructTree(TString fileNameWithFullPath);
  
 public:
  URQMDReader();
  URQMDReader(TString fileNameWithFullPath);
  virtual ~URQMDReader();

  //Gets
  TTree *GetTree(){return tree;}
  Long64_t GetEntries(){return totalEntries;}
  URQMDEvent *GetEntry(Long64_t iEntry);
    
  //Sets
  void SetBranchStatus(TString branchName, Int_t active);

  ClassDef(URQMDReader,1);

};

#endif

#ifndef URQMD_TRACK_H
#define URQMD_TRACK_H

#ifdef private
#undef private
#endif

//Forward Declarations
class TVector3;
class TLorentzVector;

//Class Definition
class URQMDTrack : public TObject {

 private:
  int trackIndex;       //Track Counter
  int urqmdPID;         //PID According to UrQMD's method
  int geantPID;         //PID According to Geant 
  int startVertex;      //! //Always 1 to indicate starting at Event vertex
  int stopVertex;       //! //Always 0 to indicate ending outside of event
  int charge;           //Charge of Track
  double time;          //End time of Track
  double px, py, pz;    //Momenta of Track
  double x, y, z;       //Position of Track
  double energy;        //Energy of Track
  double mass;          //Mass of Particle

  double timeFr;            //Freeze out time of Track
  double xFr, yFr, zFr;     //Freeze out positoin of Track
  double pxFr, pyFr, pzFr;  //Freeze out Momenta
  double energyFr;          //Freeze out Energy

  int iso3;                  //2*I_3 (see section 1.2 of URQMD Manual)
  int parentCollisionNumber; //No Idea what this is (poorly explained in the Manual)
  int nColl;                 //Number of Collisions. Spectators can be found with nColl=0
  int parentProcess;         //ID specifying the type of process responsible for this daughter

 public:
  URQMDTrack();
  virtual ~URQMDTrack();

  //Gets
  int GetTrackIndex(){return trackIndex;}
  int GetURQMDPid(){return urqmdPID;}
  int GetGeantPid(){return geantPID;}
  int GetStartVertex(){return startVertex;}
  int GetStopVertex(){return stopVertex;}
  int GetCharge(){return charge;}
  int GetIso3(){return iso3;}
  int GetParentCollisionNumber(){return parentCollisionNumber;}
  int GetNumberOfCollisions(){return nColl;}
  int GetParentProcess(){return parentProcess;}
  
  double GetEndTime(){return time;}
  double GetMomentumX(){return px;}
  double GetMomentumY(){return py;}
  double GetMomentumZ(){return pz;}
  double GetPositionX(){return x;}
  double GetPositionY(){return y;}
  double GetPositionZ(){return z;}
  double GetMass(){return mass;}
  double GetEnergy(){return energy;}
  double GetFreezeOutTime(){return timeFr;}
  double GetFreezeOutPositionX(){return xFr;}
  double GetFreezeOutPositionY(){return yFr;}
  double GetFreezeOutPositionZ(){return zFr;}
  double GetFreezeOutMomentumX(){return pxFr;}
  double GetFreezeOutMomentumY(){return pyFr;}
  double GetFreezeOutMomentumZ(){return pzFr;}
  double GetFreezeOutEnergy(){return energyFr;}
  
  TVector3 GetMomentum(){return TVector3(px,py,pz);}
  TVector3 GetPosition(){return TVector3(x,y,z);}
  TVector3 GetFreezeOutPosition(){return TVector3(xFr,yFr,zFr);}

  TLorentzVector GetPositionTimeFourVector(){return TLorentzVector(x,y,z,time);}
  TLorentzVector GetFreezeOutPositionTimeVector(){return TLorentzVector(xFr,yFr,zFr,timeFr);}
  TLorentzVector GetEnergyMomentumFourVector(){return TLorentzVector(px,py,pz,energy);}
  TLorentzVector GetFreezeOutEnergyMomentumFourVector(){return TLorentzVector(pxFr,pyFr,pzFr,energyFr);}

  //Member Functions Implemented in .cxx file
  double GetEta();
  double GetRapidity();
  double GetPt();
  double GetmTm0();

  //Sets
  int SetTrackIndex(int val){trackIndex = val;}
  int SetURQMDPid(int val){urqmdPID = val;}
  int SetGeantPid(int val){geantPID = val;}
  int SetStartVertex(int val){startVertex = val;}
  int SetStopVertex(int val){stopVertex = val;}
  int SetCharge(int val){charge = val;}
  int SetIso3(int val){iso3 = val;}
  int SetParentCollisionNumber(int val){parentCollisionNumber = val;}
  int SetNumberOfCollisions(int val){nColl = val;}
  int SetParentProcess(int val){parentProcess = val;}
  
  double SetEndTime(double val){time = val;}
  double SetMomentumX(double val){px = val;}
  double SetMomentumY(double val){py = val;}
  double SetMomentumZ(double val){pz = val;}
  double SetPositionX(double val){x = val;}
  double SetPositionY(double val){y = val;}
  double SetPositionZ(double val){z = val;}
  double SetMass(double val){mass = val;}
  double SetEnergy(double val){energy = val;}
  double SetFreezeOutTime(double val){timeFr = val;}
  double SetFreezeOutPositionX(double val){xFr = val;}
  double SetFreezeOutPositionY(double val){yFr = val;}
  double SetFreezeOutPositionZ(double val){zFr = val;}
  double SetFreezeOutMomentumX(double val){pxFr = val;}
  double SetFreezeOutMomentumY(double val){pyFr = val;}
  double SetFreezeOutMomentumZ(double val){pzFr = val;}
  double SetFreezeOutEnergy(double val){energyFr = val;}

  //Prints
  void PrintTrackSummary();
  
  ClassDef(URQMDTrack,1);

};

#endif

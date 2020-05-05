#ifdef __CINT__

// turns off dictionary generation for all
#pragma link off all class;
#pragma link off all function;
#pragma link off all global;
#pragma link off all typedef;
// link to nested scope


#pragma link C++ nestedclass;
//#pragma link C++ namespace filesystem;

#pragma link C++ defined_in "Logger.h";

#pragma link C++ class URQMDReader+;
#pragma link C++ class URQMDEvent+;
#pragma link C++ class URQMDTrack+;
#pragma link C++ class TriggerTrack+;
#pragma link C++ class TriggerEvent+;
#pragma link C++ class Detector+;
#pragma link C++ class DetectorChain+;

#endif

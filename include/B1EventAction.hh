
#ifndef B1EventAction_h
#define B1EventAction_h 1

#include <vector>
#include "G4UserEventAction.hh"
//#include "B1RunAction.hh"
#include "globals.hh"

class B1RunAction;
class HistoManager;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction , HistoManager*);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
  
  void AddEdep1(G4double edep) { fEdep1 += edep; }
  void AddEdep2(G4double edep) { fEdep2 += edep; }
  void AddEdep3(G4double edep) {fEdep3 += edep;}

  void IncrementPhotonInDetector(const size_t detectorID);
  
  private:
    B1RunAction* fRunAction;
    HistoManager* fHistoManager;

  G4double     fEdep1;
  G4double     fEdep2;
  G4double     fEdep3;
    
    G4int fPrintModulo;
  std::vector<G4int> fNPhotonInDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

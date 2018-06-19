#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4Track.hh"
#include "B1RunAction.hh"

class B1EventAction;
class DetectorConstruction;
class G4LogicalVolume;
/// Stepping action class
/// 

class B1SteppingAction : public G4UserSteppingAction
{
  public:
  B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction);
    virtual ~B1SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
  G4int GetD1S(){return CD1Sci;};
  G4int GetD1C(){return CD1Che;};
  G4int GetD2C(){return CD2Che;};
  
  private:

  B1EventAction*  fEventAction;
  B1RunAction* fRunAction;
  G4LogicalVolume* fScoringVolume1;
  G4LogicalVolume* fScoringVolume2;
  G4LogicalVolume* fScoringVolume3;
  G4int fScintillationCounter;
  G4int fCerenkovCounter;
  G4int fEventNumber;
  G4int CD1Sci;
  G4int CD1Che;
  G4int CD2Che;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


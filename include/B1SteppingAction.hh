#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class B1EventAction;
class DetectorConstruction;
class G4LogicalVolume;

/// Stepping action class
/// 

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
  B1EventAction*  fEventAction;
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
//pippo

#ifndef B1StackingAction_h
#define B1StackingAction_h 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class G4LogicalVolume;
class OpNoviceStackingAction : public G4UserStackingAction
{
  public:
    OpNoviceStackingAction();
    virtual ~OpNoviceStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4LogicalVolume* fScoringVolume1;
  G4LogicalVolume* fScoringVolume2;
  G4int fScintillationCounter;
    G4int fCerenkovCounter;
    G4int CD1Sci;
  G4int CD1Che;
  G4int CD2Che;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

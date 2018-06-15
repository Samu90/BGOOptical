#include "B1StackingAction.hh"
#include "B1ActionInitialization.hh"
#include "HistoManager.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1DetectorConstruction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::B1ActionInitialization(B1DetectorConstruction* detector)
  : G4VUserActionInitialization(),
    fDetector(detector)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::~B1ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::BuildForMaster() const
{// Histo manager
    HistoManager*  histo = new HistoManager();
    
    // Actions
    SetUserAction(new B1RunAction(histo));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::Build() const
{  HistoManager*  histo = new HistoManager();

   
  SetUserAction(new B1PrimaryGeneratorAction(fDetector));

  B1RunAction* runAction = new B1RunAction(histo);
  SetUserAction(runAction);
  
  B1EventAction* eventAction = new B1EventAction(runAction, histo);
  SetUserAction(eventAction);
  
    B1SteppingAction* steppingAction = new B1SteppingAction(eventAction);
    SetUserAction(steppingAction);

    OpNoviceStackingAction* stackingAction= new OpNoviceStackingAction();
    SetUserAction(stackingAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "B1StackingAction.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "B1DetectorConstruction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::OpNoviceStackingAction()
  : G4UserStackingAction(),
     fScintillationCounter(0),
    fCerenkovCounter(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::~OpNoviceStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//aTrack punta all'i-esima particella secondaria
G4ClassificationOfNewTrack
OpNoviceStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary

      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation"){
        fScintillationCounter++;}

      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov"){
	fCerenkovCounter++;}


      
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::NewStage()
{
  G4cout<<G4endl;
  G4cout << "Number of Scintillation photons produced in this event : "
         << fScintillationCounter << G4endl;
  G4cout << "Number of Cerenkov photons produced in this event : "
         << fCerenkovCounter << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

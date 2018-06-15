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
    fScoringVolume1(0),
    fScoringVolume2(0),
    fScintillationCounter(0),
    fCerenkovCounter(0),
    CD1Sci(0),
    CD1Che(0),
    CD2Che(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceStackingAction::~OpNoviceStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//aTrack punta all'i-esima particella secondaria
G4ClassificationOfNewTrack
OpNoviceStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
if (!fScoringVolume1 && !fScoringVolume2) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();
 }
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary

      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation"){
        fScintillationCounter++;}

      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov"){
	fCerenkovCounter++;}

      G4LogicalVolume* OptVolume=aTrack->GetVolume();
      //int ParticleID = aTrack->GetParentID();
      G4cout<< OptVolume <<G4endl;
      if(OptVolume==fScoringVolume1 ){
	G4cout<<"è entrata nel volume1"<<G4endl;
	if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation"){
	  CD1Sci++;
	  G4double EnergyOpt=aTrack->GetTotalEnergy();
	}//chiudo if step
	if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov"){
	  CD1Che++;
	  G4double EnergyOpt=aTrack->GetTotalEnergy();
	}//chiudo if step      
      }//chiudo controllo volume
      
      if(OptVolume==fScoringVolume2){
	if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov"){
	  CD2Che++;
	  G4double EnergyOpt=aTrack->GetTotalEnergy();
	  //G4cout<< "cherenkov sul 2"<<G4endl;
	}
      }
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
  G4cout<<G4endl;
  G4cout << "Number of Photon in Detector 1:  Sci:" << CD1Sci << "   Cher:"<< CD1Che <<G4endl;
  G4cout << "Number of Photon in Detector 2:  Cher:" << CD2Che << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceStackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

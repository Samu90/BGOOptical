#include "G4OpticalPhoton.hh"
#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "OpNovicePhysicsList.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "B1RunAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction,B1RunAction* runAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fRunAction(runAction),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0)
{
  fScintillationCounter = 0;
  fCerenkovCounter      = 0;
  fEventNumber = -1;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume3 && !fScoringVolume1 && !fScoringVolume2) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume3 = detectorConstruction->GetScoringVolume3();
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();
  }
  

  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();
  
  // get volume of the current step

  /*G4LogicalVolume* volume2 
    = step->GetPostStepPoint()->GetTouchableHandle()
    ->GetVolume()->GetLogicalVolume();*/
  
  // check if we are in scoring volume
  //  if (volume != fScoringVolume3 && volume != fScoringVolume2 && volume != fScoringVolume1) return;
  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();

  fEventAction->AddEdep3(edepStep);

  
  //int ParticleID = aTrack->GetParentID();
  
  
  
  G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  if (eventNumber != fEventNumber) {
    fEventNumber = eventNumber;
    fScintillationCounter = 0;
    fCerenkovCounter = 0;
  }
  
  G4Track* track = step->GetTrack();
  
  G4String ParticleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  
    if (volume == fScoringVolume1 &&  ParticleName=="opticalphoton")
    {	
      fEventAction->IncrementPhotonInDetector(0);
    }
    else if(volume== fScoringVolume2 &&  ParticleName=="opticalphoton")      
      {
	fEventAction->IncrementPhotonInDetector(1);
      }

  
  
  
  if (ParticleName != "opticalphoton"){ // if the particle is an optical photon return, else
    //if the particle is not an optical photon (muon for example) generate secondaries particles
    
    const std::vector<const G4Track*>* secondaries=step->GetSecondaryInCurrentStep();
    
    
    if (secondaries->size()>0) {
      for(unsigned int i=0; i<secondaries->size(); ++i) {
	if (secondaries->at(i)->GetParentID()>0) {
	  if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
	     == G4OpticalPhoton::OpticalPhotonDefinition()){
	    
	    //G4cout<<"fotone"<<G4endl;
	    //if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
	  }
	}
      }
    }//chiude l'if secondaries->Size
  }//if optical

  if(ParticleName == "opticalphoton"){

    if(volume == fScoringVolume1){
      G4double phEnergy=step->GetTrack()->GetTotalEnergy();
      //      G4cout << "fotone sull'1" << G4endl;
      if(track->GetCreatorProcess()->GetProcessName()=="Scintillation"){fRunAction->GetCounter()->IncreaseS1();
	fEventAction->AddEdep1(phEnergy);}
      if(track->GetCreatorProcess()->GetProcessName()=="Cerenkov"){fRunAction->GetCounter()->IncreaseC1();
	fEventAction->AddEdep1(phEnergy);}
      track->SetTrackStatus(fStopAndKill);
    }

    if(volume == fScoringVolume2){
      G4double phEnergy=step->GetTrack()->GetTotalEnergy();
      //G4cout << "fotone sul 2" << G4endl;
      if(track->GetCreatorProcess()->GetProcessName()=="Scintillation"){fRunAction->GetCounter()->IncreaseS2();}
      if(track->GetCreatorProcess()->GetProcessName()=="Cerenkov"){fRunAction->GetCounter()->IncreaseC2();
	G4cout<< "energia fotone  : " <<phEnergy<<G4endl;
	fEventAction->AddEdep2(phEnergy);}
      track->SetTrackStatus(fStopAndKill);
    }
    
  }//if optical photon





  
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


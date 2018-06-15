#include "B1RunAction.hh"
#include "HistoManager.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1SteppingAction.hh"

// #include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


B1RunAction::B1RunAction(HistoManager* histo)
  : G4UserRunAction(),
    fHistoManager(histo),
    fEdep3(0)
{ 
    
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fEdep3);

  Conteggi = new MyCounter();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{
  delete Conteggi;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

    //histograms
    fHistoManager -> Book();
}

void B1RunAction::FillPerEvent(G4double Edep3)
{
    //accumulate statistic
    //
    fEdep3 += Edep3;    //fSum2EGap += EGap*EGap;
    
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run*)
{
  //G4int NbOfEvents = run->GetNumberOfEvent();
//  if (nofEvents == 0) return;
    
    
  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();


  //G4double edep1  = fEdep1.GetValue();
  // G4double edep2  = fEdep2.GetValue();
  // G4double edep3  = fEdep3.GetValue();
    
  // G4double edep1_2 = f2Edep1.GetValue();
  // G4double edep2_2 = f2Edep2.GetValue();



//  const B1DetectorConstruction* detectorConstruction
//   = static_cast<const B1DetectorConstruction*>
//     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.

  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  
    G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
    //compute statistics: mean and rms
    //
    
    
  //    edep1 /= NbOfEvents; edep1_2 /= NbOfEvents;
  //G4double rmsedep1 = edep1_2 - edep1*edep1;
  //if (rmsedep1 >0.) rmsedep1 = std::sqrt(rmsedep1); else rmsedep1 = 0.;
    
  //edep2 /= NbOfEvents; edep2_2 /= NbOfEvents;
  //G4double rmsedep2 = edep2_2 - edep2*edep2;
  //if (rmsedep2 >0.) rmsedep2 = std::sqrt(rmsedep2); else rmsedep2 = 0.;
  //
    
    //    G4cout
    //<< "\n--------------------End of Run------------------------------\n"
    //<< "\n mean Energy in S1: " << G4BestUnit(edep1,"Energy")
    //<< " +- "                          << G4BestUnit(rmsedep1,"Energy")
    //<< "\n mean Energy in S2: " << G4BestUnit(edep2,"Energy")
    //<< " +- "                          << G4BestUnit(rmsedep2,"Energy")
    //<< G4endl;
    
    
    G4cout << "//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << G4endl;
    G4cout << "//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << G4endl;

    G4cout
      << G4endl
      << "--------------------End of Global Run-----------------------"<< G4endl;
       G4cout << "cristal cher:" << Conteggi->GetCountC() << G4endl;
   
   
       
    fHistoManager->PrintStatistic();
    fHistoManager->Save();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




void B1RunAction::AddEdep3(G4double edep)
{
  fEdep3  += edep;
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


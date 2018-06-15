#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "OpNovicePhysicsList.hh"
#include "Randomize.hh"
#include <ctime>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
    // Choose the Random engine
    G4cout << "*******************" << G4endl;
    G4cout << "*** AUTOSEED ON ***" << G4endl;
    G4cout << "*******************" << G4endl;
    //  long seeds[2];
    time_t systime = time(NULL);
    long time0 = (long) systime;
    //  sleep(10);
    //  long time1 = time0 + G4UniformRand()*1024;
    //  sleep(10);
    //  long time2 = time0 + G4UniformRand()*1024;
    //  int base = 2000;
    //  int mult = time0 % base;
    //  seeds[0] =  time1 % base;
    //  seeds[1] = (mult* seeds[0] + time2%mult) % base;
    //  G4cout<<"time: "<<time0<<" "<<time1<<" "<<time2 <<G4endl;
    //  seeds[1] = (long) (systime*G4UniformRand() );
    //  G4cout<<"seeds: "<<seeds[0]<<" "<<seeds[1]<<G4endl;
    //  G4Random::setTheSeeds(seeds);
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4Random::setTheSeed(time0);
    G4Random::showEngineStatus();
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  B1DetectorConstruction* detector = new B1DetectorConstruction();
  runManager->SetUserInitialization(detector);

  // Physics list
  OpNovicePhysicsList* physicsList = new OpNovicePhysicsList();
  physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization(detector));
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

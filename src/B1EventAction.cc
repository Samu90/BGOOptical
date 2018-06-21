

#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction, HistoManager* histo)
: G4UserEventAction(),
  fRunAction(runAction),
  fHistoManager(histo),
  fEdep3(0.),
  fPrintModulo(0)
{
  fPrintModulo=100;
  fNPhotonInDetector.resize(2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event* evt)
{
  fNPhotonInDetector.clear();
    G4int evtNb = evt->GetEventID();
    if (evtNb%fPrintModulo == 0)
        G4cout << "\n---> Begin of event: " << evtNb << G4endl;
    
    // initialisation per event
    fEdep3  = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void B1EventAction::EndOfEventAction(const G4Event*)
{
  fRunAction->FillPerEvent(fEdep3);

    //fill histograms
    //
    if(fEdep3> 0){
       fHistoManager->FillHisto(2, fEdep3);
    }
    //fill ntuple
    //
    fHistoManager->FillNtuple(fEdep3);
    
  bool debug = false;
    
  // accumulate statistics in run action
    fRunAction->AddEdep3(fEdep3);

    for(size_t i=0;i<fNPhotonInDetector.size();i++)
      {
	G4cout<<"N opt phot in detector "<<i<<" "<<fNPhotonInDetector[i]<<G4endl;									  
      }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1EventAction::IncrementPhotonInDetector(const size_t detectorID)
{
  if(detectorID>fNPhotonInDetector.size())
    {
      G4cout<<"ERROR B1EventAction::IncrementPhotonInDetector size"<<G4endl;
	return;
    }
  fNPhotonInDetector[detectorID]++;
}

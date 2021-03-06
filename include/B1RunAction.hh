

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

#include "MyCounter.hh"

class G4Run;
class HistoManager;


/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.



class B1RunAction : public G4UserRunAction
{
public:
  B1RunAction(HistoManager*);
  virtual ~B1RunAction();
  
  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
  void FillPerEvent(G4double, G4double ,G4double );
  void AddEdep1 (G4double edep);
  void AddEdep2 (G4double edep);  
  void AddEdep3 (G4double edep);
  
  MyCounter* GetCounter() const { return Conteggi;};
  
private:
  HistoManager* fHistoManager;
  
  
  G4Accumulable<G4double> fEdep1;
  G4Accumulable<G4double> fEdep2;
  G4Accumulable<G4double> fEdep3;
  
  
  MyCounter* Conteggi;
};






#endif


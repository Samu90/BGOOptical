#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4csv.hh"
//#include "g4xml.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();

    void Book();
    void Save();
    
    void FillHisto(G4int id, G4double e, G4double weight = 1.0);
    void Normalize(G4int id, G4double fac);    

  void FillNtuple(G4double edep3);
    
    void PrintStatistic();        
    
  private:
    G4bool fFactoryOn;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


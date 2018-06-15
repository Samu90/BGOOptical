
#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();
    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    

  G4LogicalVolume* GetScoringVolume1() const { return fScoringVolume1; }
  G4LogicalVolume* GetScoringVolume2() const { return fScoringVolume2; }
  G4LogicalVolume* GetScoringVolume3() const { return fScoringVolume3; }
  

  
  protected:
  
  G4LogicalVolume* fScoringVolume1;
  G4LogicalVolume* fScoringVolume2;
  G4LogicalVolume* fScoringVolume3;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


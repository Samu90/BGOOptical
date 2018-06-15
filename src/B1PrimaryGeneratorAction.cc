#include "B1PrimaryGeneratorAction.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "B1DetectorConstruction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double pCos(){
    G4double thetaMax=3.14159;
    G4double a;
    G4double b;
    do{
        a=(G4float)G4UniformRand()*(thetaMax)-thetaMax/2;
        b=(G4float)G4UniformRand();
    }while(b>cos(a)*cos(a));
    
    
    return a;
    
}
B1PrimaryGeneratorAction::B1PrimaryGeneratorAction(B1DetectorConstruction*)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="mu+");
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleEnergy(2.*GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //    Direzione Momento casuale!!
    G4double theta=pCos();
    G4double phi=G4UniformRand()*2*3.141;
    G4double pz=-1;
    G4double px=0;
    G4double py=0;
 

    G4double x0=0;
    G4double y0=0;
    G4double z0=3*cm;
    
        
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
  
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

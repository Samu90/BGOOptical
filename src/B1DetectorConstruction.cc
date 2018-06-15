#include "B1DetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

//257 muoni attesi con 1.7cm tra gli scint e 12 cm tra scint e cristallo

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  

   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 15*cm;
  G4double world_sizeZ  = 20*cm;

  //Dimensioni Scintillatori
  

  //Posizione scintillatori
  
  
  G4double XDimCher=9*cm;
  G4double YDimCher=1.1*cm;
  G4double ZDimCher=1.1*cm;
  
  G4double XPosCher=0;
  G4double YPosCher=0;
  G4double ZPosCher=0;
  
  G4double density=0.;
  G4int ncomponents=0;
  G4int natoms=0;
  
  
  //
  // Define air
  //
  G4Element* N = nist->FindOrBuildElement(7);
  G4Element* O = nist->FindOrBuildElement(8);
  
  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, ncomponents=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);
  
  //   Define BGO
  
  G4Element* Bi = nist->FindOrBuildElement(83);
  G4Element* Ge = nist->FindOrBuildElement(32);
  
  G4Material* BGO =  new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
  BGO->AddElement(O , natoms=12);
  BGO->AddElement(Ge, natoms= 3);
  BGO->AddElement(Bi, natoms= 4);

  
      
//
// ------------ Generate & Add Material Properties Table ------------
//
  //lunghezza d'onda dei gamma emessi
  G4double photonEnergy[] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };
  //
  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

//
//BGO
//

G4double refractiveIndex1[] =
            { 2.15, 2.15,  2.15, 2.15,  2.15,
              2.15, 2.15,  2.15, 2.15,  2.15,
              2.15, 2.15,  2.15, 2.15,  2.15,
              2.15, 2.15,  2.15, 2.15,  2.15,
              2.15, 2.15,  2.15, 2.15,  2.15,             
              2.15, 2.15,  2.15, 2.15,  2.15,
              2.15, 2.15};

  assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

G4double absorption[] =
           {10.*m,  10.*m,  10.*m,  10.*m, 10.*m, 10.*m,
           10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
           10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
           10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
           10.*m, 10.*m, 10.*m, 10.*m, 10.*m, 10.*m,
           10.*m, 10.*m };

//corrispondenti alla lambda
G4double scintilFast[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  G4double scintilSlow[] =
            { .00, .00, .00, .00, .00, .00, .00,
              .00, .00, .00, .00, .00, .00, .00,
              .00, .00, .00, .00, .00, .00, .00,
              .00, .00, .00, .00, .00, .00, .00,
              .00, .00, .00, .00 };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

 
     
G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

 myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
   ->SetSpline(true);
 myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
   ->SetSpline(true);
 
 myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
   ->SetSpline(true);
 myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
   ->SetSpline(true);
 
 myMPT1->AddConstProperty("SCINTILLATIONYIELD",9./keV);
 myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
 myMPT1->AddConstProperty("FASTTIMECONSTANT", 300.*ns);
 myMPT1->AddConstProperty("SLOWTIMECONSTANT",0*ns);
 myMPT1->AddConstProperty("YIELDRATIO",1.0);
 

  //Set Properties
 BGO->SetMaterialPropertiesTable(myMPT1);
 BGO->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

G4cout << "BGO G4MaterialPropertiesTable" << G4endl;
  myMPT1->DumpTable();

 
//
// Air
//
  G4double refractiveIndex2[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, nEntries);

  //Ser Properties
  air->SetMaterialPropertiesTable(myMPT2);
  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  myMPT2->DumpTable();

  


  //
  //Define world
  //

  

  
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
      world_sizeXY, world_sizeXY, world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        air,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  
  
  

  //SCintillatore Cherenkov

  //Defining rotation
  G4RotationMatrix rotm = G4RotationMatrix();
  rotm.rotateY(0*deg);
  //rotm.rotateY(45*deg);
  G4ThreeVector PosCher=G4ThreeVector(XPosCher,YPosCher,ZPosCher);
  G4Transform3D transform = G4Transform3D(rotm,PosCher);
  
  
  //Defining object
  G4Box* solidCristCher = new G4Box("CrisCher", XDimCher, YDimCher, ZDimCher);
  
  G4LogicalVolume* logicCristCher =
    new G4LogicalVolume(solidCristCher,          //its solid
                            BGO,            //its material
                        "CristCherLV");        //its name
  
  
  
  G4PVPlacement* physCrist= new G4PVPlacement(
		    transform,                     //no rotation
		    logicCristCher,            //its logical volume
		    "Crysta2PV",               //its name
		    logicWorld,                     //its mother  volume
		    false,                 //no boolean operation
		    0,                     //copy number
		    checkOverlaps);       // checking overlaps
  


// ------------- Surfaces --------------
//
// Around Cristal
//

  G4OpticalSurface* opCristSurface = new G4OpticalSurface("CristSurface");
   opCristSurface->SetType(dielectric_LUTDAVIS);
  opCristSurface->SetFinish(Rough_LUT);
  opCristSurface->SetModel(DAVIS);

  G4LogicalBorderSurface* logicCristSurface = new G4LogicalBorderSurface("CristSurface",physCrist,physWorld,opCristSurface);

G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
        (logicCristSurface->GetSurface(physCrist,physWorld)->
                                                       GetSurfaceProperty());
 if (opticalSurface) opticalSurface->DumpInfo();



//
// Generate & Add Material Properties Table attached to the optical surfaces
//
 opticalSurface->SetFinish(polished);
 
  const G4int num = 2;
  G4double ephoton[num] = {2.034*eV, 4.136*eV};

  //OpticalWaterSurface
  G4double refractiveIndex[num] = {2.15, 2.20};
  G4double specularLobe[num]    = {1.0, 1.0};
  G4double specularSpike[num]   = {0.0, 0.0};
  G4double backScatter[num]     = {0.0, 0.0};
  G4double efficency[num]       = {0.7, 0.7};
  G4double reflectivity[num]    = {0.3, 0.3};

  
  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

  myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);
  myST1->AddProperty("EFFICENCY",             ephoton, efficency,     num);
  myST1->AddProperty("REFLECTIVITY",          ephoton, reflectivity,     num);

  G4cout << "BGO Surface G4MaterialPropertiesTable" << G4endl;
  myST1->DumpTable();

  opCristSurface->SetMaterialPropertiesTable(myST1);
  

  G4double XDimDet,YDimDet,ZDimDet;
  XDimDet=0.25*cm;
  YDimDet=1.1*cm;
  ZDimDet=1.1*cm;

  G4double XPosDet1=9.*cm+0.25*cm;//XDimCher+XDimDet;
  G4double YPosDet1=0;
  G4double ZPosDet1=0;

  G4double XPosDet2=-9.*cm-0.25*cm;//-XDimCher-XDimDet;
  G4double YPosDet2=0;
  G4double ZPosDet2=0;

  //Defining rotation
  //rotm.rotateY(45*deg);
  G4ThreeVector PosD1=G4ThreeVector(XPosDet1,YPosDet1,ZPosDet1);
  G4ThreeVector PosD2=G4ThreeVector(XPosDet2,YPosDet2,ZPosDet2);
  G4Transform3D transform1 = G4Transform3D(rotm,PosD1);
  G4Transform3D transform2 = G4Transform3D(rotm,PosD2);


  

  
  G4Box* GammaDet1 = new G4Box("Det1", XDimDet, YDimDet, ZDimDet);
   
  G4LogicalVolume* logicGammaDet1 =
    new G4LogicalVolume(GammaDet1,          //its solid
			air,            //its material
                        "GammaDet1LV");        //its name
  
  G4PVPlacement* physGammaDet1= new G4PVPlacement(
						  transform1,                     //no rotation
						  logicGammaDet1,            //its logical volume
						  "GammaDet1PV",               //its name
						  logicWorld,                     //its mother  volume
						  false,                 //no boolean operation
						  0,                     //copy number
						  checkOverlaps);       // checking overlaps
  
  G4Box* GammaDet2 = new G4Box("Det2", XDimDet, YDimDet, ZDimDet);
  
  G4LogicalVolume* logicGammaDet2 =
    new G4LogicalVolume(GammaDet2,          //its solid
			air,            //its material
			"GammaDet2LV");        //its name
  
  G4PVPlacement* physGammaDet2= new G4PVPlacement(
						  transform2,                     //no rotation
						  logicGammaDet2,            //its logical volume
						  "GammaDet2PV",               //its name
						  logicWorld,                     //its mother  volume
						  false,                 //no boolean operation
						  0,                     //copy number
						  checkOverlaps);       // checking overlaps
  
  
  

  
  
  // Set Crist1 as scoring volume
  //
  fScoringVolume1= logicGammaDet1;
  fScoringVolume2= logicGammaDet2;
  fScoringVolume3= logicCristCher;
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

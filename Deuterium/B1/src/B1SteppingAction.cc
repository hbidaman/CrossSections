//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(const B1DetectorConstruction* detectorConstruction, 
		B1EventAction* eventAction)
: G4UserSteppingAction(), fDetConstruction(detectorConstruction), fEventAction(eventAction)
{}	
	//,
//  fScoringVolume(0)
//{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{/*
  if (!fScoringVolume) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }
*/
  // get volume of the current step
//  G4LogicalVolume* volume 
//    = step->GetPreStepPoint()->GetTouchableHandle()
//      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
 // if (volume != fScoringVolume) return;

  // collect energy deposited in this step
//G4double counter=0.;
 
  G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();    
//  G4double edep = step->GetNonIonizingEnergyDeposit();
  G4double edep = step->GetTotalEnergyDeposit();
//  G4double ekin = step->GetPreStepPoint()->GetKineticEnergy();

  //if ( volume == fDetConstruction->GetAbsorberPV() && edep > 0.) {

G4String  el = "hadElastic";
G4String nCap = "nCapture";
G4String nInEl = "neutronInelastic";
G4String nFiss = "nFission";

//const G4VProcess * process = step->GetPostStepPoint()->GetProcessDefinedStep();
//G4cout << "Process called is: " << process->GetProcessName() << G4endl;

const G4String process = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
G4cout << "Process called is: " << process << G4endl;


  if ( volume == fDetConstruction->GetAbsorberPV()) {
fEventAction->AddAbs(edep);
G4Track *aTrack = step->GetTrack();

//aTrack->SetTrackStatus(fStopAndKill);
//G4cout<< "Volume energy is deposited into: " << fDetConstruction->GetAbsorberPV()->GetName()<< G4endl;
//G4cout<< volume->GetName()<<G4endl;
/*  
 //original way of getting crosssection
if (aTrack->GetParentID() ==1) {

fEventAction->AddCounter();

}
*/
if (aTrack->GetParentID() == 0) {
//G4Track *aTrack = step->GetTrack();

//const G4ThreeVector  initialPosition = step-> GetPreStepPoint()-> GetPosition();
G4double initialPositionz = step->GetPreStepPoint()->GetPosition().getZ();
G4double initialPositiony = step->GetPreStepPoint()->GetPosition().getY();
G4double initialPositionx = step->GetPreStepPoint()->GetPosition().getX();
G4double initialPosition = (initialPositionz + initialPositiony + initialPositionx);
G4cout << "Particle position: " << initialPosition << G4endl;
fEventAction->SetPosition(initialPosition);

const G4String process0 = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
G4cout << "Process called is: " << process0 << G4endl;


if(process0 == el){
fEventAction->AddElCounter();
fEventAction->AddCounter();
aTrack->SetTrackStatus(fStopAndKill);

}
else
if(process0 == nCap || process0 == nInEl || process0 ==nFiss)
{
fEventAction->AddInElCounter();
fEventAction->AddCounter();
aTrack->SetTrackStatus(fStopAndKill);
}
//else
//fEventAction->OtherCounter();

}
else {

//G4Track *aTrack = step->GetTrack();
aTrack->SetTrackStatus(fStopAndKill);

}

//Counter = Counter + 1.;
//  G4cout << "Counter total: " << Counter << G4endl;
  }
//  G4cout << "Energy (edep): "<< edep << G4endl;
  //G4cout << "Counter total: " << Counter << G4endl;
 // fEventAction->AddEdep(edepStep);  
//auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

